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
struct termios {int c_iflag; int* c_cc; int c_cflag; int /*<<< orphan*/  c_lflag; int /*<<< orphan*/  c_oflag; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  void* cc_t ;

/* Variables and functions */
 int CS8 ; 
 int CSIZE ; 
 int /*<<< orphan*/  ECHO ; 
 int /*<<< orphan*/  ECHOCTL ; 
 int /*<<< orphan*/  FIONBIO ; 
 int /*<<< orphan*/  ICANON ; 
 int ICRNL ; 
 int /*<<< orphan*/  ISIG ; 
 int ISTRIP ; 
 int IXANY ; 
 int IXOFF ; 
 int IXON ; 
 int MODE_ECHO ; 
 int MODE_EDIT ; 
 int MODE_FLOW ; 
 int MODE_FORCE ; 
 int MODE_INBIN ; 
 int MODE_LIT_ECHO ; 
 int MODE_OUT8 ; 
 int MODE_OUTBIN ; 
 int MODE_SOFT_TAB ; 
 int MODE_TRAPSIG ; 
 int /*<<< orphan*/  NOKERNINFO ; 
 int /*<<< orphan*/  ONLCR ; 
 int /*<<< orphan*/  OPOST ; 
 int /*<<< orphan*/  OXTABS ; 
 int PARENB ; 
 int /*<<< orphan*/  SIGINFO ; 
 int /*<<< orphan*/  SIGTSTP ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  SIG_UNBLOCK ; 
 int SYNCHing ; 
 int /*<<< orphan*/  TAB3 ; 
 int /*<<< orphan*/  TABDLY ; 
 int /*<<< orphan*/  TCSADRAIN ; 
 int /*<<< orphan*/  TCSANOW ; 
 size_t VDSUSP ; 
 size_t VEOL ; 
 size_t VEOL2 ; 
 size_t VLNEXT ; 
 size_t VMIN ; 
 size_t VTIME ; 
 scalar_t__ _POSIX_VDISABLE ; 
 int /*<<< orphan*/  ayt ; 
 int /*<<< orphan*/  ayt_status ; 
 scalar_t__ crlf ; 
 scalar_t__ escape ; 
 int flushout ; 
 int globalmode ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int localchars ; 
 struct termios new_tc ; 
 struct termios old_tc ; 
 scalar_t__ restartany ; 
 scalar_t__ rlogin ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  susp ; 
 int /*<<< orphan*/  tcgetattr (int /*<<< orphan*/ ,struct termios*) ; 
 scalar_t__ tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct termios*) ; 
 int /*<<< orphan*/  tin ; 
 int /*<<< orphan*/  tout ; 
 int ttyflush (int) ; 

void
TerminalNewMode(int f)
{
    static int prevmode = 0;
    struct termios tmp_tc;
    int onoff;
    int old;
    cc_t esc;

    globalmode = f&~MODE_FORCE;
    if (prevmode == f)
	return;

    /*
     * Write any outstanding data before switching modes
     * ttyflush() returns 0 only when there is no more data
     * left to write out, it returns -1 if it couldn't do
     * anything at all, otherwise it returns 1 + the number
     * of characters left to write.
     */
    old = ttyflush(SYNCHing|flushout);
    if (old < 0 || old > 1) {
	tcgetattr(tin, &tmp_tc);
	do {
	    /*
	     * Wait for data to drain, then flush again.
	     */
	    tcsetattr(tin, TCSADRAIN, &tmp_tc);
	    old = ttyflush(SYNCHing|flushout);
	} while (old < 0 || old > 1);
    }

    old = prevmode;
    prevmode = f&~MODE_FORCE;
    tmp_tc = new_tc;

    if (f&MODE_ECHO) {
	tmp_tc.c_lflag |= ECHO;
	tmp_tc.c_oflag |= ONLCR;
	if (crlf)
		tmp_tc.c_iflag |= ICRNL;
    } else {
	tmp_tc.c_lflag &= ~ECHO;
	tmp_tc.c_oflag &= ~ONLCR;
# ifdef notdef
	if (crlf)
		tmp_tc.c_iflag &= ~ICRNL;
# endif
    }

    if ((f&MODE_FLOW) == 0) {
	tmp_tc.c_iflag &= ~(IXOFF|IXON);	/* Leave the IXANY bit alone */
    } else {
	if (restartany < 0) {
		tmp_tc.c_iflag |= IXOFF|IXON;	/* Leave the IXANY bit alone */
	} else if (restartany > 0) {
		tmp_tc.c_iflag |= IXOFF|IXON|IXANY;
	} else {
		tmp_tc.c_iflag |= IXOFF|IXON;
		tmp_tc.c_iflag &= ~IXANY;
	}
    }

    if ((f&MODE_TRAPSIG) == 0) {
	tmp_tc.c_lflag &= ~ISIG;
	localchars = 0;
    } else {
	tmp_tc.c_lflag |= ISIG;
	localchars = 1;
    }

    if (f&MODE_EDIT) {
	tmp_tc.c_lflag |= ICANON;
    } else {
	tmp_tc.c_lflag &= ~ICANON;
	tmp_tc.c_iflag &= ~ICRNL;
	tmp_tc.c_cc[VMIN] = 1;
	tmp_tc.c_cc[VTIME] = 0;
    }

    if ((f&(MODE_EDIT|MODE_TRAPSIG)) == 0) {
# ifdef VLNEXT
	tmp_tc.c_cc[VLNEXT] = (cc_t)(_POSIX_VDISABLE);
# endif
    }

    if (f&MODE_SOFT_TAB) {
# ifdef	OXTABS
	tmp_tc.c_oflag |= OXTABS;
# endif
# ifdef	TABDLY
	tmp_tc.c_oflag &= ~TABDLY;
	tmp_tc.c_oflag |= TAB3;
# endif
    } else {
# ifdef	OXTABS
	tmp_tc.c_oflag &= ~OXTABS;
# endif
# ifdef	TABDLY
	tmp_tc.c_oflag &= ~TABDLY;
# endif
    }

    if (f&MODE_LIT_ECHO) {
# ifdef	ECHOCTL
	tmp_tc.c_lflag &= ~ECHOCTL;
# endif
    } else {
# ifdef	ECHOCTL
	tmp_tc.c_lflag |= ECHOCTL;
# endif
    }

    if (f == -1) {
	onoff = 0;
    } else {
	if (f & MODE_INBIN)
		tmp_tc.c_iflag &= ~ISTRIP;
	else
		tmp_tc.c_iflag |= ISTRIP;
	if ((f & MODE_OUTBIN) || (f & MODE_OUT8)) {
		tmp_tc.c_cflag &= ~(CSIZE|PARENB);
		tmp_tc.c_cflag |= CS8;
		if(f & MODE_OUTBIN)
		    tmp_tc.c_oflag &= ~OPOST;
		else
		    tmp_tc.c_oflag |= OPOST;
	} else {
		tmp_tc.c_cflag &= ~(CSIZE|PARENB);
		tmp_tc.c_cflag |= old_tc.c_cflag & (CSIZE|PARENB);
		tmp_tc.c_oflag |= OPOST;
	}
	onoff = 1;
    }

    if (f != -1) {

#ifdef	SIGTSTP
	signal(SIGTSTP, susp);
#endif	/* SIGTSTP */
#ifdef	SIGINFO
	signal(SIGINFO, ayt);
#endif
#ifdef NOKERNINFO
	tmp_tc.c_lflag |= NOKERNINFO;
#endif
	/*
	 * We don't want to process ^Y here.  It's just another
	 * character that we'll pass on to the back end.  It has
	 * to process it because it will be processed when the
	 * user attempts to read it, not when we send it.
	 */
# ifdef	VDSUSP
	tmp_tc.c_cc[VDSUSP] = (cc_t)(_POSIX_VDISABLE);
# endif
	/*
	 * If the VEOL character is already set, then use VEOL2,
	 * otherwise use VEOL.
	 */
	esc = (rlogin != _POSIX_VDISABLE) ? rlogin : escape;
	if ((tmp_tc.c_cc[VEOL] != esc)
# ifdef	VEOL2
	    && (tmp_tc.c_cc[VEOL2] != esc)
# endif
	    ) {
		if (tmp_tc.c_cc[VEOL] == (cc_t)(_POSIX_VDISABLE))
		    tmp_tc.c_cc[VEOL] = esc;
# ifdef	VEOL2
		else if (tmp_tc.c_cc[VEOL2] == (cc_t)(_POSIX_VDISABLE))
		    tmp_tc.c_cc[VEOL2] = esc;
# endif
	}
    } else {
        sigset_t sm;

#ifdef	SIGINFO
	signal(SIGINFO, ayt_status);
#endif
#ifdef	SIGTSTP
	signal(SIGTSTP, SIG_DFL);
	sigemptyset(&sm);
	sigaddset(&sm, SIGTSTP);
	sigprocmask(SIG_UNBLOCK, &sm, NULL);
#endif	/* SIGTSTP */
	tmp_tc = old_tc;
    }
    if (tcsetattr(tin, TCSADRAIN, &tmp_tc) < 0)
	tcsetattr(tin, TCSANOW, &tmp_tc);

    ioctl(tin, FIONBIO, (char *)&onoff);
    ioctl(tout, FIONBIO, (char *)&onoff);

}