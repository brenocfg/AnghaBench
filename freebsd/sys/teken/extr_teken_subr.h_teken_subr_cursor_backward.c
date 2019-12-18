#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int tp_col; } ;
struct TYPE_6__ {int /*<<< orphan*/  t_stateflags; TYPE_1__ t_cursor; } ;
typedef  TYPE_2__ teken_t ;

/* Variables and functions */
 int /*<<< orphan*/  TS_WRAPPED ; 
 int /*<<< orphan*/  teken_funcs_cursor (TYPE_2__*) ; 

__attribute__((used)) static void
teken_subr_cursor_backward(teken_t *t, unsigned int ncols)
{

	if (ncols > t->t_cursor.tp_col)
		t->t_cursor.tp_col = 0;
	else
		t->t_cursor.tp_col -= ncols;
	t->t_stateflags &= ~TS_WRAPPED;
	teken_funcs_cursor(t);
}