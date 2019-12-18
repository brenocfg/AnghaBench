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
typedef  enum intr_polarity { ____Placeholder_intr_polarity } intr_polarity ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int UINT16 ;
struct TYPE_2__ {int /*<<< orphan*/  SciInterrupt; } ;

/* Variables and functions */
#define  ACPI_MADT_POLARITY_ACTIVE_HIGH 130 
#define  ACPI_MADT_POLARITY_ACTIVE_LOW 129 
#define  ACPI_MADT_POLARITY_CONFORMS 128 
 int ACPI_MADT_POLARITY_MASK ; 
 TYPE_1__ AcpiGbl_FADT ; 
 int INTR_POLARITY_HIGH ; 
 int INTR_POLARITY_LOW ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static enum intr_polarity
interrupt_polarity(UINT16 IntiFlags, UINT8 Source)
{

	switch (IntiFlags & ACPI_MADT_POLARITY_MASK) {
	default:
		printf("WARNING: Bogus Interrupt Polarity. Assume CONFORMS\n");
		/* FALLTHROUGH*/
	case ACPI_MADT_POLARITY_CONFORMS:
		if (Source == AcpiGbl_FADT.SciInterrupt)
			return (INTR_POLARITY_LOW);
		else
			return (INTR_POLARITY_HIGH);
	case ACPI_MADT_POLARITY_ACTIVE_HIGH:
		return (INTR_POLARITY_HIGH);
	case ACPI_MADT_POLARITY_ACTIVE_LOW:
		return (INTR_POLARITY_LOW);
	}
}