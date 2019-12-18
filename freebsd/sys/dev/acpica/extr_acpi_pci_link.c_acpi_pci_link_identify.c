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
typedef  int /*<<< orphan*/  driver_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int SciInterrupt; } ;

/* Variables and functions */
 TYPE_1__ AcpiGbl_FADT ; 
 int NUM_ISA_INTERRUPTS ; 
 int pci_link_bios_isa_irqs ; 

__attribute__((used)) static void
acpi_pci_link_identify(driver_t *driver, device_t parent)
{

	/*
	 * If the SCI is an ISA IRQ, add it to the bitmask of known good
	 * ISA IRQs.
	 *
	 * XXX: If we are using the APIC, the SCI might have been
	 * rerouted to an APIC pin in which case this is invalid.  However,
	 * if we are using the APIC, we also shouldn't be having any PCI
	 * interrupts routed via ISA IRQs, so this is probably ok.
	 */
	if (AcpiGbl_FADT.SciInterrupt < NUM_ISA_INTERRUPTS)
		pci_link_bios_isa_irqs |= (1 << AcpiGbl_FADT.SciInterrupt);
}