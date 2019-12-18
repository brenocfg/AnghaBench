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
struct thread {int /*<<< orphan*/  td_tid; int /*<<< orphan*/  td_proc; } ;
struct linux_sched_setaffinity_args {int len; scalar_t__ user_mask_ptr; int /*<<< orphan*/  pid; } ;
typedef  int /*<<< orphan*/  cpuset_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_LEVEL_WHICH ; 
 int /*<<< orphan*/  CPU_WHICH_TID ; 
 int EINVAL ; 
 int ESRCH ; 
 int /*<<< orphan*/  PROC_UNLOCK (int /*<<< orphan*/ ) ; 
 int kern_cpuset_setaffinity (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct thread* linux_tdfind (struct thread*,int /*<<< orphan*/ ,int) ; 

int
linux_sched_setaffinity(struct thread *td,
    struct linux_sched_setaffinity_args *args)
{
	struct thread *tdt;

	if (args->len < sizeof(cpuset_t))
		return (EINVAL);

	tdt = linux_tdfind(td, args->pid, -1);
	if (tdt == NULL)
		return (ESRCH);

	PROC_UNLOCK(tdt->td_proc);

	return (kern_cpuset_setaffinity(td, CPU_LEVEL_WHICH, CPU_WHICH_TID,
	    tdt->td_tid, sizeof(cpuset_t), (cpuset_t *) args->user_mask_ptr));
}