#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  __flush_tlb_global () ; 
 int /*<<< orphan*/  cpu_sleep () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  trigger_address_error () ; 
 int /*<<< orphan*/  watchdog_trigger_immediate () ; 

__attribute__((used)) static void native_machine_restart(char * __unused)
{
	local_irq_disable();

	/* Destroy all of the TLBs in preparation for reset by MMU */
	__flush_tlb_global();

	/* Address error with SR.BL=1 first. */
	trigger_address_error();

#ifdef CONFIG_SUPERH32
	/* If that fails or is unsupported, go for the watchdog next. */
	watchdog_trigger_immediate();
#endif

	/*
	 * Give up and sleep.
	 */
	while (1)
		cpu_sleep();
}