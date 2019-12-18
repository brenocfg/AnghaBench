#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct kvmppc_vcore {scalar_t__ halt_poll_ns; TYPE_2__* runner; void* vcore_state; int /*<<< orphan*/  lock; int /*<<< orphan*/  wq; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_3__ {int /*<<< orphan*/  halt_poll_success_ns; int /*<<< orphan*/  halt_poll_fail_ns; int /*<<< orphan*/  halt_wait_ns; int /*<<< orphan*/  halt_successful_wait; int /*<<< orphan*/  halt_successful_poll; int /*<<< orphan*/  halt_attempted_poll; } ;
struct TYPE_4__ {TYPE_1__ stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_SWAITQUEUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 void* VCORE_INACTIVE ; 
 void* VCORE_POLLING ; 
 void* VCORE_SLEEPING ; 
 int /*<<< orphan*/  finish_swait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  grow_halt_poll_ns (struct kvmppc_vcore*) ; 
 scalar_t__ halt_poll_ns ; 
 int /*<<< orphan*/  ktime_add_ns (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ktime_before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 scalar_t__ ktime_to_ns (int /*<<< orphan*/ ) ; 
 scalar_t__ kvmppc_vcore_check_block (struct kvmppc_vcore*) ; 
 int /*<<< orphan*/  prepare_to_swait_exclusive (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  shrink_halt_poll_ns (struct kvmppc_vcore*) ; 
 scalar_t__ single_task_running () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_kvmppc_vcore_blocked (struct kvmppc_vcore*,int) ; 
 int /*<<< orphan*/  trace_kvmppc_vcore_wakeup (int,scalar_t__) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static void kvmppc_vcore_blocked(struct kvmppc_vcore *vc)
{
	ktime_t cur, start_poll, start_wait;
	int do_sleep = 1;
	u64 block_ns;
	DECLARE_SWAITQUEUE(wait);

	/* Poll for pending exceptions and ceded state */
	cur = start_poll = ktime_get();
	if (vc->halt_poll_ns) {
		ktime_t stop = ktime_add_ns(start_poll, vc->halt_poll_ns);
		++vc->runner->stat.halt_attempted_poll;

		vc->vcore_state = VCORE_POLLING;
		spin_unlock(&vc->lock);

		do {
			if (kvmppc_vcore_check_block(vc)) {
				do_sleep = 0;
				break;
			}
			cur = ktime_get();
		} while (single_task_running() && ktime_before(cur, stop));

		spin_lock(&vc->lock);
		vc->vcore_state = VCORE_INACTIVE;

		if (!do_sleep) {
			++vc->runner->stat.halt_successful_poll;
			goto out;
		}
	}

	prepare_to_swait_exclusive(&vc->wq, &wait, TASK_INTERRUPTIBLE);

	if (kvmppc_vcore_check_block(vc)) {
		finish_swait(&vc->wq, &wait);
		do_sleep = 0;
		/* If we polled, count this as a successful poll */
		if (vc->halt_poll_ns)
			++vc->runner->stat.halt_successful_poll;
		goto out;
	}

	start_wait = ktime_get();

	vc->vcore_state = VCORE_SLEEPING;
	trace_kvmppc_vcore_blocked(vc, 0);
	spin_unlock(&vc->lock);
	schedule();
	finish_swait(&vc->wq, &wait);
	spin_lock(&vc->lock);
	vc->vcore_state = VCORE_INACTIVE;
	trace_kvmppc_vcore_blocked(vc, 1);
	++vc->runner->stat.halt_successful_wait;

	cur = ktime_get();

out:
	block_ns = ktime_to_ns(cur) - ktime_to_ns(start_poll);

	/* Attribute wait time */
	if (do_sleep) {
		vc->runner->stat.halt_wait_ns +=
			ktime_to_ns(cur) - ktime_to_ns(start_wait);
		/* Attribute failed poll time */
		if (vc->halt_poll_ns)
			vc->runner->stat.halt_poll_fail_ns +=
				ktime_to_ns(start_wait) -
				ktime_to_ns(start_poll);
	} else {
		/* Attribute successful poll time */
		if (vc->halt_poll_ns)
			vc->runner->stat.halt_poll_success_ns +=
				ktime_to_ns(cur) -
				ktime_to_ns(start_poll);
	}

	/* Adjust poll time */
	if (halt_poll_ns) {
		if (block_ns <= vc->halt_poll_ns)
			;
		/* We slept and blocked for longer than the max halt time */
		else if (vc->halt_poll_ns && block_ns > halt_poll_ns)
			shrink_halt_poll_ns(vc);
		/* We slept and our poll time is too small */
		else if (vc->halt_poll_ns < halt_poll_ns &&
				block_ns < halt_poll_ns)
			grow_halt_poll_ns(vc);
		if (vc->halt_poll_ns > halt_poll_ns)
			vc->halt_poll_ns = halt_poll_ns;
	} else
		vc->halt_poll_ns = 0;

	trace_kvmppc_vcore_wakeup(do_sleep, block_ns);
}