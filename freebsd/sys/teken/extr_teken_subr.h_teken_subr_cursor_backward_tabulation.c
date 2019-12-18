#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ tp_col; } ;
struct TYPE_7__ {TYPE_1__ t_cursor; } ;
typedef  TYPE_2__ teken_t ;

/* Variables and functions */
 int /*<<< orphan*/  teken_funcs_cursor (TYPE_2__*) ; 
 scalar_t__ teken_tab_isset (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static void
teken_subr_cursor_backward_tabulation(teken_t *t, unsigned int ntabs)
{

	do {
		/* Stop when we've reached the beginning of the line. */
		if (t->t_cursor.tp_col == 0)
			break;

		t->t_cursor.tp_col--;

		/* Tab marker set. */
		if (teken_tab_isset(t, t->t_cursor.tp_col))
			ntabs--;
	} while (ntabs > 0);

	teken_funcs_cursor(t);
}