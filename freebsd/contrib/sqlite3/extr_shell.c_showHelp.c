#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ArraySize (char**) ; 
 char** azHelp ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,char const*) ; 
 scalar_t__ sqlite3_strglob (char*,char*) ; 
 scalar_t__ sqlite3_strlike (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  utf8_printf (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static int showHelp(FILE *out, const char *zPattern){
  int i = 0;
  int j = 0;
  int n = 0;
  char *zPat;
  if( zPattern==0
   || zPattern[0]=='0'
   || strcmp(zPattern,"-a")==0
   || strcmp(zPattern,"-all")==0
  ){
    /* Show all commands, but only one line per command */
    if( zPattern==0 ) zPattern = "";
    for(i=0; i<ArraySize(azHelp); i++){
      if( azHelp[i][0]=='.' || zPattern[0] ){
        utf8_printf(out, "%s\n", azHelp[i]);
        n++;
      }
    }
  }else{
    /* Look for commands that for which zPattern is an exact prefix */
    zPat = sqlite3_mprintf(".%s*", zPattern);
    for(i=0; i<ArraySize(azHelp); i++){
      if( sqlite3_strglob(zPat, azHelp[i])==0 ){
        utf8_printf(out, "%s\n", azHelp[i]);
        j = i+1;
        n++;
      }
    }
    sqlite3_free(zPat);
    if( n ){
      if( n==1 ){
        /* when zPattern is a prefix of exactly one command, then include the
        ** details of that command, which should begin at offset j */
        while( j<ArraySize(azHelp)-1 && azHelp[j][0]!='.' ){
          utf8_printf(out, "%s\n", azHelp[j]);
          j++;
        }
      }
      return n;
    }
    /* Look for commands that contain zPattern anywhere.  Show the complete
    ** text of all commands that match. */
    zPat = sqlite3_mprintf("%%%s%%", zPattern);
    for(i=0; i<ArraySize(azHelp); i++){
      if( azHelp[i][0]=='.' ) j = i;
      if( sqlite3_strlike(zPat, azHelp[i], 0)==0 ){
        utf8_printf(out, "%s\n", azHelp[j]);
        while( j<ArraySize(azHelp)-1 && azHelp[j+1][0]!='.' ){
          j++;
          utf8_printf(out, "%s\n", azHelp[j]);
        }
        i = j;
        n++;
      }
    }
    sqlite3_free(zPat);
  }
  return n;
}