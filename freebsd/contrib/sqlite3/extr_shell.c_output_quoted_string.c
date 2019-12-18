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
 int /*<<< orphan*/  raw_printf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  setBinaryMode (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  setTextMode (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  utf8_printf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void output_quoted_string(FILE *out, const char *z){
  int i;
  char c;
  setBinaryMode(out, 1);
  for(i=0; (c = z[i])!=0 && c!='\''; i++){}
  if( c==0 ){
    utf8_printf(out,"'%s'",z);
  }else{
    raw_printf(out, "'");
    while( *z ){
      for(i=0; (c = z[i])!=0 && c!='\''; i++){}
      if( c=='\'' ) i++;
      if( i ){
        utf8_printf(out, "%.*s", i, z);
        z += i;
      }
      if( c=='\'' ){
        raw_printf(out, "'");
        continue;
      }
      if( c==0 ){
        break;
      }
      z++;
    }
    raw_printf(out, "'");
  }
  setTextMode(out, 1);
}