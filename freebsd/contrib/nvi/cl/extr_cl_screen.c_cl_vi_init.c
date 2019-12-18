#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_19__ {int c_iflag; void** c_cc; int /*<<< orphan*/  c_lflag; } ;
struct TYPE_16__ {int c_iflag; } ;
struct TYPE_18__ {TYPE_4__ vi_enter; TYPE_1__ orig; int /*<<< orphan*/  ti_te; } ;
struct TYPE_17__ {int /*<<< orphan*/ * gp; } ;
typedef  TYPE_2__ SCR ;
typedef  int /*<<< orphan*/  GS ;
typedef  TYPE_3__ CL_PRIVATE ;

/* Variables and functions */
 TYPE_3__* CLP (TYPE_2__*) ; 
 int /*<<< orphan*/  CL_SCR_VI_INIT ; 
 int /*<<< orphan*/  CL_STDIN_TTY ; 
 scalar_t__ EINTR ; 
 scalar_t__ F_ISSET (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISIG ; 
 int IXOFF ; 
 int IXON ; 
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  M_SYSERR ; 
 int /*<<< orphan*/  O_COLUMNS ; 
 int /*<<< orphan*/  O_LINES ; 
 char* O_STR (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  O_TERM ; 
 scalar_t__ O_VAL (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGTSTP ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int TCSADRAIN ; 
 int TCSASOFT ; 
 int /*<<< orphan*/  TI_SENT ; 
 int /*<<< orphan*/  TRUE ; 
 size_t VDISCARD ; 
 size_t VDSUSP ; 
 size_t VLNEXT ; 
 size_t VQUIT ; 
 size_t VSTATUS ; 
 size_t VSUSP ; 
 void* _POSIX_VDISABLE ; 
 int /*<<< orphan*/  cl_putenv (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ cl_term_init (TYPE_2__*) ; 
 int /*<<< orphan*/  cl_vi_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cur_term ; 
 int /*<<< orphan*/  del_curterm (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  idlok (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  isatty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keypad (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msgq (TYPE_2__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * newterm (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  noecho () ; 
 int /*<<< orphan*/  nonl () ; 
 scalar_t__ opts_empty (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw () ; 
 int /*<<< orphan*/  sig_init (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  stdscr ; 
 scalar_t__ tcgetattr (int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ tcsetattr (int /*<<< orphan*/ ,int,TYPE_4__*) ; 
 int /*<<< orphan*/  unsetenv (char*) ; 

__attribute__((used)) static int
cl_vi_init(SCR *sp)
{
	CL_PRIVATE *clp;
	GS *gp;
	char *o_cols, *o_lines, *o_term, *ttype;

	gp = sp->gp;
	clp = CLP(sp);

	/* If already initialized, just set the terminal modes. */
	if (F_ISSET(clp, CL_SCR_VI_INIT))
		goto fast;

	/* Curses vi always reads from (and writes to) a terminal. */
	if (!F_ISSET(clp, CL_STDIN_TTY) || !isatty(STDOUT_FILENO)) {
		msgq(sp, M_ERR,
		    "016|Vi's standard input and output must be a terminal");
		return (1);
	}

	/* We'll need a terminal type. */
	if (opts_empty(sp, O_TERM, 0))
		return (1);
	ttype = O_STR(sp, O_TERM);

	/*
	 * XXX
	 * Changing the row/column and terminal values is done by putting them
	 * into the environment, which is then read by curses.  What this loses
	 * in ugliness, it makes up for in stupidity.  We can't simply put the
	 * values into the environment ourselves, because in the presence of a
	 * kernel mechanism for returning the window size, entering values into
	 * the environment will screw up future screen resizing events, e.g. if
	 * the user enters a :shell command and then resizes their window.  So,
	 * if they weren't already in the environment, we make sure to delete
	 * them immediately after setting them.
	 *
	 * XXX
	 * Putting the TERM variable into the environment is necessary, even
	 * though we're using newterm() here.  We may be using initscr() as
	 * the underlying function.
	 */
	o_term = getenv("TERM");
	cl_putenv("TERM", ttype, 0);
	o_lines = getenv("LINES");
	cl_putenv("LINES", NULL, (u_long)O_VAL(sp, O_LINES));
	o_cols = getenv("COLUMNS");
	cl_putenv("COLUMNS", NULL, (u_long)O_VAL(sp, O_COLUMNS));

	/*
	 * The terminal is aways initialized, either in `main`, or by a
	 * previous call to newterm(3X).
	 */
	(void)del_curterm(cur_term);

	/*
	 * We never have more than one SCREEN at a time, so set_term(NULL) will
	 * give us the last SCREEN.
	 */
	errno = 0;
	if (newterm(ttype, stdout, stdin) == NULL) {
		if (errno)
			msgq(sp, M_SYSERR, "%s", ttype);
		else
			msgq(sp, M_ERR, "%s: unknown terminal type", ttype);
		return (1);
	}

	if (o_term == NULL)
		unsetenv("TERM");
	if (o_lines == NULL)
		unsetenv("LINES");
	if (o_cols == NULL)
		unsetenv("COLUMNS");

	/*
	 * XXX
	 * Someone got let out alone without adult supervision -- the SunOS
	 * newterm resets the signal handlers.  There's a race, but it's not
	 * worth closing.
	 */
	(void)sig_init(sp->gp, sp);

	/*
	 * We use raw mode.  What we want is 8-bit clean, however, signals
	 * and flow control should continue to work.  Admittedly, it sounds
	 * like cbreak, but it isn't.  Using cbreak() can get you additional
	 * things like IEXTEN, which turns on flags like DISCARD and LNEXT.
	 *
	 * !!!
	 * If raw isn't turning off echo and newlines, something's wrong.
	 * However, it shouldn't hurt.
	 */
	noecho();			/* No character echo. */
	nonl();				/* No CR/NL translation. */
	raw();				/* 8-bit clean. */
	idlok(stdscr, 1);		/* Use hardware insert/delete line. */

	/* Put the cursor keys into application mode. */
	(void)keypad(stdscr, TRUE);

	/*
	 * XXX
	 * The screen TI sequence just got sent.  See the comment in
	 * cl_funcs.c:cl_attr().
	 */
	clp->ti_te = TI_SENT;

	/*
	 * XXX
	 * Historic implementations of curses handled SIGTSTP signals
	 * in one of three ways.  They either:
	 *
	 *	1: Set their own handler, regardless.
	 *	2: Did not set a handler if a handler was already installed.
	 *	3: Set their own handler, but then called any previously set
	 *	   handler after completing their own cleanup.
	 *
	 * We don't try and figure out which behavior is in place, we force
	 * it to SIG_DFL after initializing the curses interface, which means
	 * that curses isn't going to take the signal.  Since curses isn't
	 * reentrant (i.e., the whole curses SIGTSTP interface is a fantasy),
	 * we're doing The Right Thing.
	 */
	(void)signal(SIGTSTP, SIG_DFL);

	/*
	 * If flow control was on, turn it back on.  Turn signals on.  ISIG
	 * turns on VINTR, VQUIT, VDSUSP and VSUSP.   The main curses code
	 * already installed a handler for VINTR.  We're going to disable the
	 * other three.
	 *
	 * XXX
	 * We want to use ^Y as a vi scrolling command.  If the user has the
	 * DSUSP character set to ^Y (common practice) clean it up.  As it's
	 * equally possible that the user has VDSUSP set to 'a', we disable
	 * it regardless.  It doesn't make much sense to suspend vi at read,
	 * so I don't think anyone will care.  Alternatively, we could look
	 * it up in the table of legal command characters and turn it off if
	 * it matches one.  VDSUSP wasn't in POSIX 1003.1-1990, so we test for
	 * it.
	 *
	 * XXX
	 * We don't check to see if the user had signals enabled originally.
	 * If they didn't, it's unclear what we're supposed to do here, but
	 * it's also pretty unlikely.
	 */
	if (tcgetattr(STDIN_FILENO, &clp->vi_enter)) {
		msgq(sp, M_SYSERR, "tcgetattr");
		goto err;
	}
	if (clp->orig.c_iflag & IXON)
		clp->vi_enter.c_iflag |= IXON;
	if (clp->orig.c_iflag & IXOFF)
		clp->vi_enter.c_iflag |= IXOFF;

	clp->vi_enter.c_lflag |= ISIG;
#ifdef VDSUSP
	clp->vi_enter.c_cc[VDSUSP] = _POSIX_VDISABLE;
#endif
	clp->vi_enter.c_cc[VQUIT] = _POSIX_VDISABLE;
	clp->vi_enter.c_cc[VSUSP] = _POSIX_VDISABLE;

	/*
	 * XXX
	 * OSF/1 doesn't turn off the <discard>, <literal-next> or <status>
	 * characters when curses switches into raw mode.  It should be OK
	 * to do it explicitly for everyone.
	 */
#ifdef VDISCARD
	clp->vi_enter.c_cc[VDISCARD] = _POSIX_VDISABLE;
#endif
#ifdef VLNEXT
	clp->vi_enter.c_cc[VLNEXT] = _POSIX_VDISABLE;
#endif
#ifdef VSTATUS
	clp->vi_enter.c_cc[VSTATUS] = _POSIX_VDISABLE;
#endif

	/* Initialize terminal based information. */
	if (cl_term_init(sp))
		goto err;

fast:	/* Set the terminal modes. */
	if (tcsetattr(STDIN_FILENO, TCSASOFT | TCSADRAIN, &clp->vi_enter)) {
		if (errno == EINTR)
			goto fast;
		msgq(sp, M_SYSERR, "tcsetattr");
err:		(void)cl_vi_end(sp->gp);
		return (1);
	}
	return (0);
}