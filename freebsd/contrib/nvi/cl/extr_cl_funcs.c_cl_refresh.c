#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_13__ {TYPE_1__* focus; scalar_t__ killersig; } ;
struct TYPE_12__ {scalar_t__ roff; scalar_t__ coff; scalar_t__ cols; int /*<<< orphan*/ * gp; } ;
typedef  TYPE_1__ SCR ;
typedef  int /*<<< orphan*/  GS ;
typedef  TYPE_2__ CL_PRIVATE ;

/* Variables and functions */
 TYPE_2__* CLP (TYPE_1__*) ; 
 int /*<<< orphan*/ * CLSP (TYPE_1__*) ; 
 int /*<<< orphan*/  CL_LAYOUT ; 
 scalar_t__ ERR ; 
 int /*<<< orphan*/  F_CLR (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ F_ISSET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* TAILQ_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_rdiv (TYPE_1__*) ; 
 int /*<<< orphan*/  clearok (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  curscr ; 
 scalar_t__ doupdate () ; 
 int /*<<< orphan*/  getyx (int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/  q ; 
 int /*<<< orphan*/ * stdscr ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,size_t,size_t) ; 
 scalar_t__ wnoutrefresh (int /*<<< orphan*/ *) ; 

int
cl_refresh(SCR *sp, int repaint)
{
	GS *gp;
	CL_PRIVATE *clp;
	WINDOW *win;
	SCR *psp, *tsp;
	size_t y, x;

	gp = sp->gp;
	clp = CLP(sp);
	win = CLSP(sp) ? CLSP(sp) : stdscr;

	/*
	 * If we received a killer signal, we're done, there's no point
	 * in refreshing the screen.
	 */
	if (clp->killersig)
		return (0);

	/*
	 * If repaint is set, the editor is telling us that we don't know
	 * what's on the screen, so we have to repaint from scratch.
	 *
	 * If repaint set or the screen layout changed, we need to redraw
	 * any lines separating vertically split screens.  If the horizontal
	 * offsets are the same, then the split was vertical, and need to
	 * draw a dividing line.
	 */
	if (repaint || F_ISSET(clp, CL_LAYOUT)) {
		getyx(stdscr, y, x);
		for (psp = sp; psp != NULL; psp = TAILQ_NEXT(psp, q))
			for (tsp = TAILQ_NEXT(psp, q); tsp != NULL;
			    tsp = TAILQ_NEXT(tsp, q))
				if (psp->roff == tsp->roff) {
				    if (psp->coff + psp->cols + 1 == tsp->coff)
					cl_rdiv(psp);
				    else 
				    if (tsp->coff + tsp->cols + 1 == psp->coff)
					cl_rdiv(tsp);
				}
		(void)wmove(stdscr, y, x);
		F_CLR(clp, CL_LAYOUT);
	}

	/*
	 * In the curses library, doing wrefresh(curscr) is okay, but the
	 * screen flashes when we then apply the refresh() to bring it up
	 * to date.  So, use clearok().
	 */
	if (repaint)
		clearok(curscr, 1);
	/*
	 * Only do an actual refresh, when this is the focus window,
	 * i.e. the one holding the cursor. This assumes that refresh
	 * is called for that window after refreshing the others.
	 * This prevents the cursor being drawn in the other windows.
	 */
	return (wnoutrefresh(stdscr) == ERR || 
		wnoutrefresh(win) == ERR || 
		(sp == clp->focus && doupdate() == ERR));
}