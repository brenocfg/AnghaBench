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
struct TYPE_3__ {scalar_t__ iIndent; scalar_t__ nIndent; scalar_t__ aiIndent; } ;
typedef  TYPE_1__ ShellState ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3_free (scalar_t__) ; 

__attribute__((used)) static void explain_data_delete(ShellState *p){
  sqlite3_free(p->aiIndent);
  p->aiIndent = 0;
  p->nIndent = 0;
  p->iIndent = 0;
}