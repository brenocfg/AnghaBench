#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ pid; int fd; scalar_t__ sent; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  Exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SIGUSR2 ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int SLAVES ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  X_FINOK ; 
 int /*<<< orphan*/  atomic (int /*<<< orphan*/ ,int,char*,int) ; 
 int caught ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  doslave (int,int) ; 
 int /*<<< orphan*/  dumpabort ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fork () ; 
 scalar_t__ getpid () ; 
 scalar_t__ master ; 
 int /*<<< orphan*/  proceed ; 
 int /*<<< orphan*/  quit (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigpipe ; 
 TYPE_1__* slaves ; 
 TYPE_1__* slp ; 
 scalar_t__ socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tperror ; 
 int /*<<< orphan*/  write ; 

void
enslave(void)
{
	int cmd[2];
	int i, j;

	master = getpid();

	signal(SIGTERM, dumpabort);  /* Slave sends SIGTERM on dumpabort() */
	signal(SIGPIPE, sigpipe);
	signal(SIGUSR1, tperror);    /* Slave sends SIGUSR1 on tape errors */
	signal(SIGUSR2, proceed);    /* Slave sends SIGUSR2 to next slave */

	for (i = 0; i < SLAVES; i++) {
		if (i == slp - &slaves[0]) {
			caught = 1;
		} else {
			caught = 0;
		}

		if (socketpair(AF_UNIX, SOCK_STREAM, 0, cmd) < 0 ||
		    (slaves[i].pid = fork()) < 0)
			quit("too many slaves, %d (recompile smaller): %s\n",
			    i, strerror(errno));

		slaves[i].fd = cmd[1];
		slaves[i].sent = 0;
		if (slaves[i].pid == 0) { 	    /* Slave starts up here */
			for (j = 0; j <= i; j++)
			        (void) close(slaves[j].fd);
			signal(SIGINT, SIG_IGN);    /* Master handles this */
			doslave(cmd[0], i);
			Exit(X_FINOK);
		}
	}

	for (i = 0; i < SLAVES; i++)
		(void) atomic(write, slaves[i].fd,
			      (char *) &slaves[(i + 1) % SLAVES].pid,
		              sizeof slaves[0].pid);

	master = 0;
}