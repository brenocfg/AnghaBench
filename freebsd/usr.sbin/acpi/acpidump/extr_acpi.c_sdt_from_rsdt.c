#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
struct TYPE_10__ {int Length; int /*<<< orphan*/  Signature; } ;
struct TYPE_9__ {int /*<<< orphan*/ * TableOffsetEntry; } ;
struct TYPE_8__ {int /*<<< orphan*/ * TableOffsetEntry; } ;
typedef  TYPE_1__ ACPI_TABLE_XSDT ;
typedef  TYPE_2__ ACPI_TABLE_RSDT ;
typedef  TYPE_3__ ACPI_TABLE_HEADER ;

/* Variables and functions */
 scalar_t__ acpi_checksum (TYPE_3__*,int) ; 
 scalar_t__ acpi_map_sdt (scalar_t__) ; 
 int addr_size ; 
 int /*<<< orphan*/  errx (int,char*,int) ; 
 scalar_t__ le32toh (int /*<<< orphan*/ ) ; 
 scalar_t__ le64toh (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

ACPI_TABLE_HEADER *
sdt_from_rsdt(ACPI_TABLE_HEADER *rsdp, const char *sig, ACPI_TABLE_HEADER *last)
{
	ACPI_TABLE_HEADER *sdt;
	ACPI_TABLE_RSDT *rsdt;
	ACPI_TABLE_XSDT *xsdt;
	vm_offset_t addr;
	int entries, i;

	rsdt = (ACPI_TABLE_RSDT *)rsdp;
	xsdt = (ACPI_TABLE_XSDT *)rsdp;
	entries = (rsdp->Length - sizeof(ACPI_TABLE_HEADER)) / addr_size;
	for (i = 0; i < entries; i++) {
		if (addr_size == 4)
			addr = le32toh(rsdt->TableOffsetEntry[i]);
		else
			addr = le64toh(xsdt->TableOffsetEntry[i]);
		if (addr == 0)
			continue;
		sdt = (ACPI_TABLE_HEADER *)acpi_map_sdt(addr);
		if (last != NULL) {
			if (sdt == last)
				last = NULL;
			continue;
		}
		if (memcmp(sdt->Signature, sig, strlen(sig)))
			continue;
		if (acpi_checksum(sdt, sdt->Length))
			errx(1, "RSDT entry %d is corrupt", i);
		return (sdt);
	}

	return (NULL);
}