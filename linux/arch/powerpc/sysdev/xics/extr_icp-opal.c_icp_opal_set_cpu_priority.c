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
 unsigned char DEFAULT_PRIORITY ; 
 unsigned char LOWEST_PRIORITY ; 
 int /*<<< orphan*/  iosync () ; 
 int /*<<< orphan*/  opal_int_set_cppr (unsigned char) ; 
 int /*<<< orphan*/  xics_set_base_cppr (unsigned char) ; 

__attribute__((used)) static void icp_opal_set_cpu_priority(unsigned char cppr)
{
	/*
	 * Here be dragons. The caller has asked to allow only IPI's and not
	 * external interrupts. But OPAL XIVE doesn't support that. So instead
	 * of allowing no interrupts allow all. That's still not right, but
	 * currently the only caller who does this is xics_migrate_irqs_away()
	 * and it works in that case.
	 */
	if (cppr >= DEFAULT_PRIORITY)
		cppr = LOWEST_PRIORITY;

	xics_set_base_cppr(cppr);
	opal_int_set_cppr(cppr);
	iosync();
}