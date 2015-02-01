/**************************/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <time.h>

using namespace std;

int read_keyboard();

/*************************/


#define H 20
#define L 40

int Ba=(L/2)-8, Bd=(L/2)+7, pts=0, a, x=1, y=1, xx=1, yy=1, t=0, n1=1;

char screen[H][L],n;
bool screen1[H][L],screen2[H][L],screen3[H][L];

bool over=false; // dieu kien ket thuc game


void screen_display(){
  system("clear");
  cout <<"Casse Briques - Minh Nhat Linf14" << endl;
  cout <<"Utiliser les 2 buttons 'a' et 'd' pour aller a gauche et a droite" << endl;
  cout <<"taper le 'q' pour quitter le jeu" << endl;
  for(int i=0; i<H; i++){
    for(int j=0; j<L; j++){
      cout << screen[i][j];
    }
    cout << endl;
  }
  cout <<"Votre points: " << pts << endl;

}

void clear_screen() {
  for(int i=1; i<H-1; i++)
    for (int j=1; j<L-1; j++)
      screen[i][j]=' ';
}

void carre()
{
  system("clear");
  for(int i=0; i<H; i++)
    {
      for(int j=0; j<L; j++)
	{
	  if( i==0 || j==0 || i==H-1 || j==L-1 )
	    screen[i][j]='*';
	}
    }
}


/********************************/
//la barre
int key;

void barre1()
{
  if (key =='a')
    {
    if (Ba>1)
      {
	Ba=Ba-2;Bd=Bd-2;
      }
    }
  if (key == 'd')
    {
      if (Bd<L-2)
	{
	  Ba=Ba+2,Bd=Bd+2;
	}
    }
  
  for (int j=0;j<L;j++) 
    {
  if (j>Ba && j<Bd)
    { screen[H-3][j]='_';}
    }
}


/**les briques***********/
void check(){
for (int j=1;j<L-1;j++){
  screen1[2][j]=true;
  screen1[3][j]=true;

  screen2[7][j]=true;
  screen2[8][j]=true;
  screen2[9][j]=true;
 
  screen3[12][j]=true;
  screen3[13][j]=true;
  screen3[14][j]=true;
  screen3[15][j]=true;
 }
}

void briques1()
{
  for (int j=6;j<L-5;j++){
    if (screen1[2][j]==true)
      screen[2][j]='=';}

  for (int j=9;j<L-8;j++){
    if (screen1[3][j]==true)
      screen[3][j]='=';}
}

void briques2()
{
  for (int j=10;j<L-9;j++){
    if (screen2[7][j]==true)
      screen[7][j]='+';}

  for (int j=9;j<L-6;j++){
    if (screen2[8][j]==true)
      screen[8][j]='+';}
  
  for (int j=8;j<L-5;j++){
    if (screen2[9][j]==true)
      screen[9][j]='+';}
}

void briques3()
{
  for (int j=14;j<L-13;j++){
    if (screen3[12][j]==true)
      screen[12][j]='X';}
  
  for (int j=13;j<L-9;j++){
    if (screen3[13][j]==true)
      screen[13][j]='X';}
  
  for (int j=10;j<L-8;j++){
    if (screen3[14][j]==true)
      screen[14][j]='X';}

  for (int j=9;j<L-5;j++){
    if (screen3[15][j]==true)
      screen[15][j]='X';}
}

void jouer(){ 
  if (screen[x][y]=='='){ 
    xx=-1*xx;
    screen1[x][y]=false;
    screen1[x][y+1]=false;
    pts=pts+50;
  }
  if (pts == 1350 && n1==1){
      over = true;
      screen[x][y]='O';
      screen[x][y+1]=' ';
      screen[x-1][y-1]=' ';
      screen_display();
      cout <<" pressez 'w' pour suivre, 'q' pour quitter" << endl;
      cin >> n;
      if (n == 'w')
	{
	  n1=2;
	  x=1;
	  y=1;
	  xx=1; yy=1;
	}
    }
  if (screen[x][y]=='+'){
    xx=-1*xx;
    screen2[x][y]=false;
    screen2[x][y+1]=false;
    pts=pts+50;
    if (pts == 3250){
      over = true;
      screen[x][y]='O';
      screen[x][y+1]=' ';
      screen[x-1][y-1]=' ';
      screen_display();
      cout <<" pressez 'w' pour suivre, 'q' pour quitter" << endl;
      cin >> n;
      if (n == 'w')
	{
	  n1=3;
	  x=1; y=1; 
	  xx=1; yy=1;
	  }
	}
  }
  if (screen[x][y]=='X'){
    xx=-1*xx;
    screen3[x][y]=false;
    screen3[x][y+1]=false;
    pts=pts+50;
    if (pts == 5250){
      over = true;
      screen[x][y]='O';
      screen[x][y+1]=' ';
      screen[x-1][y-1]=' ';
      screen_display();a=1;
    }
  }
}
/*************************************/	
/* le ball */

void balle(){
  screen[x][y]='O';
  if (x==1) xx=1;
  if (y==1) yy=1;
  if (y==L-2) yy=-1;
  if (x==H-2) over = true;a=0;
  x += xx;
  y += yy;
    //{ over=true; a=0;} // ket thuc game = vrai
  if (screen[x][y]=='_'){
    xx=-1;}
}




int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;
  
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
  
  ch = getchar();
  
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
  
  if(ch != EOF)
    {
      ungetc(ch, stdin);
      return 1;
    }
  
  return 0;
} 
int read_keyboard() {
  int key;
  if (kbhit())
    key = getc(stdin);
  else
    key = 0;
  return key;
}

/**********************************/

int main(){
  int t=0;
  do
    {
      key = read_keyboard();
      clear_screen();
      barre1();
      if (t==0){
	check();
	t=1;
      }
      if (n1==1){
       	briques1();
      }
      if (n1==2){
		briques2();
      }
      if (n1==3){
      	briques3();
	  }
      jouer();
      balle();
      carre();
      screen_display();
      usleep(100 * 1000);
      if (over==true){
	if (a==0){
	  clear_screen();
	  cout <<"You lose!!" <<endl;
	  exit(0);
	}
	if (a==1){
	  clear_screen();
	  cout <<"You win!!" <<endl;
	 exit(0);}  // ket thuc game
      }
    }
  while (key != 'q');
  return(0);
}
