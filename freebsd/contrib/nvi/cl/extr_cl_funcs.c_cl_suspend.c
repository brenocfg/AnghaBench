#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct termios {int dummy; } ;
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_15__ {TYPE_1__* frp; scalar_t__ killersig; struct termios orig; int /*<<< orphan*/ * gp; } ;
struct TYPE_14__ {int /*<<< orphan*/ * name; } ;
typedef  TYPE_2__ SCR ;
typedef  int /*<<< orphan*/  GS ;
typedef  TYPE_2__ CL_PRIVATE ;

/* Variables and functions */
 TYPE_2__* CLP (TYPE_2__*) ; 
 int /*<<< orphan*/ * CLSP (TYPE_2__*) ; 
 int CL_SCR_EX_INIT ; 
 int CL_SCR_VI_INIT ; 
 int /*<<< orphan*/  CL_SIGWINCH ; 
 int /*<<< orphan*/  CL_STDIN_TTY ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  F_CLR (TYPE_2__*,int) ; 
 scalar_t__ F_ISSET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_SET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 size_t LINES ; 
 int /*<<< orphan*/  SC_EX ; 
 int /*<<< orphan*/  SIGTSTP ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int TCSADRAIN ; 
 int TCSASOFT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cl_refresh (TYPE_2__*,int) ; 
 int /*<<< orphan*/  cl_rename (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ cl_ssize (TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  endwin () ; 
 int /*<<< orphan*/  getyx (int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/  keypad (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stdscr ; 
 int /*<<< orphan*/  tcgetattr (int /*<<< orphan*/ ,struct termios*) ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int,struct termios*) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ *) ; 

int
cl_suspend(SCR *sp, int *allowedp)
{
	struct termios t;
	CL_PRIVATE *clp;
	WINDOW *win;
	GS *gp;
	size_t y, x;
	int changed;

	gp = sp->gp;
	clp = CLP(sp);
	win = CLSP(sp) ? CLSP(sp) : stdscr;
	*allowedp = 1;

	/*
	 * The ex implementation of this function isn't needed by screens not
	 * supporting ex commands that require full terminal canonical mode
	 * (e.g. :suspend).
	 *
	 * The vi implementation of this function isn't needed by screens not
	 * supporting vi process suspension, i.e. any screen that isn't backed
	 * by a UNIX shell.
	 *
	 * Setting allowedp to 0 will cause the editor to reject the command.
	 */
	if (F_ISSET(sp, SC_EX)) { 
		/* Save the terminal settings, and restore the original ones. */
		if (F_ISSET(clp, CL_STDIN_TTY)) {
			(void)tcgetattr(STDIN_FILENO, &t);
			(void)tcsetattr(STDIN_FILENO,
			    TCSASOFT | TCSADRAIN, &clp->orig);
		}

		/* Stop the process group. */
		(void)kill(0, SIGTSTP);

		/* Time passes ... */

		/* Restore terminal settings. */
		if (F_ISSET(clp, CL_STDIN_TTY))
			(void)tcsetattr(STDIN_FILENO, TCSASOFT | TCSADRAIN, &t);
		return (0);
	}

	/*
	 * Move to the lower left-hand corner of the screen.
	 *
	 * XXX
	 * Not sure this is necessary in System V implementations, but it
	 * shouldn't hurt.
	 */
	getyx(win, y, x);
	(void)wmove(win, LINES - 1, 0);
	(void)wrefresh(win);

	/*
	 * Temporarily end the screen.  System V introduced a semantic where
	 * endwin() could be restarted.  We use it because restarting curses
	 * from scratch often fails in System V.  4BSD curses didn't support
	 * restarting after endwin(), so we have to do what clean up we can
	 * without calling it.
	 */
	/* Save the terminal settings. */
	(void)tcgetattr(STDIN_FILENO, &t);

	/* Restore the cursor keys to normal mode. */
	(void)keypad(stdscr, FALSE);

	/* Restore the window name. */
	(void)cl_rename(sp, NULL, 0);

	(void)endwin();

	/*
	 * XXX
	 * Restore the original terminal settings.  This is bad -- the
	 * reset can cause character loss from the tty queue.  However,
	 * we can't call endwin() in BSD curses implementations, and too
	 * many System V curses implementations don't get it right.
	 */
	(void)tcsetattr(STDIN_FILENO, TCSADRAIN | TCSASOFT, &clp->orig);

	/* Stop the process group. */
	(void)kill(0, SIGTSTP);

	/* Time passes ... */

	/*
	 * If we received a killer signal, we're done.  Leave everything
	 * unchanged.  In addition, the terminal has already been reset
	 * correctly, so leave it alone.
	 */
	if (clp->killersig) {
		F_CLR(clp, CL_SCR_EX_INIT | CL_SCR_VI_INIT);
		return (0);
	}

	/* Restore terminal settings. */
	wrefresh(win);			    /* Needed on SunOs/Solaris ? */
	if (F_ISSET(clp, CL_STDIN_TTY))
		(void)tcsetattr(STDIN_FILENO, TCSASOFT | TCSADRAIN, &t);

	/* Set the window name. */
	(void)cl_rename(sp, sp->frp->name, 1);

	/* Put the cursor keys into application mode. */
	(void)keypad(stdscr, TRUE);

	/* Refresh and repaint the screen. */
	(void)wmove(win, y, x);
	(void)cl_refresh(sp, 1);

	/* If the screen changed size, set the SIGWINCH bit. */
	if (cl_ssize(sp, 1, NULL, NULL, &changed))
		return (1);
	if (changed)
		F_SET(CLP(sp), CL_SIGWINCH);

	return (0);
}