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

/* Variables and functions */
 char* DV ; 
 scalar_t__ EBUSY ; 
 scalar_t__ EIO ; 
 int /*<<< orphan*/  FD ; 
 int /*<<< orphan*/  HUPCL ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  TCSANOW ; 
 int /*<<< orphan*/  VERBOSE ; 
 int /*<<< orphan*/  alarm (int) ; 
 int /*<<< orphan*/  alarmtr ; 
 scalar_t__ boolean (int /*<<< orphan*/ ) ; 
 int child ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dn ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int fork () ; 
 int /*<<< orphan*/  jmpbuf ; 
 int /*<<< orphan*/  kill (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open (char*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  stdout ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  tcgetattr (int /*<<< orphan*/ ,struct termios*) ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct termios*) ; 
 int /*<<< orphan*/  value (int /*<<< orphan*/ ) ; 
 int wait (int*) ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 

int
dn_dialer(char *num, char *acu)
{
	int lt, nw;
	int timelim;
	struct termios cntrl;

	if (boolean(value(VERBOSE)))
		printf("\nstarting call...");
	if ((dn = open(acu, 1)) < 0) {
		if (errno == EBUSY)
			printf("line busy...");
		else
			printf("acu open error...");
		return (0);
	}
	if (setjmp(jmpbuf)) {
		kill(child, SIGKILL);
		close(dn);
		return (0);
	}
	signal(SIGALRM, alarmtr);
	timelim = 5 * strlen(num);
	alarm(timelim < 30 ? 30 : timelim);
	if ((child = fork()) == 0) {
		/*
		 * ignore this stuff for aborts
		 */
		signal(SIGALRM, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		sleep(2);
		nw = write(dn, num, lt = strlen(num));
		exit(nw != lt);
	}
	/*
	 * open line - will return on carrier
	 */
	if ((FD = open(DV, 2)) < 0) {
		if (errno == EIO)
			printf("lost carrier...");
		else
			printf("dialup line open failed...");
		alarm(0);
		kill(child, SIGKILL);
		close(dn);
		return (0);
	}
	alarm(0);
	tcgetattr(dn, &cntrl);
	cntrl.c_cflag |= HUPCL;
	tcsetattr(dn, TCSANOW, &cntrl);
	signal(SIGALRM, SIG_DFL);
	while ((nw = wait(&lt)) != child && nw != -1)
		;
	fflush(stdout);
	close(dn);
	if (lt != 0) {
		close(FD);
		return (0);
	}
	return (1);
}