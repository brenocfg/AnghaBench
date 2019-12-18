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
struct perf_event {int dummy; } ;
struct hw_perf_event_extra {int idx; int alloc; scalar_t__ config; int /*<<< orphan*/  reg; } ;
struct event_constraint {int dummy; } ;
struct er_account {scalar_t__ config; int /*<<< orphan*/  lock; int /*<<< orphan*/  ref; int /*<<< orphan*/  reg; } ;
struct cpu_hw_events {int /*<<< orphan*/  is_fake; TYPE_1__* shared_regs; } ;
struct TYPE_2__ {struct er_account* regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 struct event_constraint emptyconstraint ; 
 int intel_alt_er (int,scalar_t__) ; 
 int /*<<< orphan*/  intel_fixup_er (struct perf_event*,int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct event_constraint *
__intel_shared_reg_get_constraints(struct cpu_hw_events *cpuc,
				   struct perf_event *event,
				   struct hw_perf_event_extra *reg)
{
	struct event_constraint *c = &emptyconstraint;
	struct er_account *era;
	unsigned long flags;
	int idx = reg->idx;

	/*
	 * reg->alloc can be set due to existing state, so for fake cpuc we
	 * need to ignore this, otherwise we might fail to allocate proper fake
	 * state for this extra reg constraint. Also see the comment below.
	 */
	if (reg->alloc && !cpuc->is_fake)
		return NULL; /* call x86_get_event_constraint() */

again:
	era = &cpuc->shared_regs->regs[idx];
	/*
	 * we use spin_lock_irqsave() to avoid lockdep issues when
	 * passing a fake cpuc
	 */
	raw_spin_lock_irqsave(&era->lock, flags);

	if (!atomic_read(&era->ref) || era->config == reg->config) {

		/*
		 * If its a fake cpuc -- as per validate_{group,event}() we
		 * shouldn't touch event state and we can avoid doing so
		 * since both will only call get_event_constraints() once
		 * on each event, this avoids the need for reg->alloc.
		 *
		 * Not doing the ER fixup will only result in era->reg being
		 * wrong, but since we won't actually try and program hardware
		 * this isn't a problem either.
		 */
		if (!cpuc->is_fake) {
			if (idx != reg->idx)
				intel_fixup_er(event, idx);

			/*
			 * x86_schedule_events() can call get_event_constraints()
			 * multiple times on events in the case of incremental
			 * scheduling(). reg->alloc ensures we only do the ER
			 * allocation once.
			 */
			reg->alloc = 1;
		}

		/* lock in msr value */
		era->config = reg->config;
		era->reg = reg->reg;

		/* one more user */
		atomic_inc(&era->ref);

		/*
		 * need to call x86_get_event_constraint()
		 * to check if associated event has constraints
		 */
		c = NULL;
	} else {
		idx = intel_alt_er(idx, reg->config);
		if (idx != reg->idx) {
			raw_spin_unlock_irqrestore(&era->lock, flags);
			goto again;
		}
	}
	raw_spin_unlock_irqrestore(&era->lock, flags);

	return c;
}