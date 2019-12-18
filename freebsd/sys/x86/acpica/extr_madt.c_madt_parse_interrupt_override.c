#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
typedef  enum intr_trigger { ____Placeholder_intr_trigger } intr_trigger ;
typedef  enum intr_polarity { ____Placeholder_intr_polarity } intr_polarity ;
struct TYPE_6__ {int SciInterrupt; } ;
struct TYPE_5__ {int SourceIrq; int GlobalIrq; } ;
typedef  TYPE_1__ ACPI_MADT_INTERRUPT_OVERRIDE ;

/* Variables and functions */
 int ACPI_Q_MADT_IRQ0 ; 
 TYPE_4__ AcpiGbl_FADT ; 
 int /*<<< orphan*/  acpi_OverrideInterruptLevel (int) ; 
 int acpi_quirks ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  ioapic_disable_pin (void*,int /*<<< orphan*/ ) ; 
 int ioapic_get_vector (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioapic_remap_vector (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ioapic_set_polarity (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ioapic_set_triggermode (void*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ madt_find_interrupt (int,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  madt_parse_interrupt_values (TYPE_1__*,int*,int*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
madt_parse_interrupt_override(ACPI_MADT_INTERRUPT_OVERRIDE *intr)
{
	void *new_ioapic, *old_ioapic;
	u_int new_pin, old_pin;
	enum intr_trigger trig;
	enum intr_polarity pol;

	if (acpi_quirks & ACPI_Q_MADT_IRQ0 && intr->SourceIrq == 0 &&
	    intr->GlobalIrq == 2) {
		if (bootverbose)
			printf("MADT: Skipping timer override\n");
		return;
	}

	if (madt_find_interrupt(intr->GlobalIrq, &new_ioapic, &new_pin) != 0) {
		printf("MADT: Could not find APIC for vector %u (IRQ %u)\n",
		    intr->GlobalIrq, intr->SourceIrq);
		return;
	}

	madt_parse_interrupt_values(intr, &trig, &pol);

	/* Remap the IRQ if it is mapped to a different interrupt vector. */
	if (intr->SourceIrq != intr->GlobalIrq) {
		/*
		 * If the SCI is remapped to a non-ISA global interrupt,
		 * then override the vector we use to setup and allocate
		 * the interrupt.
		 */
		if (intr->GlobalIrq > 15 &&
		    intr->SourceIrq == AcpiGbl_FADT.SciInterrupt)
			acpi_OverrideInterruptLevel(intr->GlobalIrq);
		else
			ioapic_remap_vector(new_ioapic, new_pin,
			    intr->SourceIrq);
		if (madt_find_interrupt(intr->SourceIrq, &old_ioapic,
		    &old_pin) != 0)
			printf("MADT: Could not find APIC for source IRQ %u\n",
			    intr->SourceIrq);
		else if (ioapic_get_vector(old_ioapic, old_pin) ==
		    intr->SourceIrq)
			ioapic_disable_pin(old_ioapic, old_pin);
	}

	/* Program the polarity and trigger mode. */
	ioapic_set_triggermode(new_ioapic, new_pin, trig);
	ioapic_set_polarity(new_ioapic, new_pin, pol);
}