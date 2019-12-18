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
struct thread {size_t td_oncpu; int td_owepreempt; int /*<<< orphan*/  td_critnest; } ;
struct TYPE_2__ {int lo_flags; } ;
struct rmlock {TYPE_1__ lock_object; } ;
struct rm_priotracker {int rmp_flags; struct thread* rmp_thread; } ;
struct pcpu {int dummy; } ;

/* Variables and functions */
 int LO_SLEEPABLE ; 
 scalar_t__ SCHEDULER_STOPPED () ; 
 int /*<<< orphan*/  THREAD_SLEEPING_OK () ; 
 scalar_t__ __predict_true (int) ; 
 int /*<<< orphan*/  _rm_unlock_hard (struct thread*,struct rm_priotracker*) ; 
 struct pcpu** cpuid_to_pcpu ; 
 int /*<<< orphan*/  rm_tracker_remove (struct pcpu*,struct rm_priotracker*) ; 
 int /*<<< orphan*/  sched_unpin () ; 

void
_rm_runlock(struct rmlock *rm, struct rm_priotracker *tracker)
{
	struct pcpu *pc;
	struct thread *td = tracker->rmp_thread;

	if (SCHEDULER_STOPPED())
		return;

	td->td_critnest++;	/* critical_enter(); */
	pc = cpuid_to_pcpu[td->td_oncpu]; /* pcpu_find(td->td_oncpu); */
	rm_tracker_remove(pc, tracker);
	td->td_critnest--;
	sched_unpin();

	if (rm->lock_object.lo_flags & LO_SLEEPABLE)
		THREAD_SLEEPING_OK();

	if (__predict_true(0 == (td->td_owepreempt | tracker->rmp_flags)))
		return;

	_rm_unlock_hard(td, tracker);
}