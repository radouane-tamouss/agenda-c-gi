
/////APPLICATION CONSOLE D'UNE AGENDA QUI STOCK LES EVENTS DANS UN FICHIER /////
//CREATED BY RADOUANE TAMOUSS ,MOUHCINE MELLOUCK , MOUAD MOUSMIH , AYMAN EL AMRY///





#include<string>
#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<iostream>
#include<time.h>
#include<cstdlib>
#include<fstream>
#include<iomanip>
#pragma warning(disable : 4996) //Pour eviter un error au niveau de visual studio "This function or variable may be unsafe"




using namespace std;
struct Date {
    int dd;
    int mm;
    int yy;
};
struct Date date;

struct Rappel {
    int dd = 0;
    int mm;
    string note;
};
struct Rappel R;


COORD xy = { 0, 0 };

void gotoxy(int x, int y)//cette fonction pour choisir l'emplacement de cout dans le console.
{
    xy.X = x; xy.Y = y; // X et Y des cardinalite
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
}

bool check_leapYear(int year) { //tester c'est une anne est bisixtil ou non (fevrier = 28 || fevrier =29)
    if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0))
        return 1;
    return 0;
}

void increase_month(int* mm, int* yy) { //pour incremonter le mois
    ++* mm;
    if (*mm > 12) {
        ++* yy;
        *mm = *mm - 12;
    }
}

void decrease_month(int* mm, int* yy) { //decrease the month by one
    --* mm;
    if (*mm < 1) {
        --* yy;
        if (*yy < 1600) {
            printf("No record available");
            return;
        }
        *mm = *mm + 12;
    }
}


int getNumberOfDays(int month, int year) { //retourner le nombre de jours au mois et anne donne
    switch (month) {
    case 1: return(31);
    case 2: if (check_leapYear(year) == 1)
        return(29);
          else
        return(28);
    case 3: return(31);
    case 4: return(30);
    case 5: return(31);
    case 6: return(30);
    case 7: return(31);
    case 8: return(31);
    case 9: return(30);
    case 10: return(31);
    case 11: return(30);
    case 12: return(31);
    default: return(-1);
    }
}

string getName(int day) { //retourner le nom de jour
    switch (day) {
    case 0:return("Dimanch");
    case 1:return("Lundi");
    case 2:return("Mardi");
    case 3:return("Mercredi");
    case 4:return("Jeudi");
    case 5:return("Vendredi");
    case 6:return("Samedi");
    default:return("Error in getName() module.Invalid argument passed");
    }
}

void print_date(int mm, int yy) { //prints the name of month and year
    cout << "---------------------------\n";
    gotoxy(25, 6);
    switch (mm) {
    case 1: cout << "Janvier"; break;
    case 2: cout << "Fevrier"; break;
    case 3: cout << "mars"; break;
    case 4: cout << "avril"; break;
    case 5: cout << "Mai"; break;
    case 6: cout << "Juin"; break;
    case 7: cout << "Juillet"; break;
    case 8: cout << "Aout"; break;
    case 9: cout << "Septembre"; break;
    case 10:cout << "Octobre"; break;
    case 11:cout << "Novembre"; break;
    case 12:cout << "Decembre"; break;
    }
    cout << " , " << yy;
    gotoxy(20, 7);
    cout << "---------------------------";
}
int getDayNumber(int day, int mon, int year) { //retourner le nombre d'un jour
    int res = 0, t1, t2, y = year;
    year = year - 1600;
    while (year >= 100) {
        res = res + 5;
        year = year - 100;
    }
    res = (res % 7);
    t1 = ((year - 1) / 4);
    t2 = (year - 1) - t1;
    t1 = (t1 * 2) + t2;
    t1 = (t1 % 7);
    res = res + t1;
    res = res % 7;
    t2 = 0;
    for (t1 = 1; t1 < mon; t1++) {
        t2 += getNumberOfDays(t1, y);
    }
    t2 = t2 + day;
    t2 = t2 % 7;
    res = res + t2;
    res = res % 7;
    if (y > 2000)
        res = res + 1;
    res = res % 7;
    return res;
}

string getDay(int dd, int mm, int yy) {
    int day;
    if (!(mm >= 1 && mm <= 12)) {
        return("Mois invalide!!");
    }
    if (!(dd >= 1 && dd <= getNumberOfDays(mm, yy))) {
        return("Date invalide !");
    }
    if (yy >= 1600) {
        day = getDayNumber(dd, mm, yy);
        day = day % 7;
        return(getName(day));
    }
    else {
        return("Merci de saisir un anne superieur a 1600 : ");
    }
}

int checkNote(int dd, int mm) {
    fstream myfile;//pour enregestre les events
    myfile.open("note.dat", ios::in | ios::binary);
    if (!myfile)
    {
        cout << "imposible d'ouvrire le fichier !";
    }
    while (myfile.read((char*)&R, sizeof(R)), 1 == 1)
    {
        if (R.dd == dd && R.mm == mm)
        {
            myfile.close();
            return 1;
        }
    }
    myfile.close();
    return 0;

}

void printMonth(int mon, int year, int x, int y) { //afficher le mois avec tous les jours 
    int nod, day, cnt, d = 1, x1 = x, y1 = y, isNote = 0;
    if (!(mon >= 1 && mon <= 12)) {
        cout << "    MOIS INVALID !!!   ";
        cin.get();
        return;
    }
    if (!(year >= 1600)) {
        cout << "ANNE INVALIDE !!! ";
        cin.get();
        return;
    }
    gotoxy(20, y);
    print_date(mon, year);
    y += 3;
    gotoxy(x, y);
    cout << "S   M   T   W   T   F   S   ";
    y++;
    nod = getNumberOfDays(mon, year);
    day = getDayNumber(d, mon, year);
    switch (day) { //pour localiser le premier jours dans l'agenda
    case 0:
        x = x;
        cnt = 1;
        break;
    case 1:
        x = x + 4;
        cnt = 2;
        break;
    case 2:
        x = x + 8;
        cnt = 3;
        break;
    case 3:
        x = x + 12;
        cnt = 4;
        break;
    case 4:
        x = x + 16;
        cnt = 5;
        break;
    case 5:
        x = x + 20; //pour la position
        cnt = 6;
        break;
    case 6:
        x = x + 24;
        cnt = 7;
        break;
    default:
        cout << "INVALID DATA FROM THE getOddNumber()MODULE";
        return;
    }
    gotoxy(x, y);

    printf("%02d", d);

    for (d = 2; d <= nod; d++) {
        if (cnt % 7 == 0) {
            y++;
            cnt = 0;
            x = x1 - 4;
        }
        x = x + 4;
        cnt++;
        gotoxy(x, y);



        printf("%02d", d);

    }


    gotoxy(8, y + 2);   cout << "saisir  'n' pour voir le mois suivant ";
    gotoxy(8, y + 3);   cout << "saisir  'p' pour voir le mois precedent ";
    gotoxy(8, y + 4);   cout << " appuyez sur 'q' pour  Quiter";
    gotoxy(8, y + 5);   cout << " saisir  's' pour voir les evenement de ce mois : ";


}

void AddNote() {

    fstream myfile;
    myfile.open("note.dat", ios::out | ios::app | ios::binary);
    system("cls");
    gotoxy(5, 7);
    cout << "entrer un date(dd/mm) :";
    cin >> R.dd;
    cin >> R.mm;
    gotoxy(5, 8);
    cout << "entrer votre evenement :";
    std::cin >> std::ws;

    getline(cin, R.note);

    if (myfile.write((char*)&R, sizeof(R)), 1)
    {
        gotoxy(5, 12);
        cout << "enregestre avec succes  ";
        myfile.close();
    }
    else
    {
        gotoxy(5, 12);
        cout << "\a fail to save !!!\a";

    }
    gotoxy(5, 15);
    cout << "saisir un buton ...... ";
    cin.get();
    myfile.close();


}

void showNote(int mm) {

    fstream myfile;

    int i = 0, isFound = 0;
    system("cls");
    myfile.open("note.dat", ios::out | ios::in | ios::binary);
    if (!myfile)
    {
        cout << "imposible d'ouvrire le fichier  ";
    }
    while (myfile.read((char*)&R, sizeof(R)))
    {
        if (R.mm == mm)
        {
            gotoxy(10, 5 + i);
            isFound = 1;
            cout << "event " << i + 1 << " jour = " << R.dd << " : " << R.note;

i++;
cin.get();
        } 

    }
    if (isFound == 0) {
        gotoxy(10, 5);
        cout << "Aucun evenement";
    }
    gotoxy(10, 7 + i);
    cout << "saisir un buton .......";
    cin.get();


}

int main() {
    string currDate;
    int choice;
    char ch = 'a';
    while (1)
    {
        system("cls");
        gotoxy(40, 15);  cout << "*************       MENU      **************" << endl;
        gotoxy(40, 17); cout << " 1. Trouve un jours" << endl;
        gotoxy(40, 19); cout << " 2. Afficher tous les jours d'un mois " << endl;
        gotoxy(40, 21); cout << " 3. Ajoute un evenement " << endl;
        gotoxy(40, 23); cout << " 4. Afficher la date et l'heure actuelle " << endl;
        gotoxy(40, 25); cout << " 5.EXIT" << endl;
        gotoxy(40, 27); cout << "*********************************************" << endl;
        gotoxy(46, 31); cout << "VEUILLEZ SAISIR VOTRE CHOIX  : ";
        cin >> choice;
        system("cls");
        switch (choice)
        {
        case 1:
            gotoxy(40, 16); cout << "Entrer un  date (DD MM YYYY) : ";
            cin >> date.dd >> date.mm >> date.yy;
            gotoxy(40, 17); cout << "Ce jour est  : " << getDay(date.dd, date.mm, date.yy);
            gotoxy(40, 18);  cout << "\nSaisir un caractere pour continue ......";
            cin.get();
            cin.get();
            break;
        case 2:
            cout << "Entrer  un mois est un anne sous la forme  (MM YYYY) : ";
            cin >> date.mm >> date.yy;
            system("cls");
            while (ch != 'q') {
                printMonth(date.mm, date.yy, 20, 5);
                ch = cin.get();
                if (ch == 'n') {
                    increase_month(&date.mm, &date.yy);
                    system("cls");
                    printMonth(date.mm, date.yy, 20, 5);
                }
                else if (ch == 'p') {
                    decrease_month(&date.mm, &date.yy);
                    system("cls");
                    printMonth(date.mm, date.yy, 20, 5);
                }
                else if (ch == 's') {
                    showNote(date.mm);
                    system("cls");
                }
            }
            break;
        case 3:
            AddNote();
            break;
        case 4:
            while (true)
            {
                time_t t = time(NULL);
                struct tm tm = *localtime(&t);
                gotoxy(44, 16); cout << tm.tm_year + 1900 << "-" << tm.tm_mon + 1 << "-" << tm.tm_mday << "  ";
                gotoxy(44, 17); cout << setw(2) << setfill('0') << tm.tm_hour << ":" << setw(2) << setfill('0') << tm.tm_min << ":" << setw(2) << setfill('0') << tm.tm_sec << "  ";



                system("CLS");
            }
            break;
        case 5:
            exit(0);

        }
    }
    return 0;
}