#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_3__ {int GlobalIrq; int IntiFlags; } ;
typedef  TYPE_1__ ACPI_MADT_NMI_SOURCE ;

/* Variables and functions */
 int ACPI_MADT_POLARITY_CONFORMS ; 
 int ACPI_MADT_TRIGGER_CONFORMS ; 
 int /*<<< orphan*/  interrupt_polarity (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  interrupt_trigger (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioapic_set_nmi (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioapic_set_polarity (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioapic_set_triggermode (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ madt_find_interrupt (int,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void
madt_parse_nmi(ACPI_MADT_NMI_SOURCE *nmi)
{
	void *ioapic;
	u_int pin;

	if (madt_find_interrupt(nmi->GlobalIrq, &ioapic, &pin) != 0) {
		printf("MADT: Could not find APIC for vector %u\n",
		    nmi->GlobalIrq);
		return;
	}

	ioapic_set_nmi(ioapic, pin);
	if (!(nmi->IntiFlags & ACPI_MADT_TRIGGER_CONFORMS))
		ioapic_set_triggermode(ioapic, pin,
		    interrupt_trigger(nmi->IntiFlags, 0));
	if (!(nmi->IntiFlags & ACPI_MADT_POLARITY_CONFORMS))
		ioapic_set_polarity(ioapic, pin,
		    interrupt_polarity(nmi->IntiFlags, 0));
}