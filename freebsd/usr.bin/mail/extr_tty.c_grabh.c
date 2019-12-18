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
struct termios {int c_lflag; void** c_cc; } ;
struct header {int /*<<< orphan*/ * h_bcc; int /*<<< orphan*/ * h_cc; int /*<<< orphan*/ * h_subject; int /*<<< orphan*/ * h_to; } ;
typedef  int /*<<< orphan*/  sig_t ;

/* Variables and functions */
 int EXTPROC ; 
 int GBCC ; 
 int GCC ; 
 int GSUBJECT ; 
 int GTO ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTSTP ; 
 int /*<<< orphan*/  SIGTTIN ; 
 int /*<<< orphan*/  SIGTTOU ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  TCSADRAIN ; 
 int /*<<< orphan*/  TIOCEXT ; 
 size_t VERASE ; 
 size_t VKILL ; 
 void* _POSIX_VDISABLE ; 
 void* c_erase ; 
 void* c_kill ; 
 int /*<<< orphan*/ * detract (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* extract (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intjmp ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * readtty (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ tcgetattr (int /*<<< orphan*/ ,struct termios*) ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct termios*) ; 
 int /*<<< orphan*/  ttyint ; 
 scalar_t__ ttyset ; 
 int /*<<< orphan*/  warn (char*) ; 

int
grabh(struct header *hp, int gflags)
{
	struct termios ttybuf;
	sig_t saveint;
	sig_t savetstp;
	sig_t savettou;
	sig_t savettin;
	int errs;
#ifndef TIOCSTI
	sig_t savequit;
#else
# ifdef TIOCEXT
	int extproc, flag;
# endif /* TIOCEXT */
#endif /* TIOCSTI */

	savetstp = signal(SIGTSTP, SIG_DFL);
	savettou = signal(SIGTTOU, SIG_DFL);
	savettin = signal(SIGTTIN, SIG_DFL);
	errs = 0;
#ifndef TIOCSTI
	ttyset = 0;
#endif
	if (tcgetattr(fileno(stdin), &ttybuf) < 0) {
		warn("tcgetattr(stdin)");
		return (-1);
	}
	c_erase = ttybuf.c_cc[VERASE];
	c_kill = ttybuf.c_cc[VKILL];
#ifndef TIOCSTI
	ttybuf.c_cc[VERASE] = _POSIX_VDISABLE;
	ttybuf.c_cc[VKILL] = _POSIX_VDISABLE;
	if ((saveint = signal(SIGINT, SIG_IGN)) == SIG_DFL)
		(void)signal(SIGINT, SIG_DFL);
	if ((savequit = signal(SIGQUIT, SIG_IGN)) == SIG_DFL)
		(void)signal(SIGQUIT, SIG_DFL);
#else
# ifdef		TIOCEXT
	extproc = ((ttybuf.c_lflag & EXTPROC) ? 1 : 0);
	if (extproc) {
		flag = 0;
		if (ioctl(fileno(stdin), TIOCEXT, &flag) < 0)
			warn("TIOCEXT: off");
	}
# endif	/* TIOCEXT */
	if (setjmp(intjmp))
		goto out;
	saveint = signal(SIGINT, ttyint);
#endif
	if (gflags & GTO) {
#ifndef TIOCSTI
		if (!ttyset && hp->h_to != NULL)
			ttyset++, tcsetattr(fileno(stdin), TCSADRAIN, &ttybuf);
#endif
		hp->h_to =
			extract(readtty("To: ", detract(hp->h_to, 0)), GTO);
	}
	if (gflags & GSUBJECT) {
#ifndef TIOCSTI
		if (!ttyset && hp->h_subject != NULL)
			ttyset++, tcsetattr(fileno(stdin), TCSADRAIN, &ttybuf);
#endif
		hp->h_subject = readtty("Subject: ", hp->h_subject);
	}
	if (gflags & GCC) {
#ifndef TIOCSTI
		if (!ttyset && hp->h_cc != NULL)
			ttyset++, tcsetattr(fileno(stdin), TCSADRAIN, &ttybuf);
#endif
		hp->h_cc =
			extract(readtty("Cc: ", detract(hp->h_cc, 0)), GCC);
	}
	if (gflags & GBCC) {
#ifndef TIOCSTI
		if (!ttyset && hp->h_bcc != NULL)
			ttyset++, tcsetattr(fileno(stdin), TCSADRAIN, &ttybuf);
#endif
		hp->h_bcc =
			extract(readtty("Bcc: ", detract(hp->h_bcc, 0)), GBCC);
	}
out:
	(void)signal(SIGTSTP, savetstp);
	(void)signal(SIGTTOU, savettou);
	(void)signal(SIGTTIN, savettin);
#ifndef TIOCSTI
	ttybuf.c_cc[VERASE] = c_erase;
	ttybuf.c_cc[VKILL] = c_kill;
	if (ttyset)
		tcsetattr(fileno(stdin), TCSADRAIN, &ttybuf);
	(void)signal(SIGQUIT, savequit);
#else
# ifdef		TIOCEXT
	if (extproc) {
		flag = 1;
		if (ioctl(fileno(stdin), TIOCEXT, &flag) < 0)
			warn("TIOCEXT: on");
	}
# endif	/* TIOCEXT */
#endif
	(void)signal(SIGINT, saveint);
	return (errs);
}