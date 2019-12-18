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
#define  APIC_BUS_EISA 130 
#define  APIC_BUS_ISA 129 
#define  APIC_BUS_PCI 128 

__attribute__((used)) static const char *
ioapic_bus_string(int bus_type)
{

	switch (bus_type) {
	case APIC_BUS_ISA:
		return ("ISA");
	case APIC_BUS_EISA:
		return ("EISA");
	case APIC_BUS_PCI:
		return ("PCI");
	default:
		return ("unknown");
	}
}