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
typedef  int /*<<< orphan*/  zBuf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  utf8_printf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void utf8_width_print(FILE *pOut, int w, const char *zUtf){
  int i;
  int n;
  int aw = w<0 ? -w : w;
  char zBuf[1000];
  if( aw>(int)sizeof(zBuf)/3 ) aw = (int)sizeof(zBuf)/3;
  for(i=n=0; zUtf[i]; i++){
    if( (zUtf[i]&0xc0)!=0x80 ){
      n++;
      if( n==aw ){
        do{ i++; }while( (zUtf[i]&0xc0)==0x80 );
        break;
      }
    }
  }
  if( n>=aw ){
    utf8_printf(pOut, "%.*s", i, zUtf);
  }else if( w<0 ){
    utf8_printf(pOut, "%*s%s", aw-n, "", zUtf);
  }else{
    utf8_printf(pOut, "%s%*s", zUtf, aw-n, "");
  }
}