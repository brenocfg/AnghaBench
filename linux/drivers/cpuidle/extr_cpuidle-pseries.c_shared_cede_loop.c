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
struct cpuidle_driver {int dummy; } ;
struct cpuidle_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_and_cede_processor () ; 
 int /*<<< orphan*/  idle_loop_epilog (unsigned long) ; 
 int /*<<< orphan*/  idle_loop_prolog (unsigned long*) ; 
 int /*<<< orphan*/  local_irq_disable () ; 

__attribute__((used)) static int shared_cede_loop(struct cpuidle_device *dev,
			struct cpuidle_driver *drv,
			int index)
{
	unsigned long in_purr;

	idle_loop_prolog(&in_purr);

	/*
	 * Yield the processor to the hypervisor.  We return if
	 * an external interrupt occurs (which are driven prior
	 * to returning here) or if a prod occurs from another
	 * processor. When returning here, external interrupts
	 * are enabled.
	 */
	check_and_cede_processor();

	local_irq_disable();
	idle_loop_epilog(in_purr);

	return index;
}