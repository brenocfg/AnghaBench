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
struct thread {int dummy; } ;
struct linux_kill_args {scalar_t__ signum; int /*<<< orphan*/  pid; } ;
struct kill_args {int /*<<< orphan*/  pid; scalar_t__ signum; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LINUX_SIG_VALID (scalar_t__) ; 
 scalar_t__ linux_to_bsd_signal (scalar_t__) ; 
 int sys_kill (struct thread*,struct kill_args*) ; 

int
linux_kill(struct thread *td, struct linux_kill_args *args)
{
	struct kill_args /* {
	    int pid;
	    int signum;
	} */ tmp;

	/*
	 * Allow signal 0 as a means to check for privileges
	 */
	if (!LINUX_SIG_VALID(args->signum) && args->signum != 0)
		return (EINVAL);

	if (args->signum > 0)
		tmp.signum = linux_to_bsd_signal(args->signum);
	else
		tmp.signum = 0;

	tmp.pid = args->pid;
	return (sys_kill(td, &tmp));
}