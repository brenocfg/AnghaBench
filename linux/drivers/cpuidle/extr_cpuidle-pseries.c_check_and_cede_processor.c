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
 int MSR_EE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __hard_irq_enable () ; 
 int /*<<< orphan*/  cede_processor () ; 
 int mfmsr () ; 
 scalar_t__ prep_irq_for_idle () ; 

__attribute__((used)) static void check_and_cede_processor(void)
{
	/*
	 * Ensure our interrupt state is properly tracked,
	 * also checks if no interrupt has occurred while we
	 * were soft-disabled
	 */
	if (prep_irq_for_idle()) {
		cede_processor();
#ifdef CONFIG_TRACE_IRQFLAGS
		/* Ensure that H_CEDE returns with IRQs on */
		if (WARN_ON(!(mfmsr() & MSR_EE)))
			__hard_irq_enable();
#endif
	}
}