#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct thread {struct proc* td_proc; } ;
struct rusage {int /*<<< orphan*/  ru_stime; int /*<<< orphan*/  ru_utime; } ;
struct proc {TYPE_1__* p_stats; } ;
struct TYPE_2__ {struct rusage p_cru; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_STATLOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_STATUNLOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
#define  RUSAGE_CHILDREN 130 
#define  RUSAGE_SELF 129 
#define  RUSAGE_THREAD 128 
 int /*<<< orphan*/  calccru (struct proc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rufetchcalc (struct proc*,struct rusage*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rufetchtd (struct thread*,struct rusage*) ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 

int
kern_getrusage(struct thread *td, int who, struct rusage *rup)
{
	struct proc *p;
	int error;

	error = 0;
	p = td->td_proc;
	PROC_LOCK(p);
	switch (who) {
	case RUSAGE_SELF:
		rufetchcalc(p, rup, &rup->ru_utime,
		    &rup->ru_stime);
		break;

	case RUSAGE_CHILDREN:
		*rup = p->p_stats->p_cru;
		calccru(p, &rup->ru_utime, &rup->ru_stime);
		break;

	case RUSAGE_THREAD:
		PROC_STATLOCK(p);
		thread_lock(td);
		rufetchtd(td, rup);
		thread_unlock(td);
		PROC_STATUNLOCK(p);
		break;

	default:
		error = EINVAL;
	}
	PROC_UNLOCK(p);
	return (error);
}