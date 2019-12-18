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
struct TYPE_3__ {int Address; int Flags; } ;
typedef  TYPE_1__ ACPI_TABLE_MADT ;
typedef  int /*<<< orphan*/  ACPI_TABLE_HEADER ;

/* Variables and functions */
 int ACPI_MADT_PCAT_COMPAT ; 
 char* BEGIN_COMMENT ; 
 char* END_COMMENT ; 
 int /*<<< orphan*/  acpi_print_madt ; 
 int /*<<< orphan*/  acpi_print_sdt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_walk_subtables (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
acpi_handle_madt(ACPI_TABLE_HEADER *sdp)
{
	ACPI_TABLE_MADT *madt;

	printf(BEGIN_COMMENT);
	acpi_print_sdt(sdp);
	madt = (ACPI_TABLE_MADT *)sdp;
	printf("\tLocal APIC ADDR=0x%08x\n", madt->Address);
	printf("\tFlags={");
	if (madt->Flags & ACPI_MADT_PCAT_COMPAT)
		printf("PC-AT");
	printf("}\n");
	acpi_walk_subtables(sdp, (madt + 1), acpi_print_madt);
	printf(END_COMMENT);
}