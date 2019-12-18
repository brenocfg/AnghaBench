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
 int /*<<< orphan*/  raw_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  setBinaryMode (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  setTextMode (int /*<<< orphan*/ *,int) ; 
 char* unused_string (char const*,char*,char*,char*) ; 
 int /*<<< orphan*/  utf8_printf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void output_quoted_escaped_string(FILE *out, const char *z){
  int i;
  char c;
  setBinaryMode(out, 1);
  for(i=0; (c = z[i])!=0 && c!='\'' && c!='\n' && c!='\r'; i++){}
  if( c==0 ){
    utf8_printf(out,"'%s'",z);
  }else{
    const char *zNL = 0;
    const char *zCR = 0;
    int nNL = 0;
    int nCR = 0;
    char zBuf1[20], zBuf2[20];
    for(i=0; z[i]; i++){
      if( z[i]=='\n' ) nNL++;
      if( z[i]=='\r' ) nCR++;
    }
    if( nNL ){
      raw_printf(out, "replace(");
      zNL = unused_string(z, "\\n", "\\012", zBuf1);
    }
    if( nCR ){
      raw_printf(out, "replace(");
      zCR = unused_string(z, "\\r", "\\015", zBuf2);
    }
    raw_printf(out, "'");
    while( *z ){
      for(i=0; (c = z[i])!=0 && c!='\n' && c!='\r' && c!='\''; i++){}
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
      if( c=='\n' ){
        raw_printf(out, "%s", zNL);
        continue;
      }
      raw_printf(out, "%s", zCR);
    }
    raw_printf(out, "'");
    if( nCR ){
      raw_printf(out, ",'%s',char(13))", zCR);
    }
    if( nNL ){
      raw_printf(out, ",'%s',char(10))", zNL);
    }
  }
  setTextMode(out, 1);
}