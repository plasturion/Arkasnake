#include<windows.h>
#include<cstdio>
#include<ctime>
#include<queue>
using namespace std;
struct Seg{
    int x,y;
}s;
queue<Seg> snake;
int x=1,y=1,dx=1,dy=-1,maxX=60,maxY=19;
int field[65][25],i,j,sLen=1;
COORD coord={0,0};
void gotoxy(int x, int y){
   coord.X = x;
   coord.Y = y; // X and Y coordinates
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void initGame(){
    system("CLS");
    sLen=1;
    for(i=0;i<=60;i++)
        for(j=0;j<=20;j++)
            field[i][j] = 0;
    for(i=0;i<90;i++){
        while(field[x=rand()%55+2][y=rand()%16+2]!=0);//find new place
        field[x][y]=1;
        gotoxy(x,y);
        printf("#");
    }
    x=11,y=1;
}
void moveBody(){
    s.x=x;
    s.y=y;
    snake.push(s);
    s=snake.front();
    snake.pop();
    field[s.x][s.y]=0;
    gotoxy(s.x,s.y);
    printf(" ");
}
void eatThis(){
    field[x][y]=0;
    dx=-dx;
    s.x=x;
    s.y=y;
    snake.push(s);
    sLen++;
}
void displayResults(){
    gotoxy(0,0);
    for(i=0;i<=19;i++) {
        for(j=0;j<=60;j++)
            if(field[j][i]==0)
                printf(" ");
            else if(field[j][i]==1)
                printf("#");
            else
                printf("0");
        printf("\n");
    }
}
void gameOver(){
        while(!snake.empty())
            snake.pop();
        displayResults();
        gotoxy(20,20);
        printf("GAME OVER\n");
        system("PAUSE");
}
int main(){
    srand(time(NULL));
    while(1){
        initGame();
        eatThis();
        while(1){
            moveBody();
            x+=dx;
            y+=dy;
            if((x==maxX)||(x==0)) dx= -dx;
            if((y==maxY)||(y==0)) dy= -dy;
            if(field[x][y]==2){
                gameOver();
                break;
            }
            if(field[x][y]==1)
                eatThis();
            field[x][y]=2;
            gotoxy(x,y);
            printf("%c",32+x+y);
            gotoxy(0,20);
            printf("Length %d",sLen);
            Sleep(60);
        }
    }
    return 0;
}
