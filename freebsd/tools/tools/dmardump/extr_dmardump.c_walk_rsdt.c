#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_9__ {int Length; int /*<<< orphan*/  Signature; } ;
struct TYPE_8__ {int /*<<< orphan*/ * TableOffsetEntry; } ;
struct TYPE_7__ {int /*<<< orphan*/ * TableOffsetEntry; } ;
typedef  TYPE_1__ ACPI_TABLE_XSDT ;
typedef  TYPE_2__ ACPI_TABLE_RSDT ;
typedef  TYPE_3__ ACPI_TABLE_HEADER ;

/* Variables and functions */
 char* ACPI_SIG_DMAR ; 
 scalar_t__ acpi_checksum (TYPE_3__*,int) ; 
 int /*<<< orphan*/  acpi_handle_dmar (TYPE_3__*) ; 
 scalar_t__ acpi_map_sdt (scalar_t__) ; 
 scalar_t__ le32toh (int /*<<< orphan*/ ) ; 
 scalar_t__ le64toh (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
walk_rsdt(ACPI_TABLE_HEADER *rsdp)
{
	ACPI_TABLE_HEADER *sdp;
	ACPI_TABLE_RSDT *rsdt;
	ACPI_TABLE_XSDT *xsdt;
	vm_offset_t addr;
	int addr_size, entries, i;

	if (memcmp(rsdp->Signature, "RSDT", 4) != 0)
		addr_size = sizeof(uint32_t);
	else
		addr_size = sizeof(uint64_t);
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
		sdp = (ACPI_TABLE_HEADER *)acpi_map_sdt(addr);
		if (acpi_checksum(sdp, sdp->Length)) {
			continue;
		}
		if (!memcmp(sdp->Signature, ACPI_SIG_DMAR, 4))
			acpi_handle_dmar(sdp);
	}
}