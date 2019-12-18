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
typedef  enum intr_trigger { ____Placeholder_intr_trigger } intr_trigger ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int UINT16 ;
struct TYPE_2__ {int /*<<< orphan*/  SciInterrupt; } ;

/* Variables and functions */
#define  ACPI_MADT_TRIGGER_CONFORMS 130 
#define  ACPI_MADT_TRIGGER_EDGE 129 
#define  ACPI_MADT_TRIGGER_LEVEL 128 
 int ACPI_MADT_TRIGGER_MASK ; 
 TYPE_1__ AcpiGbl_FADT ; 
 int INTR_TRIGGER_EDGE ; 
 int INTR_TRIGGER_LEVEL ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static enum intr_trigger
interrupt_trigger(UINT16 IntiFlags, UINT8 Source)
{

	switch (IntiFlags & ACPI_MADT_TRIGGER_MASK) {
	default:
		printf("WARNING: Bogus Interrupt Trigger Mode. Assume CONFORMS.\n");
		/*FALLTHROUGH*/
	case ACPI_MADT_TRIGGER_CONFORMS:
		if (Source == AcpiGbl_FADT.SciInterrupt)
			return (INTR_TRIGGER_LEVEL);
		else
			return (INTR_TRIGGER_EDGE);
	case ACPI_MADT_TRIGGER_EDGE:
		return (INTR_TRIGGER_EDGE);
	case ACPI_MADT_TRIGGER_LEVEL:
		return (INTR_TRIGGER_LEVEL);
	}
}