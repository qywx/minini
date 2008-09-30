#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "minIni.h"

#define sizearray(a)  (sizeof(a) / sizeof((a)[0]))

const char inifile[] = "test.ini";

int main(void)
{
  char str[100];
  long n;
  int s, k;
  char section[50];

  /* string reading */
  n = ini_gets("first", "string", "aap", str, sizearray(str), inifile);
  assert(n==4 && strcmp(str,"noot")==0);
  n = ini_gets("second", "string", "aap", str, sizearray(str), inifile);
  assert(n==4 && strcmp(str,"mies")==0);
  n = ini_gets("first", "dummy", "aap", str, sizearray(str), inifile);
  assert(n==3 && strcmp(str,"aap")==0);
  printf("1. String reading tests passed\n");

  /* value reading */
  n = ini_getl("first", "val", -1, inifile);
  assert(n==1);
  n = ini_getl("second", "val", -1, inifile);
  assert(n==2);
  n = ini_getl("first", "dummy", -1, inifile);
  assert(n==-1);
  printf("2. Value reading tests passed\n");

  /* string writing */
  n = ini_puts("first", "alt", "correct", inifile);
  assert(n==1);
  n = ini_gets("first", "alt", "aap", str, sizearray(str), inifile);
  assert(n==7 && strcmp(str,"correct")==0);
  /* ----- */
  n = ini_puts("second", "alt", "correct", inifile);
  assert(n==1);
  n = ini_gets("second", "alt", "aap", str, sizearray(str), inifile);
  assert(n==7 && strcmp(str,"correct")==0);
  /* ----- */
  n = ini_puts("third", "alt", "correct", inifile);
  assert(n==1);
  n = ini_gets("third", "alt", "aap", str, sizearray(str), inifile);
  assert(n==7 && strcmp(str,"correct")==0);
  /* ----- */
  printf("3. String writing tests passed\n");

  /* section/key enumeration */
  for (s = 0; ini_getsection(s, section, sizearray(section), inifile) > 0; s++) {
    printf("[%s]\n", section);
    for (k = 0; ini_getkey(section, k, str, sizearray(str), inifile) > 0; k++) {
      printf("\t%s\n", str);
    } /* for */
  } /* for */
  
  /* string deletion */
  n = ini_puts("first", "alt", NULL, inifile);
  assert(n==1);
  n = ini_puts("second", "alt", NULL, inifile);
  assert(n==1);
  n = ini_puts("third", NULL, NULL, inifile);
  assert(n==1);

  return 0;
}
