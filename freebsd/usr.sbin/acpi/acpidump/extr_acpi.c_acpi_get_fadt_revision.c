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
struct TYPE_3__ {int Facs; int XFacs; } ;
typedef  TYPE_1__ ACPI_TABLE_FADT ;

/* Variables and functions */
 int addr_size ; 

__attribute__((used)) static int
acpi_get_fadt_revision(ACPI_TABLE_FADT *fadt)
{
	int fadt_revision;

	/* Set the FADT revision separately from the RSDP version. */
	if (addr_size == 8) {
		fadt_revision = 2;

		/*
		 * A few systems (e.g., IBM T23) have an RSDP that claims
		 * revision 2 but the 64 bit addresses are invalid.  If
		 * revision 2 and the 32 bit address is non-zero but the
		 * 32 and 64 bit versions don't match, prefer the 32 bit
		 * version for all subsequent tables.
		 */
		if (fadt->Facs != 0 &&
		    (fadt->XFacs & 0xffffffff) != fadt->Facs)
			fadt_revision = 1;
	} else
		fadt_revision = 1;
	return (fadt_revision);
}