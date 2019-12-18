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
typedef  int uint16_t ;

/* Variables and functions */
#define  ACPI_MADT_POLARITY_ACTIVE_HIGH 133 
#define  ACPI_MADT_POLARITY_ACTIVE_LOW 132 
#define  ACPI_MADT_POLARITY_CONFORMS 131 
 int ACPI_MADT_POLARITY_MASK ; 
#define  ACPI_MADT_TRIGGER_CONFORMS 130 
#define  ACPI_MADT_TRIGGER_EDGE 129 
#define  ACPI_MADT_TRIGGER_LEVEL 128 
 int ACPI_MADT_TRIGGER_MASK ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
acpi_print_mps_flags(uint16_t flags)
{

	printf("\tFlags={Polarity=");
	switch (flags & ACPI_MADT_POLARITY_MASK) {
	case ACPI_MADT_POLARITY_CONFORMS:
		printf("conforming");
		break;
	case ACPI_MADT_POLARITY_ACTIVE_HIGH:
		printf("active-hi");
		break;
	case ACPI_MADT_POLARITY_ACTIVE_LOW:
		printf("active-lo");
		break;
	default:
		printf("0x%x", flags & ACPI_MADT_POLARITY_MASK);
		break;
	}
	printf(", Trigger=");
	switch (flags & ACPI_MADT_TRIGGER_MASK) {
	case ACPI_MADT_TRIGGER_CONFORMS:
		printf("conforming");
		break;
	case ACPI_MADT_TRIGGER_EDGE:
		printf("edge");
		break;
	case ACPI_MADT_TRIGGER_LEVEL:
		printf("level");
		break;
	default:
		printf("0x%x", (flags & ACPI_MADT_TRIGGER_MASK) >> 2);
	}
	printf("}\n");
}