#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ws ;
struct winsize {int ws_col; int ws_row; } ;
struct TYPE_3__ {int sg_flags; } ;
struct TYPE_4__ {char* c_cc; TYPE_1__ sg; } ;

/* Variables and functions */
 int ANYP ; 
 int CRMOD ; 
 int ECHO ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  TIOCNOTTY ; 
 int /*<<< orphan*/  TIOCSWINSZ ; 
 size_t VERASE ; 
 int XTABS ; 
 int /*<<< orphan*/  _PATH_TTY ; 
 int cleanopen (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fatalperror (int,char*) ; 
 int /*<<< orphan*/  init_termbuf () ; 
 int /*<<< orphan*/  ioctl (int,int /*<<< orphan*/ ,char*) ; 
 char* line ; 
 int login_tty (int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int net ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pty ; 
 int /*<<< orphan*/  set_termbuf () ; 
 TYPE_2__ termbuf ; 
 int tty_linemode () ; 
 int /*<<< orphan*/  tty_rspeed (int) ; 
 int /*<<< orphan*/  tty_setlinemode (int) ; 
 int /*<<< orphan*/  tty_tspeed (int) ; 

__attribute__((used)) static void
getptyslave(void)
{
	int t = -1;
	char erase;

# ifdef	LINEMODE
	int waslm;
# endif
# ifdef	TIOCGWINSZ
	struct winsize ws;
	extern int def_row, def_col;
# endif
	extern int def_tspeed, def_rspeed;
	/*
	 * Opening the slave side may cause initilization of the
	 * kernel tty structure.  We need remember the state of
	 * 	if linemode was turned on
	 *	terminal window size
	 *	terminal speed
	 *	erase character
	 * so that we can re-set them if we need to.
	 */
# ifdef	LINEMODE
	waslm = tty_linemode();
# endif
	erase = termbuf.c_cc[VERASE];

	/*
	 * Make sure that we don't have a controlling tty, and
	 * that we are the session (process group) leader.
	 */
# ifdef	TIOCNOTTY
	t = open(_PATH_TTY, O_RDWR);
	if (t >= 0) {
		(void) ioctl(t, TIOCNOTTY, (char *)0);
		(void) close(t);
	}
# endif

	t = cleanopen(line);
	if (t < 0)
		fatalperror(net, line);


	/*
	 * set up the tty modes as we like them to be.
	 */
	init_termbuf();
# ifdef	TIOCGWINSZ
	if (def_row || def_col) {
		memset((char *)&ws, 0, sizeof(ws));
		ws.ws_col = def_col;
		ws.ws_row = def_row;
		(void)ioctl(t, TIOCSWINSZ, (char *)&ws);
	}
# endif

	/*
	 * Settings for sgtty based systems
	 */
# ifndef	USE_TERMIO
	termbuf.sg.sg_flags |= CRMOD|ANYP|ECHO|XTABS;
# endif	/* USE_TERMIO */

	/*
	 * Settings for all other termios/termio based
	 * systems, other than 4.4BSD.  In 4.4BSD the
	 * kernel does the initial terminal setup.
	 */
	tty_rspeed((def_rspeed > 0) ? def_rspeed : 9600);
	tty_tspeed((def_tspeed > 0) ? def_tspeed : 9600);
	if (erase)
		termbuf.c_cc[VERASE] = erase;
# ifdef	LINEMODE
	if (waslm)
		tty_setlinemode(1);
# endif	/* LINEMODE */

	/*
	 * Set the tty modes, and make this our controlling tty.
	 */
	set_termbuf();
	if (login_tty(t) == -1)
		fatalperror(net, "login_tty");
	if (net > 2)
		(void) close(net);
#ifdef	AUTHENTICATION
#if	defined(NO_LOGIN_F) && defined(LOGIN_R)
	/*
	 * Leave the pty open so that we can write out the rlogin
	 * protocol for /bin/login, if the authentication works.
	 */
#else
	if (pty > 2) {
		(void) close(pty);
		pty = -1;
	}
#endif
#endif /* AUTHENTICATION */
}