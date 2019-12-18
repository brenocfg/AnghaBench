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
struct TYPE_3__ {scalar_t__ zTempFile; scalar_t__ doXdgOpen; } ;
typedef  TYPE_1__ ShellState ;

/* Variables and functions */
 scalar_t__ shellDeleteFile (scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_free (scalar_t__) ; 

__attribute__((used)) static void clearTempFile(ShellState *p){
  if( p->zTempFile==0 ) return;
  if( p->doXdgOpen ) return;
  if( shellDeleteFile(p->zTempFile) ) return;
  sqlite3_free(p->zTempFile);
  p->zTempFile = 0;
}