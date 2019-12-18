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
 int /*<<< orphan*/  IRQ_SUBCLASS_MEASUREMENT_ALERT ; 
 int PMC_RELEASE ; 
 int /*<<< orphan*/  irq_subclass_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  setup_pmc_cpu ; 

__attribute__((used)) static void release_pmc_hardware(void)
{
	int flags = PMC_RELEASE;

	irq_subclass_unregister(IRQ_SUBCLASS_MEASUREMENT_ALERT);
	on_each_cpu(setup_pmc_cpu, &flags, 1);
}