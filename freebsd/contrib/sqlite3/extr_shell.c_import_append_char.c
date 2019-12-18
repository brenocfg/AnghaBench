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
struct TYPE_3__ {scalar_t__ n; scalar_t__ nAlloc; char* z; } ;
typedef  TYPE_1__ ImportCtx ;

/* Variables and functions */
 int /*<<< orphan*/  shell_out_of_memory () ; 
 char* sqlite3_realloc64 (char*,scalar_t__) ; 

__attribute__((used)) static void import_append_char(ImportCtx *p, int c){
  if( p->n+1>=p->nAlloc ){
    p->nAlloc += p->nAlloc + 100;
    p->z = sqlite3_realloc64(p->z, p->nAlloc);
    if( p->z==0 ) shell_out_of_memory();
  }
  p->z[p->n++] = (char)c;
}