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
struct sigaction {int /*<<< orphan*/  sa_sigaction; int /*<<< orphan*/  sa_flags; int /*<<< orphan*/  sa_mask; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  SA_SIGINFO ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGSTOP ; 
 scalar_t__ cont_received ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ exit_received ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 int getpid () ; 
 int /*<<< orphan*/  job_handler ; 
 int /*<<< orphan*/  kill (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ stop_received ; 

void
job_control_test(void)
{
	struct sigaction sa;
	pid_t pid;
	int count = 10;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = job_handler;
	sigaction(SIGCHLD, &sa, NULL);
	stop_received = 0;
	cont_received = 0;
	exit_received = 0;
	fflush(stdout);
	pid = fork();
	if (pid == 0) {
		printf("child %d\n", getpid());
		kill(getpid(), SIGSTOP);
		sleep(2);
		exit(1);
	}

	while (!(cont_received && stop_received && exit_received)) {
		sleep(1);
		if (--count == 0)
			break;
	}
	if (!(cont_received && stop_received && exit_received))
		errx(1, "job signals lost");

	printf("job control test OK.\n");
}