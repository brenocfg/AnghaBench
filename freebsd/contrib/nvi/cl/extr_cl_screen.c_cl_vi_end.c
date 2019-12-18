#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ti_te; } ;
typedef  int /*<<< orphan*/  GS ;
typedef  TYPE_1__ CL_PRIVATE ;

/* Variables and functions */
 int /*<<< orphan*/  CL_IN_EX ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  F_ISSET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* GCLP (int /*<<< orphan*/ *) ; 
 scalar_t__ LINES ; 
 int /*<<< orphan*/  TE_SENT ; 
 int /*<<< orphan*/  cl_freecap (TYPE_1__*) ; 
 int /*<<< orphan*/  deleteln () ; 
 int /*<<< orphan*/  delscreen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  endwin () ; 
 int /*<<< orphan*/  keypad (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  move (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refresh () ; 
 int /*<<< orphan*/  set_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdscr ; 

__attribute__((used)) static int
cl_vi_end(GS *gp)
{
	CL_PRIVATE *clp;

	clp = GCLP(gp);

	/* Restore the cursor keys to normal mode. */
	(void)keypad(stdscr, FALSE);

	/*
	 * If we were running vi when we quit, scroll the screen up a single
	 * line so we don't lose any information.
	 *
	 * Move to the bottom of the window (some endwin implementations don't
	 * do this for you).
	 */
	if (!F_ISSET(clp, CL_IN_EX)) {
		(void)move(0, 0);
		(void)deleteln();
		(void)move(LINES - 1, 0);
		(void)refresh();
	}

	cl_freecap(clp);

	/* End curses window. */
	(void)endwin();

	/* Free the SCREEN created by newterm(3X). */
	delscreen(set_term(NULL));

	/*
	 * XXX
	 * The screen TE sequence just got sent.  See the comment in
	 * cl_funcs.c:cl_attr().
	 */
	clp->ti_te = TE_SENT;

	return (0);
}