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
struct hw_perf_event_extra {size_t idx; scalar_t__ alloc; } ;
struct TYPE_2__ {struct hw_perf_event_extra extra_reg; } ;
struct perf_event {TYPE_1__ hw; } ;
struct intel_uncore_extra_reg {int /*<<< orphan*/  ref; } ;
struct intel_uncore_box {struct intel_uncore_extra_reg* shared_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ uncore_box_is_fake (struct intel_uncore_box*) ; 

void uncore_put_constraint(struct intel_uncore_box *box, struct perf_event *event)
{
	struct intel_uncore_extra_reg *er;
	struct hw_perf_event_extra *reg1 = &event->hw.extra_reg;

	/*
	 * Only put constraint if extra reg was actually allocated. Also
	 * takes care of event which do not use an extra shared reg.
	 *
	 * Also, if this is a fake box we shouldn't touch any event state
	 * (reg->alloc) and we don't care about leaving inconsistent box
	 * state either since it will be thrown out.
	 */
	if (uncore_box_is_fake(box) || !reg1->alloc)
		return;

	er = &box->shared_regs[reg1->idx];
	atomic_dec(&er->ref);
	reg1->alloc = 0;
}