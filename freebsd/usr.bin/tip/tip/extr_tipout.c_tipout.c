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
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  BEAUTIFY ; 
 int BUFSIZ ; 
 scalar_t__ EIO ; 
 scalar_t__ ENXIO ; 
 int /*<<< orphan*/  EXCEPTIONS ; 
 int /*<<< orphan*/  FD ; 
 int /*<<< orphan*/  SCRIPT ; 
 int /*<<< orphan*/  SIGEMT ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGIOT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGSYS ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_IGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 char STRIP_PAR ; 
 scalar_t__ any (char,int /*<<< orphan*/ ) ; 
 scalar_t__ boolean (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fscript ; 
 int /*<<< orphan*/  fwrite (char*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intEMT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intIOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intSYS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intTERM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isgraph (char) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ *) ; 
 size_t read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigbuf ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,size_t) ; 

void
tipout(void)
{
	char buf[BUFSIZ];
	char *cp;
	ssize_t scnt;
	size_t cnt;
	sigset_t mask, omask;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGEMT, intEMT);		/* attention from TIPIN */
	signal(SIGTERM, intTERM);	/* time to go signal */
	signal(SIGIOT, intIOT);		/* scripting going on signal */
	signal(SIGHUP, intTERM);	/* for dial-ups */
	signal(SIGSYS, intSYS);		/* beautify toggle */
	(void) setjmp(sigbuf);
	sigprocmask(SIG_BLOCK, NULL, &omask);
	for (;;) {
		sigprocmask(SIG_SETMASK, &omask, NULL);
		scnt = read(FD, buf, BUFSIZ);
		if (scnt <= 0) {
			/* lost carrier */
			if (scnt == 0 ||
			    (scnt < 0 && (errno == EIO || errno == ENXIO))) {
				sigemptyset(&mask);
				sigaddset(&mask, SIGTERM);
				sigprocmask(SIG_BLOCK, &mask, NULL);
				intTERM(SIGHUP);
				/*NOTREACHED*/
			}
			continue;
		}
		cnt = scnt;
		sigemptyset(&mask);
		sigaddset(&mask, SIGEMT);
		sigaddset(&mask, SIGTERM);
		sigaddset(&mask, SIGIOT);
		sigaddset(&mask, SIGSYS);
		sigprocmask(SIG_BLOCK, &mask, NULL);
		for (cp = buf; cp < buf + cnt; cp++)
			*cp &= STRIP_PAR;
		write(STDOUT_FILENO, buf, cnt);
		if (boolean(value(SCRIPT)) && fscript != NULL) {
			if (!boolean(value(BEAUTIFY))) {
				fwrite(buf, 1, cnt, fscript);
			} else {
				for (cp = buf; cp < buf + cnt; cp++)
					if ((*cp >= ' ' && *cp <= '~') ||
					    any(*cp, value(EXCEPTIONS)))
						putc(*cp, fscript);
			}
			for (cp = buf; cp < buf + cnt; cp++) {
				if (!isgraph(*cp)) {
					fflush(fscript);
					break;
				}
			}
		}
	}
}