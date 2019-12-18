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
struct TYPE_9__ {unsigned int tp_row; scalar_t__ tp_col; } ;
struct TYPE_8__ {unsigned int ts_begin; unsigned int ts_end; } ;
struct TYPE_7__ {unsigned int tp_row; } ;
struct TYPE_10__ {int t_stateflags; TYPE_3__ t_cursor; TYPE_2__ t_originreg; TYPE_2__ t_scrollreg; TYPE_1__ t_winsize; } ;
typedef  TYPE_4__ teken_t ;

/* Variables and functions */
 int TS_ORIGIN ; 
 int TS_WRAPPED ; 
 int /*<<< orphan*/  teken_funcs_cursor (TYPE_4__*) ; 

__attribute__((used)) static void
teken_subr_set_top_and_bottom_margins(teken_t *t, unsigned int top,
    unsigned int bottom)
{

	/* Adjust top row number. */
	if (top > 0)
		top--;
	/* Adjust bottom row number. */
	if (bottom == 0 || bottom > t->t_winsize.tp_row)
		bottom = t->t_winsize.tp_row;

	/* Invalid arguments. */
	if (top >= bottom - 1) {
		top = 0;
		bottom = t->t_winsize.tp_row;
	}

	/* Apply scrolling region. */
	t->t_scrollreg.ts_begin = top;
	t->t_scrollreg.ts_end = bottom;
	if (t->t_stateflags & TS_ORIGIN)
		t->t_originreg = t->t_scrollreg;

	/* Home cursor to the top left of the scrolling region. */
	t->t_cursor.tp_row = t->t_originreg.ts_begin;
	t->t_cursor.tp_col = 0;
	t->t_stateflags &= ~TS_WRAPPED;
	teken_funcs_cursor(t);
}