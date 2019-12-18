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
struct TYPE_5__ {int /*<<< orphan*/  orig; } ;
typedef  int /*<<< orphan*/  GS ;
typedef  TYPE_1__ CL_PRIVATE ;

/* Variables and functions */
 int CL_SCR_EX_INIT ; 
 int CL_SCR_VI_INIT ; 
 int CL_STDIN_TTY ; 
 int /*<<< orphan*/  F_CLR (TYPE_1__*,int) ; 
 scalar_t__ F_ISSET (TYPE_1__*,int) ; 
 TYPE_1__* GCLP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int TCSADRAIN ; 
 int TCSASOFT ; 
 scalar_t__ cl_ex_end (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_term_end (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_vi_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

int
cl_quit(GS *gp)
{
	CL_PRIVATE *clp;
	int rval;

	rval = 0;
	clp = GCLP(gp);

	/*
	 * If we weren't really running, ignore it.  This happens if the
	 * screen changes size before we've called curses.
	 */
	if (!F_ISSET(clp, CL_SCR_EX_INIT | CL_SCR_VI_INIT))
		return (0);

	/* Clean up the terminal mappings. */
	if (cl_term_end(gp))
		rval = 1;

	/* Really leave vi mode. */
	if (F_ISSET(clp, CL_STDIN_TTY) &&
	    F_ISSET(clp, CL_SCR_VI_INIT) && cl_vi_end(gp))
		rval = 1;

	/* Really leave ex mode. */
	if (F_ISSET(clp, CL_STDIN_TTY) &&
	    F_ISSET(clp, CL_SCR_EX_INIT) && cl_ex_end(gp))
		rval = 1;

	/*
	 * If we were running ex when we quit, or we're using an implementation
	 * of curses where endwin() doesn't get this right, restore the original
	 * terminal modes.
	 *
	 * XXX
	 * We always do this because it's too hard to figure out what curses
	 * implementations get it wrong.  It may discard type-ahead characters
	 * from the tty queue.
	 */
	(void)tcsetattr(STDIN_FILENO, TCSADRAIN | TCSASOFT, &clp->orig);

	F_CLR(clp, CL_SCR_EX_INIT | CL_SCR_VI_INIT);
	return (rval);
}