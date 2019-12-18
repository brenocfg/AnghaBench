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
typedef  scalar_t__ vm_paddr_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT64 ;
struct TYPE_10__ {int Revision; scalar_t__ XsdtPhysicalAddress; } ;
struct TYPE_8__ {int Length; } ;
struct TYPE_9__ {scalar_t__* TableOffsetEntry; TYPE_1__ Header; } ;
typedef  TYPE_2__ ACPI_TABLE_XSDT ;
typedef  TYPE_3__ ACPI_TABLE_RSDP ;
typedef  TYPE_2__ ACPI_TABLE_HEADER ;
typedef  int /*<<< orphan*/  ACPI_PHYSICAL_ADDRESS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_RSDP_XCHECKSUM_LENGTH ; 
 char const* ACPI_SIG_XSDT ; 
 int /*<<< orphan*/  AcpiOsGetRootPointer () ; 
 scalar_t__ AcpiTbChecksum (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_unmap_table (TYPE_2__*) ; 
 scalar_t__ bootverbose ; 
 TYPE_2__* map_table (scalar_t__,int,char const*) ; 
 TYPE_3__* pmap_mapbios (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmap_unmapbios (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ probe_table (scalar_t__,char const*) ; 
 scalar_t__ resource_disabled (char*,int /*<<< orphan*/ ) ; 

vm_paddr_t
acpi_find_table(const char *sig)
{
	ACPI_PHYSICAL_ADDRESS rsdp_ptr;
	ACPI_TABLE_RSDP *rsdp;
	ACPI_TABLE_XSDT *xsdt;
	ACPI_TABLE_HEADER *table;
	vm_paddr_t addr;
	int i, count;

	if (resource_disabled("acpi", 0))
		return (0);

	/*
	 * Map in the RSDP.  Since ACPI uses AcpiOsMapMemory() which in turn
	 * calls pmap_mapbios() to find the RSDP, we assume that we can use
	 * pmap_mapbios() to map the RSDP.
	 */
	if ((rsdp_ptr = AcpiOsGetRootPointer()) == 0)
		return (0);
	rsdp = pmap_mapbios(rsdp_ptr, sizeof(ACPI_TABLE_RSDP));
	if (rsdp == NULL) {
		if (bootverbose)
			printf("ACPI: Failed to map RSDP\n");
		return (0);
	}

	addr = 0;
	if (rsdp->Revision >= 2 && rsdp->XsdtPhysicalAddress != 0) {
		/*
		 * AcpiOsGetRootPointer only verifies the checksum for
		 * the version 1.0 portion of the RSDP.  Version 2.0 has
		 * an additional checksum that we verify first.
		 */
		if (AcpiTbChecksum((UINT8 *)rsdp, ACPI_RSDP_XCHECKSUM_LENGTH)) {
			if (bootverbose)
				printf("ACPI: RSDP failed extended checksum\n");
			return (0);
		}
		xsdt = map_table(rsdp->XsdtPhysicalAddress, 2, ACPI_SIG_XSDT);
		if (xsdt == NULL) {
			if (bootverbose)
				printf("ACPI: Failed to map XSDT\n");
			pmap_unmapbios((vm_offset_t)rsdp,
			    sizeof(ACPI_TABLE_RSDP));
			return (0);
		}
		count = (xsdt->Header.Length - sizeof(ACPI_TABLE_HEADER)) /
		    sizeof(UINT64);
		for (i = 0; i < count; i++)
			if (probe_table(xsdt->TableOffsetEntry[i], sig)) {
				addr = xsdt->TableOffsetEntry[i];
				break;
			}
		acpi_unmap_table(xsdt);
	}
	pmap_unmapbios((vm_offset_t)rsdp, sizeof(ACPI_TABLE_RSDP));

	if (addr == 0) {
		if (bootverbose)
			printf("ACPI: No %s table found\n", sig);
		return (0);
	}
	if (bootverbose)
		printf("%s: Found table at 0x%jx\n", sig, (uintmax_t)addr);

	/*
	 * Verify that we can map the full table and that its checksum is
	 * correct, etc.
	 */
	table = map_table(addr, 0, sig);
	if (table == NULL)
		return (0);
	acpi_unmap_table(table);

	return (addr);
}