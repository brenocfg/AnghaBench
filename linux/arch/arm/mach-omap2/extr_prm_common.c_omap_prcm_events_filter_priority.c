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
struct TYPE_2__ {int nr_regs; unsigned long* priority_mask; } ;

/* Variables and functions */
 TYPE_1__* prcm_irq_setup ; 

__attribute__((used)) static void omap_prcm_events_filter_priority(unsigned long *events,
	unsigned long *priority_events)
{
	int i;

	for (i = 0; i < prcm_irq_setup->nr_regs; i++) {
		priority_events[i] =
			events[i] & prcm_irq_setup->priority_mask[i];
		events[i] ^= priority_events[i];
	}
}