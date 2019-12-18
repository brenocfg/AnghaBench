#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  XDsdt; int /*<<< orphan*/  Dsdt; } ;
struct TYPE_7__ {int /*<<< orphan*/  Length; } ;
typedef  TYPE_1__ ACPI_TABLE_HEADER ;
typedef  TYPE_2__ ACPI_TABLE_FADT ;

/* Variables and functions */
 scalar_t__ acpi_checksum (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int acpi_get_fadt_revision (TYPE_2__*) ; 
 scalar_t__ acpi_map_sdt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int,char*) ; 

ACPI_TABLE_HEADER *
dsdt_from_fadt(ACPI_TABLE_FADT *fadt)
{
	ACPI_TABLE_HEADER	*sdt;

	/* Use the DSDT address if it is version 1, otherwise use XDSDT. */
	if (acpi_get_fadt_revision(fadt) == 1)
		sdt = (ACPI_TABLE_HEADER *)acpi_map_sdt(fadt->Dsdt);
	else
		sdt = (ACPI_TABLE_HEADER *)acpi_map_sdt(fadt->XDsdt);
	if (acpi_checksum(sdt, sdt->Length))
		errx(1, "DSDT is corrupt\n");
	return (sdt);
}