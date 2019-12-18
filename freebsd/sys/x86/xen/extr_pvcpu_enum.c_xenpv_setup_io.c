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
 int /*<<< orphan*/  ACPI_INTR_APIC ; 
 int /*<<< orphan*/  acpi_SetDefaultIntrModel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  num_io_irqs ; 
 scalar_t__ xen_initial_domain () ; 

__attribute__((used)) static int
xenpv_setup_io(void)
{

	if (xen_initial_domain()) {
		/*
		 * NB: we could iterate over the MADT IOAPIC entries in order
		 * to figure out the exact number of IOAPIC interrupts, but
		 * this is legacy code so just keep using the previous
		 * behaviour and assume a maximum of 256 interrupts.
		 */
		num_io_irqs = max(255, num_io_irqs);

		acpi_SetDefaultIntrModel(ACPI_INTR_APIC);
	}
	return (0);
}