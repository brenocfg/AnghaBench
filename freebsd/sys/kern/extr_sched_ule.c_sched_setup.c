#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tdq {int /*<<< orphan*/  tdq_lowpri; } ;
struct TYPE_3__ {int /*<<< orphan*/  td_priority; int /*<<< orphan*/  td_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  TDQ_LOCK (struct tdq*) ; 
 int /*<<< orphan*/  TDQ_LOCKPTR (struct tdq*) ; 
 struct tdq* TDQ_SELF () ; 
 int /*<<< orphan*/  TDQ_UNLOCK (struct tdq*) ; 
 int /*<<< orphan*/  sched_setup_smp () ; 
 int /*<<< orphan*/  tdq_load_add (struct tdq*,TYPE_1__*) ; 
 int /*<<< orphan*/  tdq_setup (struct tdq*,int /*<<< orphan*/ ) ; 
 TYPE_1__ thread0 ; 

__attribute__((used)) static void
sched_setup(void *dummy)
{
	struct tdq *tdq;

#ifdef SMP
	sched_setup_smp();
#else
	tdq_setup(TDQ_SELF(), 0);
#endif
	tdq = TDQ_SELF();

	/* Add thread0's load since it's running. */
	TDQ_LOCK(tdq);
	thread0.td_lock = TDQ_LOCKPTR(TDQ_SELF());
	tdq_load_add(tdq, &thread0);
	tdq->tdq_lowpri = thread0.td_priority;
	TDQ_UNLOCK(tdq);
}