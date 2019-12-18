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
struct thread {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  ts_runtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  THREAD_LOCK_ASSERT (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_fork_thread (struct thread*,struct thread*) ; 
 int /*<<< orphan*/  sched_interact_fork (struct thread*) ; 
 int /*<<< orphan*/  sched_interact_update (struct thread*) ; 
 int /*<<< orphan*/  sched_pctcpu_update (TYPE_1__*,int) ; 
 int /*<<< orphan*/  sched_priority (struct thread*) ; 
 TYPE_1__* td_get_sched (struct thread*) ; 
 scalar_t__ tickincr ; 

void
sched_fork(struct thread *td, struct thread *child)
{
	THREAD_LOCK_ASSERT(td, MA_OWNED);
	sched_pctcpu_update(td_get_sched(td), 1);
	sched_fork_thread(td, child);
	/*
	 * Penalize the parent and child for forking.
	 */
	sched_interact_fork(child);
	sched_priority(child);
	td_get_sched(td)->ts_runtime += tickincr;
	sched_interact_update(td);
	sched_priority(td);
}