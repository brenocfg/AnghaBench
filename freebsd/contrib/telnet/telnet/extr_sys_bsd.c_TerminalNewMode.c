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
struct termio {int c_iflag; int* c_cc; int c_cflag; int /*<<< orphan*/  c_lflag; int /*<<< orphan*/  c_oflag; } ;
struct tchars {void* t_brkc; scalar_t__ t_eofc; scalar_t__ t_quitc; scalar_t__ t_intrc; scalar_t__ t_stopc; scalar_t__ t_startc; } ;
struct sgttyb {int /*<<< orphan*/  sg_flags; } ;
struct ltchars {scalar_t__ t_dsuspc; scalar_t__ t_lnextc; scalar_t__ t_suspc; } ;
typedef  void* cc_t ;

/* Variables and functions */
 int /*<<< orphan*/  CBREAK ; 
 int /*<<< orphan*/  CRMOD ; 
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
 int LCTLECH ; 
 int LLITOUT ; 
 int LPASS8 ; 
 int MODE_ECHO ; 
 int MODE_EDIT ; 
 int MODE_FLOW ; 
 int MODE_FORCE ; 
 int MODE_INBIN ; 
 int MODE_LIT_ECHO ; 
 int MODE_OUTBIN ; 
 int MODE_SOFT_TAB ; 
 int MODE_TRAPSIG ; 
 int /*<<< orphan*/  NOKERNINFO ; 
 int /*<<< orphan*/  ONLCR ; 
 int /*<<< orphan*/  OPOST ; 
 int /*<<< orphan*/  OXTABS ; 
 int PARENB ; 
 int SIGINFO ; 
 int SIGINT ; 
 int SIGQUIT ; 
 int SIGTSTP ; 
 void SIG_DFL (int) ; 
 int SYNCHing ; 
 int /*<<< orphan*/  TAB3 ; 
 int /*<<< orphan*/  TABDLY ; 
 int /*<<< orphan*/  TCSADRAIN ; 
 int /*<<< orphan*/  TCSANOW ; 
 int /*<<< orphan*/  TIOCLSET ; 
 int /*<<< orphan*/  TIOCSETC ; 
 int /*<<< orphan*/  TIOCSETN ; 
 int /*<<< orphan*/  TIOCSLTC ; 
 size_t VDSUSP ; 
 size_t VEOL ; 
 size_t VEOL2 ; 
 size_t VLNEXT ; 
 size_t VMIN ; 
 size_t VTIME ; 
 int /*<<< orphan*/  XTABS ; 
 scalar_t__ _POSIX_VDISABLE ; 
 void ayt (int) ; 
 scalar_t__ ayt_status ; 
 scalar_t__ crlf ; 
 scalar_t__ escape ; 
 int flushout ; 
 int globalmode ; 
 void intr (int) ; 
 void intr2 (int) ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int localchars ; 
 struct termio new_tc ; 
 struct ltchars nltc ; 
 struct tchars ntc ; 
 struct sgttyb nttyb ; 
 struct termio old_tc ; 
 int olmode ; 
 struct ltchars oltc ; 
 struct tchars otc ; 
 struct sgttyb ottyb ; 
 scalar_t__ restartany ; 
 scalar_t__ rlogin ; 
 int sigblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int,void (*) (int)) ; 
 int /*<<< orphan*/  sigrelse (int) ; 
 int /*<<< orphan*/  sigsetmask (int) ; 
 void susp (int) ; 
 int /*<<< orphan*/  tcgetattr (int /*<<< orphan*/ ,struct termio*) ; 
 scalar_t__ tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct termio*) ; 
 int /*<<< orphan*/  tin ; 
 int /*<<< orphan*/  tout ; 
 int ttyflush (int) ; 

void
TerminalNewMode(int f)
{
    static int prevmode = 0;
#ifndef	USE_TERMIO
    struct tchars tc;
    struct ltchars ltc;
    struct sgttyb sb;
    int lmode;
#else	/* USE_TERMIO */
    struct termio tmp_tc;
#endif	/* USE_TERMIO */
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
#ifndef	USE_TERMIO
     * We would really like ask the kernel to wait for the output
     * to drain, like we can do with the TCSADRAIN, but we don't have
     * that option.  The only ioctl that waits for the output to
     * drain, TIOCSETP, also flushes the input queue, which is NOT
     * what we want (TIOCSETP is like TCSADFLUSH).
#endif
     */
    old = ttyflush(SYNCHing|flushout);
    if (old < 0 || old > 1) {
#ifdef	USE_TERMIO
	tcgetattr(tin, &tmp_tc);
#endif	/* USE_TERMIO */
	do {
	    /*
	     * Wait for data to drain, then flush again.
	     */
#ifdef	USE_TERMIO
	    tcsetattr(tin, TCSADRAIN, &tmp_tc);
#endif	/* USE_TERMIO */
	    old = ttyflush(SYNCHing|flushout);
	} while (old < 0 || old > 1);
    }

    old = prevmode;
    prevmode = f&~MODE_FORCE;
#ifndef	USE_TERMIO
    sb = nttyb;
    tc = ntc;
    ltc = nltc;
    lmode = olmode;
#else
    tmp_tc = new_tc;
#endif

    if (f&MODE_ECHO) {
#ifndef	USE_TERMIO
	sb.sg_flags |= ECHO;
#else
	tmp_tc.c_lflag |= ECHO;
	tmp_tc.c_oflag |= ONLCR;
	if (crlf)
		tmp_tc.c_iflag |= ICRNL;
#endif
    } else {
#ifndef	USE_TERMIO
	sb.sg_flags &= ~ECHO;
#else
	tmp_tc.c_lflag &= ~ECHO;
	tmp_tc.c_oflag &= ~ONLCR;
#endif
    }

    if ((f&MODE_FLOW) == 0) {
#ifndef	USE_TERMIO
	tc.t_startc = _POSIX_VDISABLE;
	tc.t_stopc = _POSIX_VDISABLE;
#else
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
#endif
    }

    if ((f&MODE_TRAPSIG) == 0) {
#ifndef	USE_TERMIO
	tc.t_intrc = _POSIX_VDISABLE;
	tc.t_quitc = _POSIX_VDISABLE;
	tc.t_eofc = _POSIX_VDISABLE;
	ltc.t_suspc = _POSIX_VDISABLE;
	ltc.t_dsuspc = _POSIX_VDISABLE;
#else
	tmp_tc.c_lflag &= ~ISIG;
#endif
	localchars = 0;
    } else {
#ifdef	USE_TERMIO
	tmp_tc.c_lflag |= ISIG;
#endif
	localchars = 1;
    }

    if (f&MODE_EDIT) {
#ifndef	USE_TERMIO
	sb.sg_flags &= ~CBREAK;
	sb.sg_flags |= CRMOD;
#else
	tmp_tc.c_lflag |= ICANON;
#endif
    } else {
#ifndef	USE_TERMIO
	sb.sg_flags |= CBREAK;
	if (f&MODE_ECHO)
	    sb.sg_flags |= CRMOD;
	else
	    sb.sg_flags &= ~CRMOD;
#else
	tmp_tc.c_lflag &= ~ICANON;
	tmp_tc.c_iflag &= ~ICRNL;
	tmp_tc.c_cc[VMIN] = 1;
	tmp_tc.c_cc[VTIME] = 0;
#endif
    }

    if ((f&(MODE_EDIT|MODE_TRAPSIG)) == 0) {
#ifndef	USE_TERMIO
	ltc.t_lnextc = _POSIX_VDISABLE;
#else
# ifdef VLNEXT
	tmp_tc.c_cc[VLNEXT] = (cc_t)(_POSIX_VDISABLE);
# endif
#endif
    }

    if (f&MODE_SOFT_TAB) {
#ifndef USE_TERMIO
	sb.sg_flags |= XTABS;
#else
# ifdef	OXTABS
	tmp_tc.c_oflag |= OXTABS;
# endif
# ifdef	TABDLY
	tmp_tc.c_oflag &= ~TABDLY;
	tmp_tc.c_oflag |= TAB3;
# endif
#endif
    } else {
#ifndef USE_TERMIO
	sb.sg_flags &= ~XTABS;
#else
# ifdef	OXTABS
	tmp_tc.c_oflag &= ~OXTABS;
# endif
# ifdef	TABDLY
	tmp_tc.c_oflag &= ~TABDLY;
# endif
#endif
    }

    if (f&MODE_LIT_ECHO) {
#ifndef USE_TERMIO
	lmode &= ~LCTLECH;
#else
# ifdef	ECHOCTL
	tmp_tc.c_lflag &= ~ECHOCTL;
# endif
#endif
    } else {
#ifndef USE_TERMIO
	lmode |= LCTLECH;
#else
# ifdef	ECHOCTL
	tmp_tc.c_lflag |= ECHOCTL;
# endif
#endif
    }

    if (f == -1) {
	onoff = 0;
    } else {
#ifndef	USE_TERMIO
	if (f & MODE_OUTBIN)
		lmode |= LLITOUT;
	else
		lmode &= ~LLITOUT;

	if (f & MODE_INBIN)
		lmode |= LPASS8;
	else
		lmode &= ~LPASS8;
#else
	if (f & MODE_INBIN)
		tmp_tc.c_iflag &= ~ISTRIP;
	else
		tmp_tc.c_iflag |= ISTRIP;
	if (f & MODE_OUTBIN) {
		tmp_tc.c_cflag &= ~(CSIZE|PARENB);
		tmp_tc.c_cflag |= CS8;
		tmp_tc.c_oflag &= ~OPOST;
	} else {
		tmp_tc.c_cflag &= ~(CSIZE|PARENB);
		tmp_tc.c_cflag |= old_tc.c_cflag & (CSIZE|PARENB);
		tmp_tc.c_oflag |= OPOST;
	}
#endif
	onoff = 1;
    }

    if (f != -1) {
#ifdef  SIGINT
	(void) signal(SIGINT, intr);
#endif
#ifdef  SIGQUIT
	(void) signal(SIGQUIT, intr2);
#endif
#ifdef	SIGTSTP
	(void) signal(SIGTSTP, susp);
#endif	/* SIGTSTP */
#ifdef	SIGINFO
	(void) signal(SIGINFO, ayt);
#endif
#if	defined(USE_TERMIO) && defined(NOKERNINFO)
	tmp_tc.c_lflag |= NOKERNINFO;
#endif
	/*
	 * We don't want to process ^Y here.  It's just another
	 * character that we'll pass on to the back end.  It has
	 * to process it because it will be processed when the
	 * user attempts to read it, not when we send it.
	 */
#ifndef	USE_TERMIO
	ltc.t_dsuspc = _POSIX_VDISABLE;
#else
# ifdef	VDSUSP
	tmp_tc.c_cc[VDSUSP] = (cc_t)(_POSIX_VDISABLE);
# endif
#endif
#ifdef	USE_TERMIO
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
#else
	if (tc.t_brkc == (cc_t)(_POSIX_VDISABLE))
		tc.t_brkc = esc;
#endif
    } else {
#ifdef	SIGINFO
	(void) signal(SIGINFO, (void (*)(int))ayt_status);
#endif
#ifdef  SIGINT
	(void) signal(SIGINT, SIG_DFL);
#endif
#ifdef  SIGQUIT
	(void) signal(SIGQUIT, SIG_DFL);
#endif
#ifdef	SIGTSTP
	(void) signal(SIGTSTP, SIG_DFL);
# ifndef SOLARIS
	(void) sigsetmask(sigblock(0) & ~(1<<(SIGTSTP-1)));
# else	/* SOLARIS */
	(void) sigrelse(SIGTSTP);
# endif	/* SOLARIS */
#endif	/* SIGTSTP */
#ifndef USE_TERMIO
	ltc = oltc;
	tc = otc;
	sb = ottyb;
	lmode = olmode;
#else
	tmp_tc = old_tc;
#endif
    }
#ifndef USE_TERMIO
    ioctl(tin, TIOCLSET, (char *)&lmode);
    ioctl(tin, TIOCSLTC, (char *)&ltc);
    ioctl(tin, TIOCSETC, (char *)&tc);
    ioctl(tin, TIOCSETN, (char *)&sb);
#else
    if (tcsetattr(tin, TCSADRAIN, &tmp_tc) < 0)
	tcsetattr(tin, TCSANOW, &tmp_tc);
#endif

    ioctl(tin, FIONBIO, (char *)&onoff);
    ioctl(tout, FIONBIO, (char *)&onoff);

}