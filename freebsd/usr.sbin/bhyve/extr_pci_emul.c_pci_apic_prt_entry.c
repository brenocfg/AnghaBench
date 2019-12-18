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
 int /*<<< orphan*/  dsdt_line (char*,...) ; 

__attribute__((used)) static void
pci_apic_prt_entry(int bus, int slot, int pin, int pirq_pin, int ioapic_irq,
    void *arg)
{

	dsdt_line("  Package ()");
	dsdt_line("  {");
	dsdt_line("    0x%X,", slot << 16 | 0xffff);
	dsdt_line("    0x%02X,", pin - 1);
	dsdt_line("    Zero,");
	dsdt_line("    0x%X", ioapic_irq);
	dsdt_line("  },");
}