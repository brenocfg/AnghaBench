#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct thread {int /*<<< orphan*/  td_oncpu; int /*<<< orphan*/  td_lastcpu; TYPE_3__* td_lock; } ;
struct tdq {int dummy; } ;
struct TYPE_6__ {uintptr_t mtx_lock; int /*<<< orphan*/  lock_object; } ;
struct TYPE_4__ {int md_spinlock_count; } ;
struct TYPE_5__ {TYPE_1__ td_md; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPCPU_PTR (struct tdq*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  NOCPU ; 
 int /*<<< orphan*/  PCPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TDQ_LOCK (struct tdq*) ; 
 TYPE_3__* TDQ_LOCKPTR (struct tdq*) ; 
 struct tdq* TDQ_SELF () ; 
 struct thread* choosethread () ; 
 int /*<<< orphan*/  cpu_throw (struct thread*,struct thread*) ; 
 int /*<<< orphan*/  cpu_ticks () ; 
 TYPE_2__* curthread ; 
 int /*<<< orphan*/  lock_profile_release_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sched ; 
 int /*<<< orphan*/  spinlock_exit () ; 
 int /*<<< orphan*/  switchticks ; 
 int /*<<< orphan*/  switchtime ; 
 int /*<<< orphan*/  tdq_load_rem (struct tdq*,struct thread*) ; 
 int /*<<< orphan*/  ticks ; 

void
sched_throw(struct thread *td)
{
	struct thread *newtd;
	struct tdq *tdq;

	if (td == NULL) {
#ifdef SMP
		PCPU_SET(sched, DPCPU_PTR(tdq));
#endif
		/* Correct spinlock nesting and acquire the correct lock. */
		tdq = TDQ_SELF();
		TDQ_LOCK(tdq);
		spinlock_exit();
		PCPU_SET(switchtime, cpu_ticks());
		PCPU_SET(switchticks, ticks);
	} else {
		tdq = TDQ_SELF();
		MPASS(td->td_lock == TDQ_LOCKPTR(tdq));
		tdq_load_rem(tdq, td);
		lock_profile_release_lock(&TDQ_LOCKPTR(tdq)->lock_object);
		td->td_lastcpu = td->td_oncpu;
		td->td_oncpu = NOCPU;
	}
	KASSERT(curthread->td_md.md_spinlock_count == 1, ("invalid count"));
	newtd = choosethread();
	TDQ_LOCKPTR(tdq)->mtx_lock = (uintptr_t)newtd;
	cpu_throw(td, newtd);		/* doesn't return */
}