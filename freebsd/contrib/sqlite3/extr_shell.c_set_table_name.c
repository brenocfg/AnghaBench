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
struct TYPE_3__ {char* zDestTable; } ;
typedef  TYPE_1__ ShellState ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 char quoteChar (char const*) ; 
 int /*<<< orphan*/  shell_out_of_memory () ; 
 int strlen30 (char const*) ; 

__attribute__((used)) static void set_table_name(ShellState *p, const char *zName){
  int i, n;
  char cQuote;
  char *z;

  if( p->zDestTable ){
    free(p->zDestTable);
    p->zDestTable = 0;
  }
  if( zName==0 ) return;
  cQuote = quoteChar(zName);
  n = strlen30(zName);
  if( cQuote ) n += n+2;
  z = p->zDestTable = malloc( n+1 );
  if( z==0 ) shell_out_of_memory();
  n = 0;
  if( cQuote ) z[n++] = cQuote;
  for(i=0; zName[i]; i++){
    z[n++] = zName[i];
    if( zName[i]==cQuote ) z[n++] = cQuote;
  }
  if( cQuote ) z[n++] = cQuote;
  z[n] = 0;
}