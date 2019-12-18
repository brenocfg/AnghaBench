#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ ts_end; } ;
struct TYPE_7__ {scalar_t__ tp_row; } ;
struct TYPE_9__ {int /*<<< orphan*/  t_stateflags; TYPE_2__ t_scrollreg; TYPE_1__ t_cursor; } ;
typedef  TYPE_3__ teken_t ;

/* Variables and functions */
 int /*<<< orphan*/  TS_WRAPPED ; 
 int /*<<< orphan*/  teken_funcs_cursor (TYPE_3__*) ; 
 int /*<<< orphan*/  teken_subr_do_scroll (TYPE_3__*,int) ; 

__attribute__((used)) static void
teken_subr_newline(teken_t *t)
{

	t->t_cursor.tp_row++;

	if (t->t_cursor.tp_row >= t->t_scrollreg.ts_end) {
		teken_subr_do_scroll(t, 1);
		t->t_cursor.tp_row = t->t_scrollreg.ts_end - 1;
	}

	t->t_stateflags &= ~TS_WRAPPED;
	teken_funcs_cursor(t);
}