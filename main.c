#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define earliestTime 5
#define latestTime 23
#define maxAPlace 16
#define maxSPlace 10
int skipday(int day, int month, int year);
int numberOfDays(int monthNumber, int year);
int printCalendar(int month,int year);
void getMonth(int mo,char month[]);
int chooseCovidType();
void chooseStartingDate(int date[]);
int checkPlace(int,int[maxSPlace][6]);
int checkTime(int,int);
int schedulePlace(int schedule[maxSPlace][6]);
void visit(int,int[maxSPlace][6],int[],int);
int chooseMask(int[maxSPlace][6],int);
int randomPeopleNo(int[2],int,int,int);
int randomPeopleNo2(int,int,int,int);
int randomPeopleNo3(int,int,int);
int randomPeopleNo4(int);
double approximatePossibility(int,int,int);
double approximatePossibility2(int);
int calculateSpreading(float,int);
int schedule[maxSPlace][6];
int date[2];
int virusStrength;
unsigned long int infected;
//File check
checkfile(){
  FILE *fp;
  if ((fp=fopen("places.dat","r"))==NULL) {
    puts("ERROR: File(s) missing");
    exit(1);
  }
  fclose(fp);
}
//Main
int main(void) {
  checkfile();
  system("clear");
  introduction();
  system("clear");
  virusStrength = chooseCovidType();
  system("clear");
  chooseStartingDate(date);
  system("clear");
  int round = schedulePlace(schedule);
  system("clear");
  printf("Planning successful!\n\nYou will be visiting %d places\n\n\n\n",round);
  puts("Type any character to continue... \n");
  scanf(" %c");
  for(int i=0;i<round;i++){
    system("clear");
    visit(i,schedule,date,virusStrength);
    printf("\nVisited place: %d \n",schedule[i][0]);
  }
  puts("\nTraveling done !\n");
  puts("Type any character to continue... \n");
  scanf(" %c");
  system("clear");
  printf("ENDING RESULT:\n");
  showResult(schedule,round,virusStrength);
  printf("Game end");
  return 0;
}
//Game introduction
void introduction(){
  printf("*****How much can you spread covid-19 in 2021*****\n");
  printf("                  Welcome\n");
  printf("\n\n");
  printf("This game is intended to show you, how dangerous is \nwhen you are infected with covid-19 and go out in public.\n");
  printf("You should not go outside your quaranteen place when you have covid-19,\nand you should see doctor if you have sign of covid-19.\nMore info on Google.\n");
  printf("\n");
  printf("Press any key to continue..");
  getchar();
  system("clear");
  printf("At the begining of the game:\n");
  printf("You will choose the type of covid-19 infection you will get then\n");
  printf("You will schedule places and time to visit\n");
  printf("\n");
  printf("While playing the game:\n");
  printf("Each time you visting place you have scheduled, \nyou will choose the type of mask\n");
  printf("The number of people you will met will be \nrandomize based on time, place, date\n");
  printf("\n");
  printf("At the end of the game:\n");
  printf("We will show the number of people got infected both \ndirectly and indirectly from you\n");
  printf("\n\n");
  printf("Shall we start?");
  printf("\n\n");
  printf("Press any key to continue..");
  getchar();
  printf("\n");
  return 0;
}
//Game setup
int skipday(int day, int month, int year){
  static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
  year -= month < 3;
  return (year + year / 4 - year / 100 + year / 400 + t[month] + day)% 7;
}
int numberOfDays(int monthNumber, int year){//calculate for number of day of years (compensate Feb)
  if (monthNumber == 0) return (31);
    if (monthNumber == 1) {
      if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) return (29);
      else return (28);
    }
  if (monthNumber == 2) return (31);
  if (monthNumber == 3) return (30);
  if (monthNumber == 4) return (31);
  if (monthNumber == 5) return (30);
  if (monthNumber == 6) return (31);
  if (monthNumber == 7) return (31);
  if (monthNumber == 8) return (30);
  if (monthNumber == 9) return (31);
  if (monthNumber == 10) return (30);
  if (monthNumber == 11) return (31);
  else return 0;
}
int printCalendar(int month,int year){
  int days,k;
  int current = skipday(1, month, year);
  days = numberOfDays(month, year);
  printf(" Sun   Mon  Tue  Wed  Thu  Fri  Sat\n");//first column
  for (k = 0; k < current; k++) printf("     ");//skip empty date
  for (int j = 1; j <= days; j++) {//print each date
    printf("%5d", j);
    if (++k > 6) {
      k = 0;
      printf("\n");
    }
  }
  return current;
}

void getMonth(int mo,char month[]){
    switch (mo) {
    case 0:strcpy(month,"January");break;
    case 1:strcpy(month,"February");break;
    case 2:strcpy(month,"March");break;
    case 3:strcpy(month,"April");break;
    case 4:strcpy(month,"May");break;
    case 5:strcpy(month,"June");break;
    case 6:strcpy(month,"July");break;
    case 7:strcpy(month,"August");break;
    case 8:strcpy(month,"September");break;
    case 9:strcpy(month,"October");break;
    case 10:strcpy(month,"November");break;
    case 11:strcpy(month,"December");break;}
}
int chooseCovidType(){//Ask user to enter covid type (researched)
  printf("--Choose the type of covid-19 you want to get--\n");
  int a,strength[]={100,150,170,250,210,350};
  printf("%14s%15s%10s\n","Type","Nationality","Strength");
  printf("%2d%11s%15s%9d%c\n",0,"Origin","China",strength[0],'%');
  printf("%2d%11s%15s%9d%c\n",1,"Beta","South Africa",strength[1],'%');
  printf("%2d%11s%15s%9d%c\n",2,"Alpha","UK",strength[2],'%');
  printf("%2d%11s%15s%9d%c\n",3,"Gamma","Brazil",strength[3],'%');
  printf("%2d%11s%15s%9d%c\n",4,"Delta","India",strength[4],'%');
  printf("%2d%11s%15s%9d%c\n",5,"Epsilon","USA",strength[5],'%');
  do{
    printf("Choose your type 0 - 5: ");
    scanf("%d",&a); 
    if(a<0||a>5){
      printf("There is no such type\n");
    }
  }while((a<0||a>5));
  return strength[a-1];//(return as 100 - 350 to var: virusStrength) 
}
void chooseStartingDate(int date[]){//Ask user to choose date wish to start
  printf("--Choose the day you want to play--\n");
  printf("Day is depending on current month\n");
  time_t current_time;
  struct tm strk;
  time(&current_time);
  localtime_r(&current_time, &strk);//obtain current date and time
  char month[10];
  getMonth(strk.tm_mon,month);//monthNum to monthName
  printf("This month: %s %d\n\n",month,(strk.tm_year + 1900));
  int dayskip = printCalendar(strk.tm_mon,(strk.tm_year + 1900))-1;
  int a;//Ask date from user
  do{
    printf("Choose date: ");
    scanf("%d",&a);
    if(a>0 && a<numberOfDays(strk.tm_mon, (strk.tm_year + 1900))+1) printf("invalid date\n");
  }while(!(a>0 && a<numberOfDays(strk.tm_mon, (strk.tm_year + 1900))+1));//prevent enter number out of range based on month
  date[0] = (dayskip+a)%7;//Sunday=0 , Sat=6
  if(a< 5){//date of month to period of month (Early Mid Late)
    date[1] = 0;
  }else if(a> 27){
    date[1] = 2;
  }else{
    date[1] = 1;
  }
}//date[0] is date, date[1] define: early month(0) mid month(1) late month(2)
int schedulePlace(int schedule[maxSPlace][6]){//Ask user to enter places to visit (MAX 10 places)
  int list[maxAPlace];

  FILE *fp;
  fp=fopen("places.dat","r");
  //List place from file "places.dat" and set "type of place" to array
  int account,type;
  char name[15],activity[10];
  printf("%5s%13s%13s\n","No.","Place","Activity");//print top row
  for(int i=0;i<maxAPlace;i++){
    fscanf(fp,"%d %s %s %d",&account,name,activity,&type);
    list[i]=type;//copy "type of place" to array for later calculation
    printf("%5d%13s%13s\n",account,name,activity);
  }
  fclose(fp);
  //Ask for input
  int a,b,c,stops=1;
  //Ask for 1st place (separated from loop for different printing message)
  do{
    printf("Choose place no.1 : ");
    scanf("%d",&a);
  }while(!(checkPlace(a,schedule) == 0 || a==0));
  do{
  printf("Choose starting time of place no.1 (5 - 23): ");
  scanf("%d",&b);
  }while(checkTime(b,23)==0);
  do{
    printf("Choose ending time of place no.1 (5 - 23): ");
    scanf("%d",&c);
  }while(checkTime(b,c)==0);
  schedule[0][0] = a;
  schedule[0][1] = list[a-1];
  schedule[0][2] = b;
  schedule[0][3] = c;

  //Ask for 9 other places
  for(int i=1;i<=maxSPlace;i++){
    do{
      printf("Choose place no.%d (0 for no more places) : ",i+1);
      scanf("%d",&a);
    }while(!(checkPlace(a,schedule) == 0 || a==0));
    if(a==0) break;
    printf("*time can be overlaps\n");
    do{
      printf("Choose starting time no.%d (5 - 23) : ",i+1);
      scanf("%d",&b);
    }while(checkTime(b,23)==0);//(23 for dummy) check if time is in range
    do{
      printf("Choose ending time no.%d (5 - 23) : ",i+1);
      scanf("%d",&c);
    }while(checkTime(b,c)==0);//check if time is in range and later than starting time
    schedule[i][0] = a;           //no. of place
    schedule[i][1] = list[a-1];   //type of place
    schedule[i][2] = b;           //starting time
    schedule[i][3] = c;           //ending time
    stops++;//count of how many places will player visit
  }
  return stops;
}
int checkTime(int time,int timeB){//extention of schedulePlace: check if user input time valid
  if(time<earliestTime){
    printf("The place is not opened yet at your specify time\n");
    return 0;
  }else if(time>latestTime){
    printf("The place will be close before you even finished\n");
    return 0;
  }else{
    if(time>timeB){
      printf("It is not possible to finish before start\n");
      return 0;
    }else return 1;
  }
}
int checkPlace(int a,int schedule[maxSPlace][6]){
  int dup = 0;
  if(a < 0){
    dup = 1;
    printf("Place doesn't exist\n");
  }else if(a > maxAPlace){
    dup = 1;
    printf("Place doesn't exist\n");
  }
  for(int i=0;i<=maxSPlace;i++){
    if(schedule[i][0] == a){
      dup = 1;
      printf("Place duplicated\n");
    }
  }
  return dup;
}
//In Game
void visit(int place,int schedule[maxSPlace][6],int date[],int strength){
  schedule[place][4] = randomPeopleNo(date,schedule[place][1],schedule[place][2],schedule[place][3]);
  schedule[place][5] = calculateSpreading(approximatePossibility(chooseMask(schedule,place),schedule[place][1],strength),schedule[place][4]);
  printf("\nVisiting....");
}
int randomPeopleNo(int date[2],int type,int start,int end){
  srand(time(NULL));
  if(date[1] == 0){//Early month
    return randomPeopleNo2(date[0],type,start,end)*(rand()%400+700)*0.001;
  }else if(date[1] == 1){//mid month
    return randomPeopleNo2(date[0],type,start,end)*(rand()%600+300)*0.001;
  }else if(date[1] == 2){//late month
    return randomPeopleNo2(date[0],type,start,end)*(rand()%700+350)*0.001;
  }else{
    return 0;
  }
}
int randomPeopleNo2(int date,int type,int start,int end){//extention level 1 for randomPeopleNo
  srand(time(NULL));
  switch(date){
    case 0: return randomPeopleNo3(start,end,type)*(rand()%400+600)*0.001;break;//sunday
    case 1: return randomPeopleNo3(start,end,type)*(rand()%400+100)*0.001;break;//Monday
    case 2: return randomPeopleNo3(start,end,type)*(rand()%500+100)*0.001;break;
    case 3: return randomPeopleNo3(start,end,type)*(rand()%400+200)*0.001;break;
    case 4: return randomPeopleNo3(start,end,type)*(rand()%500+700)*0.001;break;
    case 5: return randomPeopleNo3(start,end,type)*(rand()%600+300)*0.001;break;//Friday
    case 6: return randomPeopleNo3(start,end,type)*(rand()%550+550)*0.001;break;//Saturday
    default:return 0;
  }
}
int randomPeopleNo3(int start,int end,int type){//extention level 2 for randomPeopleNo
  srand(time(NULL));
  int people = 0;
  for(int i=start;i<end;i++){
    switch(i){
      case 5: people+= randomPeopleNo4(type)*(rand()%50+1)*0.001;break;
      case 6: people+= randomPeopleNo4(type)*(rand()%100+10)*0.001;break;
      case 7: people+= randomPeopleNo4(type)*(rand()%200+50)*0.001;break;
      case 8: people+= randomPeopleNo4(type)*(rand()%500+100)*0.001;break;
      case 9: people+= randomPeopleNo4(type)*(rand()%400+200)*0.001;break;
      case 10: people+= randomPeopleNo4(type)*(rand()%400+400)*0.001;break;
      case 11: people+= randomPeopleNo4(type)*(rand()%500+500)*0.001;break;
      case 12: people+= randomPeopleNo4(type)*(rand()%400+700)*0.001;break;
      case 13: people+= randomPeopleNo4(type)*(rand()%400+700)*0.001;break;
      case 14: people+= randomPeopleNo4(type)*(rand()%400+600)*0.001;break;
      case 15: people+= randomPeopleNo4(type)*(rand()%400+600)*0.001;break;
      case 16: people+= randomPeopleNo4(type)*(rand()%200+800)*0.001;break;
      case 17: people+= randomPeopleNo4(type)*(rand()%300+700)*0.001;break;
      case 18: people+= randomPeopleNo4(type)*(rand()%200+700)*0.001;break;
      case 19: people+= randomPeopleNo4(type)*(rand()%100+800)*0.001;break;
      case 20: people+= randomPeopleNo4(type)*(rand()%300+700)*0.001;break;
      case 21: people+= randomPeopleNo4(type)*(rand()%400+20)*0.001;break;
      case 22: people+= randomPeopleNo4(type)*(rand()%200+20)*0.001;break;
      case 23: people+= randomPeopleNo4(type)*(rand()%100+10)*0.001;break;
      default:people+= 0;
    }
    return people;
  }
}
int randomPeopleNo4(int type){//extention level 3 for randomPeopleNo
  srand(time(NULL));
  switch(type){
    case 11:{//outdoor eating
      return (rand()%5000+75);
    }break;
    case 12:{//malls shopping
      return (rand()%15000+300);
    }break;
    case 13:{//Indoor sport
      return (rand()%200+100);
    }break;
    case 14:{//Indoor movie
      return (rand()%300+500);
    }break;
    case 15:{//Indoor study
      return (rand()%100+260);
    }break;
    case 16:{//Indoor game
      return (rand()%500+800);
    }break;
    case 21:{//indoor concert
      return (rand()%10000+3000);
    }break;
    case 22:{//hospital
      return (rand()%20000+210);
    }break;
    case 23:{//beach
      return (rand()%500+300);
    }break;
    case 24:{//mountain
      return (rand()%300+150);
    }break;
    case 25:{//cafe
      return (rand()%200+490);
    }break;
    case 26:{//museum
      return (rand()%700+200);
    }break;
    case 27:{ // outdoor park
      return (rand()%300+80); //change number
    }break;
    case 28:{ //market
      return (rand()%300+600);
    }break;
    case 29:{ //pub
      return (rand()%300+1000);
    }break;
    case 30:{ //temple
      return (rand()%300+190);
    }break;
    default: return 0;
  }
}
int chooseMask(int schedule[maxSPlace][6],int place){//(0-6) 6 for gemmic 
  int a;
  printf("Choose type of mask you are going to wear at place %d: \n",schedule[place][0]);
  puts("0 for no mask");
  puts("1 for tissue paper");
  puts("2 for cheaply made mask");
  puts("3 for well insulated mask");
  puts("4 for 3d mask specifically designed for covid-19 situation");
  puts("5 for N95 mask with exhaust vavle");
  puts("6 for oxygen tank");
  printf("Mask number: ");
  scanf("%d",&a);

  if(a<0||a>6){
  do{
    printf("There is no type of mask you are looking for!\n\n");
    printf("Mask number: ");
    scanf("%d",&a);
  }while (a<0||a>6);
  }
  return a; 
}
double approximatePossibility(int mask,int type,int strength){
  switch(mask){
    case 0: return approximatePossibility2(type)*1.00*(strength*0.001)*2;break;
    case 1: return approximatePossibility2(type)*0.99*(strength*0.001)*2;break;
    case 2: return approximatePossibility2(type)*0.8*(strength*0.001)*2;break;
    case 3: return approximatePossibility2(type)*0.2*(strength*0.001)*2;break;
    case 4: return approximatePossibility2(type)*0.1*(strength*0.001)*2;break;
    case 5: return approximatePossibility2(type)*0.05*(strength*0.001)*2;break;
    case 6: return approximatePossibility2(type)*0.01*(strength*0.001)*2;break;
    default:return 0;
  }
}
double approximatePossibility2(int type){
  switch(type){
    case 11:{//Indoor eating
      return 1;
    }break;
    case 12:{//Indoor shopping
      return 0.35;
    }break;
    case 13:{//Indoor watch moive
      return 0.85;
    }break;
    case 14:{//Indoor study
      return 0.75;
    }break;
    case 15:{//Indoor karaoke
      return 1;
    }break;
    case 16:{//Indoor sport
      return 1;
    }break;
    case 21:{//Outdoor eating
      return 0.5;
    }break;
    case 22:{//Outdoor shopping
      return 0.1;
    }break;
    case 23:{//Outdoor watch movie
      return 0.2;
    }break;
    case 24:{//Outdoor study
      return 0.2;
    }break;
    case 25:{//Outdoor karaoke
      return 0.65;
    }break;
    case 26:{//Outdoor sport
      return 0.1;
    }break;
    case 27:{
      return 0.5; //chage the number
    }break;
    case 28:{
      return 0.5; 
    }break;
    case 29:{
      return 0.5;
    }break;
    case 30:{
      return 0.5;
    }break;
    default: return 0;
  }
}
int calculateSpreading(float possibility,int people){
  srand(time(NULL));
  return possibility*people*(rand()%90+20)*1/100; 
}
//End game
void showResult(int schedule[maxSPlace][6],int round,int virus){
  int total_infected_people=0,total_met_people=0;
  double percent;
  printf("You were infected with virus: \n");
  switch(virus){
    case 100: printf("%2d%11s%15s\n",0,"Origin","China");break;
    case 150: printf("%2d%11s%15s\n",1,"Beta","South Africa");break;
    case 170: printf("%2d%11s%15s\n",2,"Alpha","UK");break;
    case 250: printf("%2d%11s%15s\n",3,"Gamma","Brazil");break;
    case 210: printf("%2d%11s%15s\n",4,"Delta","India");break;
    case 350: printf("%2d%11s%15s\n",5,"Epsilon","USA");break;
  }
  for(int i=0 ; i<round;i++){
    total_infected_people += schedule[i][5];
    total_met_people += schedule[i][4];
  }//count
//print
  FILE *fp;
  fp=fopen("places.dat","r");
  //List place from file "places.dat" and set "type of place" to array
  int account,type;
  char name[15],activity[10];
  printf("You have visited:\n");
  printf("%5s%13s%13s%11s%10s\n","No.","Place","Activity","People met","Infected");//print top row
  for(int i=0;i<maxAPlace;i++){
    fscanf(fp,"%d %s %s %d",&account,name,activity,&type);
    for(int j=0;j<=maxAPlace;j++){
      if(account==schedule[j][0]){
        printf("%5d%13s%13s%11d%10d\n",account,name,activity,schedule[j][4],schedule[j][5]);
      }
    }
  }
  fclose(fp);
  printf("\n");
  percent = (total_infected_people*1.00/total_met_people*1.00)*100.00;
  printf("Total people met is %d.\n", total_met_people);
  printf("Total infected people is %d.\n", total_infected_people);
  printf("Percentage %f%c.\n", percent ,'%');
  printf("\n");

  printf("Steps to help prevent the spread of COVID-19 if you are sick:\n");//WORK ON THIS PLEASE
  puts("- Stay home");
  puts("- Avoid public transportation, ride-sharing, or taxis.");
  puts("- Seperate yourself from other people");
  puts("- Avoid sharing personal household items");
  puts("- WEAR MASK\n");
}

