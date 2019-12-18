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
struct winsize {size_t ws_row; size_t ws_col; } ;
typedef  int /*<<< orphan*/  SCR ;

/* Variables and functions */
 int /*<<< orphan*/  M_SYSERR ; 
 int /*<<< orphan*/  O_COLUMNS ; 
 int /*<<< orphan*/  O_LINES ; 
 size_t O_VAL (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  TIOCGWINSZ ; 
 char* getenv (char*) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct winsize*) ; 
 int /*<<< orphan*/  msgq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 size_t strtol (char*,int /*<<< orphan*/ *,int) ; 
 int tigetnum (char*) ; 

int
cl_ssize(SCR *sp, int sigwinch, size_t *rowp, size_t *colp, int *changedp)
{
	struct winsize win;
	size_t col, row;
	int rval;
	char *p;

	/* Assume it's changed. */
	if (changedp != NULL)
		*changedp = 1;

	/*
	 * !!!
	 * sp may be NULL.
	 *
	 * Get the screen rows and columns.  If the values are wrong, it's
	 * not a big deal -- as soon as the user sets them explicitly the
	 * environment will be set and the screen package will use the new
	 * values.
	 *
	 * Try TIOCGWINSZ.
	 */
	row = col = 0;
	if (ioctl(STDERR_FILENO, TIOCGWINSZ, &win) != -1) {
		row = win.ws_row;
		col = win.ws_col;
	}
	/* If here because of suspend or a signal, only trust TIOCGWINSZ. */
	if (sigwinch) {
		/*
		 * Somebody didn't get TIOCGWINSZ right, or has suspend
		 * without window resizing support.  The user just lost,
		 * but there's nothing we can do.
		 */
		if (row == 0 || col == 0) {
			if (changedp != NULL)
				*changedp = 0;
			return (0);
		}

		/*
		 * SunOS systems deliver SIGWINCH when windows are uncovered
		 * as well as when they change size.  In addition, we call
		 * here when continuing after being suspended since the window
		 * may have changed size.  Since we don't want to background
		 * all of the screens just because the window was uncovered,
		 * ignore the signal if there's no change.
		 */
		if (sp != NULL &&
		    row == O_VAL(sp, O_LINES) && col == O_VAL(sp, O_COLUMNS)) {
			if (changedp != NULL)
				*changedp = 0;
			return (0);
		}

		if (rowp != NULL)
			*rowp = row;
		if (colp != NULL)
			*colp = col;
		return (0);
	}

	/*
	 * !!!
	 * If TIOCGWINSZ failed, or had entries of 0, try termcap.  This
	 * routine is called before any termcap or terminal information
	 * has been set up.  If there's no TERM environmental variable set,
	 * let it go, at least ex can run.
	 */
	if (row == 0 || col == 0) {
		if ((p = getenv("TERM")) == NULL)
			goto noterm;
		if (row == 0)
			if ((rval = tigetnum("lines")) < 0)
				msgq(sp, M_SYSERR, "tigetnum: lines");
			else
				row = rval;
		if (col == 0)
			if ((rval = tigetnum("cols")) < 0)
				msgq(sp, M_SYSERR, "tigetnum: cols");
			else
				col = rval;
	}

	/* If nothing else, well, it's probably a VT100. */
noterm:	if (row == 0)
		row = 24;
	if (col == 0)
		col = 80;

	/*
	 * !!!
	 * POSIX 1003.2 requires the environment to override everything.
	 * Often, people can get nvi to stop messing up their screen by
	 * deleting the LINES and COLUMNS environment variables from their
	 * dot-files.
	 */
	if ((p = getenv("LINES")) != NULL)
		row = strtol(p, NULL, 10);
	if ((p = getenv("COLUMNS")) != NULL)
		col = strtol(p, NULL, 10);

	if (rowp != NULL)
		*rowp = row;
	if (colp != NULL)
		*colp = col;
	return (0);
}