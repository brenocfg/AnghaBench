#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ws ;
struct winsize {scalar_t__ ws_row; scalar_t__ ws_col; } ;
struct TYPE_2__ {int c_oflag; int c_iflag; int c_lflag; int c_cflag; } ;

/* Variables and functions */
 int CS8 ; 
 int ECHO ; 
 int ECHOE ; 
 int ECHOK ; 
 int EXTB ; 
 int HUPCL ; 
 int ICANON ; 
 int ICRNL ; 
 int IGNPAR ; 
 int ISIG ; 
 int ISTRIP ; 
 int IXOFF ; 
 int IXON ; 
 int ONLCR ; 
 int OPOST ; 
 int OXTABS ; 
 int /*<<< orphan*/  O_RDWR ; 
 int TAB3 ; 
 int /*<<< orphan*/  TIOCNOTTY ; 
 int /*<<< orphan*/  TIOCSWINSZ ; 
 int /*<<< orphan*/  _PATH_TTY ; 
 int cleanopen (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ def_col ; 
 scalar_t__ def_row ; 
 scalar_t__ def_rspeed ; 
 scalar_t__ def_tspeed ; 
 int /*<<< orphan*/  fatalperror (int,char*) ; 
 int /*<<< orphan*/  init_termbuf () ; 
 int /*<<< orphan*/  ioctl (int,int /*<<< orphan*/ ,char*) ; 
 char* line ; 
 int login_tty (int) ; 
 int /*<<< orphan*/  maybe_push_modules (int,char**) ; 
 int /*<<< orphan*/  memset (struct winsize*,int /*<<< orphan*/ ,int) ; 
 int net ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ourpty ; 
 scalar_t__ really_stream ; 
 int /*<<< orphan*/  set_termbuf () ; 
 scalar_t__ setsid () ; 
 TYPE_1__ termbuf ; 
 int /*<<< orphan*/  tty_rspeed (scalar_t__) ; 
 int /*<<< orphan*/  tty_tspeed (scalar_t__) ; 
 int ttyfd ; 
 int /*<<< orphan*/  utmp_sig_wait () ; 

void getptyslave(void)
{
    int t = -1;

    struct winsize ws;
    /*
     * Opening the slave side may cause initilization of the
     * kernel tty structure.  We need remember the state of
     * 	if linemode was turned on
     *	terminal window size
     *	terminal speed
     * so that we can re-set them if we need to.
     */


    /*
     * Make sure that we don't have a controlling tty, and
     * that we are the session (process group) leader.
     */

#ifdef HAVE_SETSID
    if(setsid()<0)
	fatalperror(net, "setsid()");
#else
# ifdef	TIOCNOTTY
    t = open(_PATH_TTY, O_RDWR);
    if (t >= 0) {
	ioctl(t, TIOCNOTTY, (char *)0);
	close(t);
    }
# endif
#endif

# ifdef PARENT_DOES_UTMP
    /*
     * Wait for our parent to get the utmp stuff to get done.
     */
    utmp_sig_wait();
# endif

    t = cleanopen(line);
    if (t < 0)
	fatalperror(net, line);

#ifdef  STREAMSPTY
    ttyfd = t;


    /*
     * Not all systems have (or need) modules ttcompat and pckt so
     * don't flag it as a fatal error if they don't exist.
     */

    if (really_stream)
	{
	    /* these are the streams modules that we want pushed. note
	       that they are in reverse order, ptem will be pushed
	       first. maybe_push_modules() will try to push all modules
	       before the first one that isn't already pushed. i.e if
	       ldterm is pushed, only ttcompat will be attempted.

	       all this is because we don't know which modules are
	       available, and we don't know which modules are already
	       pushed (via autopush, for instance).

	       */

	    char *ttymodules[] = { "ttcompat", "ldterm", "ptem", NULL };
	    char *ptymodules[] = { "pckt", NULL };

	    maybe_push_modules(t, ttymodules);
	    maybe_push_modules(ourpty, ptymodules);
	}
#endif
    /*
     * set up the tty modes as we like them to be.
     */
    init_termbuf();
# ifdef	TIOCSWINSZ
    if (def_row || def_col) {
	memset(&ws, 0, sizeof(ws));
	ws.ws_col = def_col;
	ws.ws_row = def_row;
	ioctl(t, TIOCSWINSZ, (char *)&ws);
    }
# endif

    /*
     * Settings for sgtty based systems
     */

    /*
     * Settings for UNICOS (and HPUX)
     */
# if defined(_CRAY) || defined(__hpux)
    termbuf.c_oflag = OPOST|ONLCR|TAB3;
    termbuf.c_iflag = IGNPAR|ISTRIP|ICRNL|IXON;
    termbuf.c_lflag = ISIG|ICANON|ECHO|ECHOE|ECHOK;
    termbuf.c_cflag = EXTB|HUPCL|CS8;
# endif

    /*
     * Settings for all other termios/termio based
     * systems, other than 4.4BSD.  In 4.4BSD the
     * kernel does the initial terminal setup.
     */
# if !(defined(_CRAY) || defined(__hpux)) && (BSD <= 43)
#  ifndef	OXTABS
#   define OXTABS	0
#  endif
    termbuf.c_lflag |= ECHO;
    termbuf.c_oflag |= ONLCR|OXTABS;
    termbuf.c_iflag |= ICRNL;
    termbuf.c_iflag &= ~IXOFF;
# endif
    tty_rspeed((def_rspeed > 0) ? def_rspeed : 9600);
    tty_tspeed((def_tspeed > 0) ? def_tspeed : 9600);

    /*
     * Set the tty modes, and make this our controlling tty.
     */
    set_termbuf();
    if (login_tty(t) == -1)
	fatalperror(net, "login_tty");
    if (net > 2)
	close(net);
    if (ourpty > 2) {
	close(ourpty);
	ourpty = -1;
    }
}