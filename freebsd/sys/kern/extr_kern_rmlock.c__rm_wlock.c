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
struct turnstile {int dummy; } ;
struct TYPE_2__ {int lo_flags; } ;
struct rmlock {TYPE_1__ lock_object; int /*<<< orphan*/  rm_activeReaders; void* rm_writecpus; int /*<<< orphan*/  rm_lock_mtx; int /*<<< orphan*/  rm_lock_sx; } ;
struct rm_priotracker {int rmp_flags; int /*<<< orphan*/  rmp_thread; } ;
typedef  void* cpuset_t ;

/* Variables and functions */
 scalar_t__ CPU_CMP (void**,void**) ; 
 int /*<<< orphan*/  CPU_NAND (void**,void**) ; 
 struct rm_priotracker* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int LO_SLEEPABLE ; 
 int RMPF_ONQUEUE ; 
 int RMPF_SIGNAL ; 
 scalar_t__ SCHEDULER_STOPPED () ; 
 int /*<<< orphan*/  TS_EXCLUSIVE_QUEUE ; 
 void* all_cpus ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rm_cleanIPI (struct rmlock*) ; 
 int /*<<< orphan*/  rm_spinlock ; 
 int /*<<< orphan*/  smp_no_rendezvous_barrier ; 
 int /*<<< orphan*/  smp_rendezvous_cpus (void*,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (struct rmlock*),int /*<<< orphan*/ ,struct rmlock*) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 struct turnstile* turnstile_trywait (TYPE_1__*) ; 
 int /*<<< orphan*/  turnstile_wait (struct turnstile*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
_rm_wlock(struct rmlock *rm)
{
	struct rm_priotracker *prio;
	struct turnstile *ts;
	cpuset_t readcpus;

	if (SCHEDULER_STOPPED())
		return;

	if (rm->lock_object.lo_flags & LO_SLEEPABLE)
		sx_xlock(&rm->rm_lock_sx);
	else
		mtx_lock(&rm->rm_lock_mtx);

	if (CPU_CMP(&rm->rm_writecpus, &all_cpus)) {
		/* Get all read tokens back */
		readcpus = all_cpus;
		CPU_NAND(&readcpus, &rm->rm_writecpus);
		rm->rm_writecpus = all_cpus;

		/*
		 * Assumes rm->rm_writecpus update is visible on other CPUs
		 * before rm_cleanIPI is called.
		 */
#ifdef SMP
		smp_rendezvous_cpus(readcpus,
		    smp_no_rendezvous_barrier,
		    rm_cleanIPI,
		    smp_no_rendezvous_barrier,
		    rm);

#else
		rm_cleanIPI(rm);
#endif

		mtx_lock_spin(&rm_spinlock);
		while ((prio = LIST_FIRST(&rm->rm_activeReaders)) != NULL) {
			ts = turnstile_trywait(&rm->lock_object);
			prio->rmp_flags = RMPF_ONQUEUE | RMPF_SIGNAL;
			mtx_unlock_spin(&rm_spinlock);
			turnstile_wait(ts, prio->rmp_thread,
			    TS_EXCLUSIVE_QUEUE);
			mtx_lock_spin(&rm_spinlock);
		}
		mtx_unlock_spin(&rm_spinlock);
	}
}