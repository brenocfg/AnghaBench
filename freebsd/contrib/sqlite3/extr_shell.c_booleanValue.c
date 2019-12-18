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

/* Variables and functions */
 scalar_t__ hexDigitValue (char const) ; 
 int integerValue (char const*) ; 
 scalar_t__ sqlite3_stricmp (char const*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  utf8_printf (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static int booleanValue(const char *zArg){
  int i;
  if( zArg[0]=='0' && zArg[1]=='x' ){
    for(i=2; hexDigitValue(zArg[i])>=0; i++){}
  }else{
    for(i=0; zArg[i]>='0' && zArg[i]<='9'; i++){}
  }
  if( i>0 && zArg[i]==0 ) return (int)(integerValue(zArg) & 0xffffffff);
  if( sqlite3_stricmp(zArg, "on")==0 || sqlite3_stricmp(zArg,"yes")==0 ){
    return 1;
  }
  if( sqlite3_stricmp(zArg, "off")==0 || sqlite3_stricmp(zArg,"no")==0 ){
    return 0;
  }
  utf8_printf(stderr, "ERROR: Not a boolean value: \"%s\". Assuming \"no\".\n",
          zArg);
  return 0;
}