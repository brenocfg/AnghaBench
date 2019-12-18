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
struct termios {int /*<<< orphan*/  c_cflag; } ;
typedef  int /*<<< orphan*/  sig_t ;

/* Variables and functions */
 int /*<<< orphan*/  DC ; 
 scalar_t__ FD ; 
 int /*<<< orphan*/  HUPCL ; 
 int /*<<< orphan*/  HW ; 
 int O_NONBLOCK ; 
 int O_RDWR ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  TCSAFLUSH ; 
 int /*<<< orphan*/  TIOCEXCL ; 
 int /*<<< orphan*/  alarm (int) ; 
 scalar_t__ boolean (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dead ; 
 int deadfl ; 
 int /*<<< orphan*/  deadline ; 
 char* getremote (char*) ; 
 int /*<<< orphan*/  ioctl (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ open (char*,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  tcgetattr (scalar_t__,struct termios*) ; 
 int /*<<< orphan*/  tcsetattr (scalar_t__,int /*<<< orphan*/ ,struct termios*) ; 
 scalar_t__ uu_lock (char*) ; 
 int /*<<< orphan*/  uu_unlock (char*) ; 
 char* uucplock ; 
 int /*<<< orphan*/  value (int /*<<< orphan*/ ) ; 

long
hunt(char *name)
{
	char *cp;
	sig_t f;

	f = signal(SIGALRM, dead);
	while ((cp = getremote(name))) {
		deadfl = 0;
		uucplock = strrchr(cp, '/');
		if (uucplock == NULL)
			uucplock = cp;
		else
			uucplock++;

		if (uu_lock(uucplock) < 0)
			continue;
		/*
		 * Straight through call units, such as the BIZCOMP,
		 * VADIC and the DF, must indicate they're hardwired in
		 *  order to get an open file descriptor placed in FD.
		 * Otherwise, as for a DN-11, the open will have to
		 *  be done in the "open" routine.
		 */
		if (!HW)
			break;
		if (setjmp(deadline) == 0) {
			alarm(10);
			FD = open(cp, (O_RDWR |
			    (boolean(value(DC)) ? O_NONBLOCK : 0)));
		}
		alarm(0);
		if (FD < 0) {
			perror(cp);
			deadfl = 1;
		}
		if (!deadfl) {
			struct termios cntrl;

			tcgetattr(FD, &cntrl);
			if (!boolean(value(DC)))
				cntrl.c_cflag |= HUPCL;
			tcsetattr(FD, TCSAFLUSH, &cntrl);
			ioctl(FD, TIOCEXCL, 0);
			signal(SIGALRM, SIG_DFL);
			return ((long)cp);
		}
		(void)uu_unlock(uucplock);
	}
	signal(SIGALRM, f);
	return (deadfl ? -1 : (long)cp);
}