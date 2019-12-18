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
struct TYPE_2__ {int Sequence; int Id; int MinimumTick; int Flags; int /*<<< orphan*/  Address; } ;
typedef  TYPE_1__ ACPI_TABLE_HPET ;
typedef  int /*<<< orphan*/  ACPI_TABLE_HEADER ;

/* Variables and functions */
 int ACPI_HPET_ID_COMPARATORS ; 
 int ACPI_HPET_ID_COUNT_SIZE_CAP ; 
 int ACPI_HPET_ID_HARDWARE_REV_ID ; 
 int ACPI_HPET_ID_LEGACY_CAPABLE ; 
 char* BEGIN_COMMENT ; 
 char* END_COMMENT ; 
 int /*<<< orphan*/  acpi_print_gas (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_print_sdt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
acpi_handle_hpet(ACPI_TABLE_HEADER *sdp)
{
	ACPI_TABLE_HPET *hpet;

	printf(BEGIN_COMMENT);
	acpi_print_sdt(sdp);
	hpet = (ACPI_TABLE_HPET *)sdp;
	printf("\tHPET Number=%d\n", hpet->Sequence);
	printf("\tADDR=");
	acpi_print_gas(&hpet->Address);
	printf("\tHW Rev=0x%x\n", hpet->Id & ACPI_HPET_ID_HARDWARE_REV_ID);
	printf("\tComparators=%d\n", (hpet->Id & ACPI_HPET_ID_COMPARATORS) >>
	    8);
	printf("\tCounter Size=%d\n", hpet->Id & ACPI_HPET_ID_COUNT_SIZE_CAP ?
	    1 : 0);
	printf("\tLegacy IRQ routing capable={");
	if (hpet->Id & ACPI_HPET_ID_LEGACY_CAPABLE)
		printf("TRUE}\n");
	else
		printf("FALSE}\n");
	printf("\tPCI Vendor ID=0x%04x\n", hpet->Id >> 16);
	printf("\tMinimal Tick=%d\n", hpet->MinimumTick);
	printf("\tFlags=0x%02x\n", hpet->Flags);
	printf(END_COMMENT);
}