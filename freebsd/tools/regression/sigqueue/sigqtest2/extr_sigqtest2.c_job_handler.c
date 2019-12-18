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
struct TYPE_3__ {scalar_t__ si_code; int si_pid; } ;
typedef  TYPE_1__ siginfo_t ;

/* Variables and functions */
 scalar_t__ CLD_CONTINUED ; 
 scalar_t__ CLD_EXITED ; 
 scalar_t__ CLD_STOPPED ; 
 int /*<<< orphan*/  SIGCONT ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 int cont_received ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int exit_received ; 
 int /*<<< orphan*/  kill (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int stop_received ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

void
job_handler(int sig, siginfo_t *si, void *ctx)
{
	int status;
	int ret;

	if (si->si_code == CLD_STOPPED) {
		printf("%d: stop received\n", si->si_pid);
		stop_received = 1;
		kill(si->si_pid, SIGCONT);
	} else if (si->si_code == CLD_EXITED) {
		printf("%d: exit received\n", si->si_pid);
		ret = waitpid(si->si_pid, &status, 0);
		if (ret == -1)
			errx(1, "waitpid");
		if (!WIFEXITED(status))
			errx(1, "!WIFEXITED(status)");
		exit_received = 1;
	} else if (si->si_code == CLD_CONTINUED) {
		printf("%d: cont received\n", si->si_pid);
		cont_received = 1;
	}
}