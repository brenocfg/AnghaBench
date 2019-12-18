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
struct TYPE_2__ {int /*<<< orphan*/  (* power_save ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HMT_low () ; 
 int /*<<< orphan*/  HMT_medium () ; 
 int /*<<< orphan*/  HMT_very_low () ; 
 scalar_t__ irqs_disabled () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  ppc64_runlatch_off () ; 
 int /*<<< orphan*/  ppc64_runlatch_on () ; 
 TYPE_1__ ppc_md ; 
 int /*<<< orphan*/  stub1 () ; 

void arch_cpu_idle(void)
{
	ppc64_runlatch_off();

	if (ppc_md.power_save) {
		ppc_md.power_save();
		/*
		 * Some power_save functions return with
		 * interrupts enabled, some don't.
		 */
		if (irqs_disabled())
			local_irq_enable();
	} else {
		local_irq_enable();
		/*
		 * Go into low thread priority and possibly
		 * low power mode.
		 */
		HMT_low();
		HMT_very_low();
	}

	HMT_medium();
	ppc64_runlatch_on();
}