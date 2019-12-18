#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  WINDOW ;
typedef  int /*<<< orphan*/  SCR ;
typedef  int /*<<< orphan*/  CL_PRIVATE ;

/* Variables and functions */
 int /*<<< orphan*/  A_NORMAL ; 
 int /*<<< orphan*/ * CLP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CLSP (int /*<<< orphan*/ *) ; 
 scalar_t__ ERR ; 
 int /*<<< orphan*/  F_ISSET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_SPLIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LASTLINE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RLNO (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_SCR_EXWROTE ; 
 int /*<<< orphan*/  getyx (int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/  mvwchgat (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stdscr ; 
 scalar_t__ wdeleteln (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,size_t,size_t) ; 

int
cl_deleteln(SCR *sp)
{
	CL_PRIVATE *clp;
	WINDOW *win;
	size_t y, x;

	clp = CLP(sp);
	win = CLSP(sp) ? CLSP(sp) : stdscr;

	/*
	 * This clause is required because the curses screen uses reverse
	 * video to delimit split screens.  If the screen does not do this,
	 * this code won't be necessary.
	 *
	 * If the bottom line was in reverse video, rewrite it in normal
	 * video before it's scrolled.
	 */
	if (!F_ISSET(sp, SC_SCR_EXWROTE) && IS_SPLIT(sp)) {
		getyx(win, y, x);
		mvwchgat(win, RLNO(sp, LASTLINE(sp)), 0, -1, A_NORMAL, 0, NULL);
		(void)wmove(win, y, x);
	}

	/*
	 * The bottom line is expected to be blank after this operation,
	 * and other screens must support that semantic.
	 */
	return (wdeleteln(win) == ERR);
}