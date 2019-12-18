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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_8__ {int /*<<< orphan*/  Length; int /*<<< orphan*/  Signature; } ;
struct TYPE_7__ {int Revision; int /*<<< orphan*/  XsdtPhysicalAddress; int /*<<< orphan*/  RsdtPhysicalAddress; } ;
typedef  TYPE_1__ ACPI_TABLE_RSDP ;
typedef  TYPE_2__ ACPI_TABLE_HEADER ;

/* Variables and functions */
 scalar_t__ acpi_checksum (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* acpi_find_rsd_ptr () ; 
 scalar_t__ acpi_map_sdt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_print_rsd_ptr (TYPE_1__*) ; 
 int addr_size ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ tflag ; 

ACPI_TABLE_HEADER *
sdt_load_devmem(void)
{
	ACPI_TABLE_RSDP *rp;
	ACPI_TABLE_HEADER *rsdp;

	rp = acpi_find_rsd_ptr();
	if (!rp)
		errx(1, "Can't find ACPI information");

	if (tflag)
		acpi_print_rsd_ptr(rp);
	if (rp->Revision < 2) {
		rsdp = (ACPI_TABLE_HEADER *)acpi_map_sdt(rp->RsdtPhysicalAddress);
		if (memcmp(rsdp->Signature, "RSDT", 4) != 0 ||
		    acpi_checksum(rsdp, rsdp->Length) != 0)
			errx(1, "RSDT is corrupted");
		addr_size = sizeof(uint32_t);
	} else {
		rsdp = (ACPI_TABLE_HEADER *)acpi_map_sdt(rp->XsdtPhysicalAddress);
		if (memcmp(rsdp->Signature, "XSDT", 4) != 0 ||
		    acpi_checksum(rsdp, rsdp->Length) != 0)
			errx(1, "XSDT is corrupted");
		addr_size = sizeof(uint64_t);
	}
	return (rsdp);
}