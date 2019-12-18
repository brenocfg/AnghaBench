#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ tp_row; } ;
struct TYPE_8__ {scalar_t__ ts_begin; scalar_t__ ts_end; } ;
struct TYPE_7__ {scalar_t__ tp_row; } ;
struct TYPE_10__ {size_t t_curscs; TYPE_3__ t_winsize; TYPE_2__ t_originreg; int /*<<< orphan*/  t_stateflags; TYPE_1__ t_cursor; int /*<<< orphan*/  t_saved_curscs; int /*<<< orphan*/ * t_scs; int /*<<< orphan*/  t_saved_curattr; int /*<<< orphan*/  t_curattr; TYPE_1__ t_saved_cursor; } ;
typedef  TYPE_4__ teken_t ;

/* Variables and functions */
 int /*<<< orphan*/  TS_ORIGIN ; 
 int /*<<< orphan*/  TS_WRAPPED ; 
 int /*<<< orphan*/  teken_funcs_cursor (TYPE_4__*) ; 

__attribute__((used)) static void
teken_subr_restore_cursor(teken_t *t)
{

	t->t_cursor = t->t_saved_cursor;
	t->t_curattr = t->t_saved_curattr;
	t->t_scs[t->t_curscs] = t->t_saved_curscs;
	t->t_stateflags &= ~TS_WRAPPED;

	/* Get out of origin mode when the cursor is moved outside. */
	if (t->t_cursor.tp_row < t->t_originreg.ts_begin ||
	    t->t_cursor.tp_row >= t->t_originreg.ts_end) {
		t->t_stateflags &= ~TS_ORIGIN;
		t->t_originreg.ts_begin = 0;
		t->t_originreg.ts_end = t->t_winsize.tp_row;
	}

	teken_funcs_cursor(t);
}