#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char const* nullValue; char const* colSeparator; int /*<<< orphan*/ * out; } ;
typedef  TYPE_1__ ShellState ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ memcmp (char const*,char const*,int) ; 
 scalar_t__* needCsvQuote ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,char const*) ; 
 int strlen30 (char const*) ; 
 int /*<<< orphan*/  utf8_printf (int /*<<< orphan*/ *,char*,char const*) ; 

__attribute__((used)) static void output_csv(ShellState *p, const char *z, int bSep){
  FILE *out = p->out;
  if( z==0 ){
    utf8_printf(out,"%s",p->nullValue);
  }else{
    int i;
    int nSep = strlen30(p->colSeparator);
    for(i=0; z[i]; i++){
      if( needCsvQuote[((unsigned char*)z)[i]]
         || (z[i]==p->colSeparator[0] &&
             (nSep==1 || memcmp(z, p->colSeparator, nSep)==0)) ){
        i = 0;
        break;
      }
    }
    if( i==0 ){
      char *zQuoted = sqlite3_mprintf("\"%w\"", z);
      utf8_printf(out, "%s", zQuoted);
      sqlite3_free(zQuoted);
    }else{
      utf8_printf(out, "%s", z);
    }
  }
  if( bSep ){
    utf8_printf(p->out, "%s", p->colSeparator);
  }
}