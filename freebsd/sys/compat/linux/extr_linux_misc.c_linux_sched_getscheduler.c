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
struct thread {int /*<<< orphan*/ * td_retval; int /*<<< orphan*/  td_proc; } ;
struct linux_sched_getscheduler_args {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int ESRCH ; 
 int /*<<< orphan*/  LINUX_SCHED_FIFO ; 
 int /*<<< orphan*/  LINUX_SCHED_OTHER ; 
 int /*<<< orphan*/  LINUX_SCHED_RR ; 
 int /*<<< orphan*/  PROC_UNLOCK (int /*<<< orphan*/ ) ; 
#define  SCHED_FIFO 130 
#define  SCHED_OTHER 129 
#define  SCHED_RR 128 
 int kern_sched_getscheduler (struct thread*,struct thread*,int*) ; 
 struct thread* linux_tdfind (struct thread*,int /*<<< orphan*/ ,int) ; 

int
linux_sched_getscheduler(struct thread *td,
    struct linux_sched_getscheduler_args *args)
{
	struct thread *tdt;
	int error, policy;

	tdt = linux_tdfind(td, args->pid, -1);
	if (tdt == NULL)
		return (ESRCH);

	error = kern_sched_getscheduler(td, tdt, &policy);
	PROC_UNLOCK(tdt->td_proc);

	switch (policy) {
	case SCHED_OTHER:
		td->td_retval[0] = LINUX_SCHED_OTHER;
		break;
	case SCHED_FIFO:
		td->td_retval[0] = LINUX_SCHED_FIFO;
		break;
	case SCHED_RR:
		td->td_retval[0] = LINUX_SCHED_RR;
		break;
	}
	return (error);
}