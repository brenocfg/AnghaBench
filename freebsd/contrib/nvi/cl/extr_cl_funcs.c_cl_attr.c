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
typedef  int scr_attr_t ;
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_3__ {int /*<<< orphan*/ * rmso; int /*<<< orphan*/ * smso; int /*<<< orphan*/ * rmcup; int /*<<< orphan*/  ti_te; int /*<<< orphan*/ * smcup; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  TYPE_1__ CL_PRIVATE ;

/* Variables and functions */
 TYPE_1__* CLP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CLSP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  F_ISSET (int /*<<< orphan*/ *,int) ; 
#define  SA_ALTERNATE 129 
#define  SA_INVERSE 128 
 int SC_EX ; 
 int SC_SCR_EXWROTE ; 
 int /*<<< orphan*/  TE_SENT ; 
 int /*<<< orphan*/  TI_SENT ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  cl_getcap (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  cl_putchar ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/ * stdscr ; 
 int /*<<< orphan*/  tputs (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wstandend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wstandout (int /*<<< orphan*/ *) ; 

int
cl_attr(SCR *sp, scr_attr_t attribute, int on)
{
	CL_PRIVATE *clp;
	WINDOW *win;

	clp = CLP(sp);
	win = CLSP(sp) ? CLSP(sp) : stdscr;

	switch (attribute) {
	case SA_ALTERNATE:
	/*
	 * !!!
	 * There's a major layering violation here.  The problem is that the
	 * X11 xterm screen has what's known as an "alternate" screen.  Some
	 * xterm termcap/terminfo entries include sequences to switch to/from
	 * that alternate screen as part of the ti/te (smcup/rmcup) strings.
	 * Vi runs in the alternate screen, so that you are returned to the
	 * same screen contents on exit from vi that you had when you entered
	 * vi.  Further, when you run :shell, or :!date or similar ex commands,
	 * you also see the original screen contents.  This wasn't deliberate
	 * on vi's part, it's just that it historically sent terminal init/end
	 * sequences at those times, and the addition of the alternate screen
	 * sequences to the strings changed the behavior of vi.  The problem
	 * caused by this is that we don't want to switch back to the alternate
	 * screen while getting a new command from the user, when the user is
	 * continuing to enter ex commands, e.g.:
	 *
	 *	:!date				<<< switch to original screen
	 *	[Hit return to continue]	<<< prompt user to continue
	 *	:command			<<< get command from user
	 *
	 * Note that the :command input is a true vi input mode, e.g., input
	 * maps and abbreviations are being done.  So, we need to be able to
	 * switch back into the vi screen mode, without flashing the screen. 
	 *
	 * To make matters worse, the curses initscr() and endwin() calls will
	 * do this automatically -- so, this attribute isn't as controlled by
	 * the higher level screen as closely as one might like.
	 */
	if (on) {
		if (clp->ti_te != TI_SENT) {
			clp->ti_te = TI_SENT;
			if (clp->smcup == NULL)
				(void)cl_getcap(sp, "smcup", &clp->smcup);
			if (clp->smcup != NULL)
				(void)tputs(clp->smcup, 1, cl_putchar);
		}
	} else
		if (clp->ti_te != TE_SENT) {
			clp->ti_te = TE_SENT;
			if (clp->rmcup == NULL)
				(void)cl_getcap(sp, "rmcup", &clp->rmcup);
			if (clp->rmcup != NULL)
				(void)tputs(clp->rmcup, 1, cl_putchar);
			(void)fflush(stdout);
		}
		(void)fflush(stdout);
		break;
	case SA_INVERSE:
		if (F_ISSET(sp, SC_EX | SC_SCR_EXWROTE)) {
			if (clp->smso == NULL)
				return (1);
			if (on)
				(void)tputs(clp->smso, 1, cl_putchar);
			else
				(void)tputs(clp->rmso, 1, cl_putchar);
			(void)fflush(stdout);
		} else {
			if (on)
				(void)wstandout(win);
			else
				(void)wstandend(win);
		}
		break;
	default:
		abort();
	}
	return (0);
}