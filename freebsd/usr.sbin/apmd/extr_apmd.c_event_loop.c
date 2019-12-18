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
struct timeval {scalar_t__ tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct sigaction {int /*<<< orphan*/  sa_flags; int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  BATT_CHK_INTV ; 
 scalar_t__ EINTR ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SA_RESTART ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int apmctl_fd ; 
 int /*<<< orphan*/  check_battery () ; 
 int /*<<< orphan*/  enque_signal ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct sigaction*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  proc_apmevent (int) ; 
 scalar_t__ proc_signal (int) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeval*) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigfillset (int /*<<< orphan*/ *) ; 
 int* signal_fd ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
event_loop(void)
{
	int		fdmax = 0;
	struct sigaction nsa;
	fd_set          master_rfds;
	sigset_t	sigmask, osigmask;

	FD_ZERO(&master_rfds);
	FD_SET(apmctl_fd, &master_rfds);
	fdmax = apmctl_fd > fdmax ? apmctl_fd : fdmax;

	FD_SET(signal_fd[0], &master_rfds);
	fdmax = signal_fd[0] > fdmax ? signal_fd[0] : fdmax;

	memset(&nsa, 0, sizeof nsa);
	nsa.sa_handler = enque_signal;
	sigfillset(&nsa.sa_mask);
	nsa.sa_flags = SA_RESTART;
	sigaction(SIGHUP, &nsa, NULL);
	sigaction(SIGCHLD, &nsa, NULL);
	sigaction(SIGTERM, &nsa, NULL);

	sigemptyset(&sigmask);
	sigaddset(&sigmask, SIGHUP);
	sigaddset(&sigmask, SIGCHLD);
	sigaddset(&sigmask, SIGTERM);
	sigprocmask(SIG_SETMASK, &sigmask, &osigmask);

	while (1) {
		fd_set rfds;
		int res;
		struct timeval to;

		to.tv_sec = BATT_CHK_INTV;
		to.tv_usec = 0;

		memcpy(&rfds, &master_rfds, sizeof rfds);
		sigprocmask(SIG_SETMASK, &osigmask, NULL);
		if ((res=select(fdmax + 1, &rfds, 0, 0, &to)) < 0) {
			if (errno != EINTR)
				err(1, "select");
		}
		sigprocmask(SIG_SETMASK, &sigmask, NULL);

		if (res == 0) { /* time to check the battery */
			check_battery();
			continue;
		}

		if (FD_ISSET(signal_fd[0], &rfds)) {
			if (proc_signal(signal_fd[0]) < 0)
				return;
		}

		if (FD_ISSET(apmctl_fd, &rfds))
			proc_apmevent(apmctl_fd);
	}
}