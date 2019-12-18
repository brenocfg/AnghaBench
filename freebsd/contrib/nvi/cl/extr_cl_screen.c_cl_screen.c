#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_17__ {int /*<<< orphan*/ * cup; int /*<<< orphan*/  rows; struct TYPE_17__* gp; } ;
typedef  TYPE_1__ SCR ;
typedef  TYPE_1__ GS ;
typedef  TYPE_1__ CL_PRIVATE ;

/* Variables and functions */
 TYPE_1__* CLP (TYPE_1__*) ; 
 int /*<<< orphan*/ * CLSP (TYPE_1__*) ; 
 int CL_IN_EX ; 
 int CL_SCR_EX_INIT ; 
 int CL_SCR_VI_INIT ; 
 int /*<<< orphan*/  F_CLR (TYPE_1__*,int) ; 
 scalar_t__ F_ISSET (TYPE_1__*,int) ; 
 int /*<<< orphan*/  F_SET (TYPE_1__*,int) ; 
 int G_SRESTART ; 
 scalar_t__ LF_ISSET (int) ; 
 int /*<<< orphan*/  O_COLUMNS ; 
 int /*<<< orphan*/  O_LINES ; 
 scalar_t__ O_VAL (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ RLNO (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int SC_EX ; 
 int SC_SCR_EX ; 
 int SC_SCR_VI ; 
 int SC_VI ; 
 int /*<<< orphan*/ * TAILQ_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ cl_ex_init (TYPE_1__*) ; 
 int /*<<< orphan*/  cl_putchar ; 
 scalar_t__ cl_quit (TYPE_1__*) ; 
 scalar_t__ cl_vi_init (TYPE_1__*) ; 
 int /*<<< orphan*/  q ; 
 scalar_t__ resizeterm (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * stdscr ; 
 int /*<<< orphan*/  tgoto (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  tputs (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wclrtobot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ *) ; 

int
cl_screen(SCR *sp, u_int32_t flags)
{
	CL_PRIVATE *clp;
	WINDOW *win;
	GS *gp;

	gp = sp->gp;
	clp = CLP(sp);
	win = CLSP(sp) ? CLSP(sp) : stdscr;

	/* See if the current information is incorrect. */
	if (F_ISSET(gp, G_SRESTART)) {
		if ((!F_ISSET(sp, SC_SCR_EX | SC_SCR_VI) ||
		     resizeterm(O_VAL(sp, O_LINES), O_VAL(sp, O_COLUMNS))) &&
		    cl_quit(gp))
			return (1);
		F_CLR(gp, G_SRESTART);
	}
	
	/* See if we're already in the right mode. */
	if ((LF_ISSET(SC_EX) && F_ISSET(sp, SC_SCR_EX)) ||
	    (LF_ISSET(SC_VI) && F_ISSET(sp, SC_SCR_VI)))
		return (0);

	/*
	 * Fake leaving ex mode.
	 *
	 * We don't actually exit ex or vi mode unless forced (e.g. by a window
	 * size change).  This is because many curses implementations can't be
	 * called twice in a single program.  Plus, it's faster.  If the editor
	 * "leaves" vi to enter ex, when it exits ex we'll just fall back into
	 * vi.
	 */
	if (F_ISSET(sp, SC_SCR_EX))
		F_CLR(sp, SC_SCR_EX);

	/*
	 * Fake leaving vi mode.
	 *
	 * Clear out the rest of the screen if we're in the middle of a split
	 * screen.  Move to the last line in the current screen -- this makes
	 * terminal scrolling happen naturally.  Note: *don't* move past the
	 * end of the screen, as there are ex commands (e.g., :read ! cat file)
	 * that don't want to.  Don't clear the info line, its contents may be
	 * valid, e.g. :file|append.
	 */
	if (F_ISSET(sp, SC_SCR_VI)) {
		F_CLR(sp, SC_SCR_VI);

		if (TAILQ_NEXT(sp, q) != NULL) {
			(void)wmove(win, RLNO(sp, sp->rows), 0);
			wclrtobot(win);
		}
		(void)wmove(win, RLNO(sp, sp->rows) - 1, 0);
		wrefresh(win);
	}

	/* Enter the requested mode. */
	if (LF_ISSET(SC_EX)) {
		if (cl_ex_init(sp))
			return (1);
		F_SET(clp, CL_IN_EX | CL_SCR_EX_INIT);

		/*
		 * If doing an ex screen for ex mode, move to the last line
		 * on the screen.
		 */
		if (F_ISSET(sp, SC_EX) && clp->cup != NULL)
			tputs(tgoto(clp->cup,
			    0, O_VAL(sp, O_LINES) - 1), 1, cl_putchar);
	} else {
		if (cl_vi_init(sp))
			return (1);
		F_CLR(clp, CL_IN_EX);
		F_SET(clp, CL_SCR_VI_INIT);
	}
	return (0);
}