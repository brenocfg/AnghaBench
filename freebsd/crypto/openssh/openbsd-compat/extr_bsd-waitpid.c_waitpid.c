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
union wait {scalar_t__ w_status; } ;
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  errno ; 
 int wait4 (int,union wait*,int,int /*<<< orphan*/ *) ; 

pid_t
waitpid(int pid, int *stat_loc, int options)
{
	union wait statusp;
	pid_t wait_pid;

	if (pid <= 0) {
		if (pid != -1) {
			errno = EINVAL;
			return (-1);
		}
		/* wait4() wants pid=0 for indiscriminate wait. */
		pid = 0;
	}
	wait_pid = wait4(pid, &statusp, options, NULL);
	if (stat_loc)
		*stat_loc = (int) statusp.w_status;

	return (wait_pid);
}