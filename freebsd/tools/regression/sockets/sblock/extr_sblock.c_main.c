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
struct sigaction {int sa_flags; int /*<<< orphan*/  sa_handler; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  PF_LOCAL ; 
 int SA_RESTART ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGKILL ; 
 scalar_t__ SIG_ERR ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  blocking_recver (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  kill (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  locking_recver (int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ sigaction (int /*<<< orphan*/ ,struct sigaction*,struct sigaction*) ; 
 scalar_t__ signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_handler ; 
 int /*<<< orphan*/  signaller (scalar_t__,int) ; 
 scalar_t__ socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

int
main(void)
{
	int error, fds[2], recver_fd, sender_fd;
	pid_t blocking_recver_pid;
	pid_t locking_recver_pid;
	struct sigaction sa;

	if (sigaction(SIGHUP, NULL, &sa) < 0)
		err(-1, "FAIL: sigaction(SIGHUP, NULL, &sa)");

	sa.sa_handler = signal_handler;
	if (sa.sa_flags & SA_RESTART)
		printf("SIGHUP restartable by default (cleared)\n");
	sa.sa_flags &= ~SA_RESTART;

	if (sigaction(SIGHUP, &sa, NULL) < 0)
		err(-1, "FAIL: sigaction(SIGHUP, &sa, NULL)");

#if 0
	if (signal(SIGHUP, signal_handler) == SIG_ERR)
		err(-1, "FAIL: signal(SIGHUP)");
#endif

	if (socketpair(PF_LOCAL, SOCK_STREAM, 0, fds) < 0)
		err(-1, "FAIL: socketpair(PF_LOCAL, SOGK_STREAM, 0)");

	sender_fd = fds[0];
	recver_fd = fds[1];

	blocking_recver_pid = fork();
	if (blocking_recver_pid < 0)
		err(-1, "FAIL: fork");
	if (blocking_recver_pid == 0) {
		close(sender_fd);
		blocking_recver(recver_fd);
		exit(0);
	}

	locking_recver_pid = fork();
	if (locking_recver_pid < 0) {
		error = errno;
		kill(blocking_recver_pid, SIGKILL);
		errno = error;
		err(-1, "FAIL: fork");
	}
	if (locking_recver_pid == 0) {
		close(sender_fd);
		locking_recver(recver_fd);
		exit(0);
	}

	signaller(locking_recver_pid, sender_fd);

	kill(blocking_recver_pid, SIGKILL);
	kill(locking_recver_pid, SIGKILL);
	exit(0);
}