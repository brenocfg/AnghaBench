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

/* Variables and functions */
 int /*<<< orphan*/  TIOCSETD ; 
 int /*<<< orphan*/  daemon_uid () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  kill (scalar_t__,int) ; 
 scalar_t__ odisc ; 
 scalar_t__ tipout_pid ; 
 int /*<<< orphan*/  unraw () ; 
 int /*<<< orphan*/  uu_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uucplock ; 
 int /*<<< orphan*/  wait (int /*<<< orphan*/ *) ; 

void
cleanup(int signo)
{
	daemon_uid();
	(void)uu_unlock(uucplock);
	if (odisc)
		ioctl(0, TIOCSETD, &odisc);
	unraw();
	if (signo && tipout_pid) {
		kill(tipout_pid, signo);
		wait(NULL);
	}
	exit(0);
}