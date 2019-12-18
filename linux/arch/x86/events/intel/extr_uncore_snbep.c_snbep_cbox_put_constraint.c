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
struct hw_perf_event_extra {int alloc; } ;
struct TYPE_2__ {struct hw_perf_event_extra extra_reg; } ;
struct perf_event {TYPE_1__ hw; } ;
struct intel_uncore_extra_reg {int /*<<< orphan*/  ref; } ;
struct intel_uncore_box {struct intel_uncore_extra_reg* shared_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_sub (int,int /*<<< orphan*/ *) ; 
 scalar_t__ uncore_box_is_fake (struct intel_uncore_box*) ; 

__attribute__((used)) static void snbep_cbox_put_constraint(struct intel_uncore_box *box, struct perf_event *event)
{
	struct hw_perf_event_extra *reg1 = &event->hw.extra_reg;
	struct intel_uncore_extra_reg *er = &box->shared_regs[0];
	int i;

	if (uncore_box_is_fake(box))
		return;

	for (i = 0; i < 5; i++) {
		if (reg1->alloc & (0x1 << i))
			atomic_sub(1 << (i * 6), &er->ref);
	}
	reg1->alloc = 0;
}