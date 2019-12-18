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
struct TYPE_2__ {int idle; } ;

/* Variables and functions */
 int /*<<< orphan*/  cede_processor () ; 
 TYPE_1__* get_lppaca () ; 
 int /*<<< orphan*/  prep_irq_for_idle () ; 

__attribute__((used)) static void pseries_lpar_idle(void)
{
	/*
	 * Default handler to go into low thread priority and possibly
	 * low power mode by ceding processor to hypervisor
	 */

	if (!prep_irq_for_idle())
		return;

	/* Indicate to hypervisor that we are idle. */
	get_lppaca()->idle = 1;

	/*
	 * Yield the processor to the hypervisor.  We return if
	 * an external interrupt occurs (which are driven prior
	 * to returning here) or if a prod occurs from another
	 * processor. When returning here, external interrupts
	 * are enabled.
	 */
	cede_processor();

	get_lppaca()->idle = 0;
}