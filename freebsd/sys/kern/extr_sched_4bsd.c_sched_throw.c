#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct thread {int /*<<< orphan*/  td_oncpu; int /*<<< orphan*/  td_lastcpu; TYPE_2__* td_lock; } ;
struct TYPE_6__ {int md_spinlock_count; } ;
struct TYPE_8__ {TYPE_1__ td_md; } ;
struct TYPE_7__ {int /*<<< orphan*/  lock_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  NOCPU ; 
 int /*<<< orphan*/  PCPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  choosethread () ; 
 int /*<<< orphan*/  cpu_throw (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_ticks () ; 
 TYPE_5__* curthread ; 
 int /*<<< orphan*/  lock_profile_release_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_assert (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock_spin (TYPE_2__*) ; 
 TYPE_2__ sched_lock ; 
 int /*<<< orphan*/  spinlock_exit () ; 
 int /*<<< orphan*/  switchticks ; 
 int /*<<< orphan*/  switchtime ; 
 int /*<<< orphan*/  ticks ; 

void
sched_throw(struct thread *td)
{
	/*
	 * Correct spinlock nesting.  The idle thread context that we are
	 * borrowing was created so that it would start out with a single
	 * spin lock (sched_lock) held in fork_trampoline().  Since we've
	 * explicitly acquired locks in this function, the nesting count
	 * is now 2 rather than 1.  Since we are nested, calling
	 * spinlock_exit() will simply adjust the counts without allowing
	 * spin lock using code to interrupt us.
	 */
	if (td == NULL) {
		mtx_lock_spin(&sched_lock);
		spinlock_exit();
		PCPU_SET(switchtime, cpu_ticks());
		PCPU_SET(switchticks, ticks);
	} else {
		lock_profile_release_lock(&sched_lock.lock_object);
		MPASS(td->td_lock == &sched_lock);
		td->td_lastcpu = td->td_oncpu;
		td->td_oncpu = NOCPU;
	}
	mtx_assert(&sched_lock, MA_OWNED);
	KASSERT(curthread->td_md.md_spinlock_count == 1, ("invalid count"));
	cpu_throw(td, choosethread());	/* doesn't return */
}