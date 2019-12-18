#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_paddr_t ;
struct vtdmap {int /*<<< orphan*/  cap; } ;
typedef  int /*<<< orphan*/  envname ;
struct TYPE_9__ {unsigned long Address; } ;
struct TYPE_8__ {int Length; scalar_t__ Type; } ;
struct TYPE_6__ {int Length; } ;
struct TYPE_7__ {TYPE_1__ Header; } ;
typedef  int /*<<< orphan*/  ACPI_TABLE_HEADER ;
typedef  TYPE_2__ ACPI_TABLE_DMAR ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_3__ ACPI_DMAR_HEADER ;
typedef  TYPE_4__ ACPI_DMAR_HARDWARE_UNIT ;

/* Variables and functions */
 scalar_t__ ACPI_DMAR_TYPE_HARDWARE_UNIT ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SIG_DMAR ; 
 int /*<<< orphan*/  AcpiGetTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int DRHD_MAX_UNITS ; 
 int ENXIO ; 
 int PAGE_MASK ; 
 scalar_t__ PHYS_TO_DMAP (unsigned long) ; 
 scalar_t__ VTD_CAP_CM (int /*<<< orphan*/ ) ; 
 int VTD_ROOT_PRESENT ; 
 int /*<<< orphan*/ * ctx_tables ; 
 int drhd_num ; 
 TYPE_4__** drhds ; 
 scalar_t__ getenv_ulong (char*,unsigned long*) ; 
 int max_domains ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 int* root_table ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int vtd_max_domains (struct vtdmap*) ; 
 struct vtdmap** vtdmaps ; 
 int vtophys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vtd_init(void)
{
	int i, units, remaining, tmp;
	struct vtdmap *vtdmap;
	vm_paddr_t ctx_paddr;
	char *end, envname[32];
	unsigned long mapaddr;
	ACPI_STATUS status;
	ACPI_TABLE_DMAR *dmar;
	ACPI_DMAR_HEADER *hdr;
	ACPI_DMAR_HARDWARE_UNIT *drhd;

	/*
	 * Allow the user to override the ACPI DMAR table by specifying the
	 * physical address of each remapping unit.
	 *
	 * The following example specifies two remapping units at
	 * physical addresses 0xfed90000 and 0xfeda0000 respectively.
	 * set vtd.regmap.0.addr=0xfed90000
	 * set vtd.regmap.1.addr=0xfeda0000
	 */
	for (units = 0; units < DRHD_MAX_UNITS; units++) {
		snprintf(envname, sizeof(envname), "vtd.regmap.%d.addr", units);
		if (getenv_ulong(envname, &mapaddr) == 0)
			break;
		vtdmaps[units] = (struct vtdmap *)PHYS_TO_DMAP(mapaddr);
	}

	if (units > 0)
		goto skip_dmar;

	/* Search for DMAR table. */
	status = AcpiGetTable(ACPI_SIG_DMAR, 0, (ACPI_TABLE_HEADER **)&dmar);
	if (ACPI_FAILURE(status))
		return (ENXIO);

	end = (char *)dmar + dmar->Header.Length;
	remaining = dmar->Header.Length - sizeof(ACPI_TABLE_DMAR);
	while (remaining > sizeof(ACPI_DMAR_HEADER)) {
		hdr = (ACPI_DMAR_HEADER *)(end - remaining);
		if (hdr->Length > remaining)
			break;
		/*
		 * From Intel VT-d arch spec, version 1.3:
		 * BIOS implementations must report mapping structures
		 * in numerical order, i.e. All remapping structures of
		 * type 0 (DRHD) enumerated before remapping structures of
		 * type 1 (RMRR) and so forth.
		 */
		if (hdr->Type != ACPI_DMAR_TYPE_HARDWARE_UNIT)
			break;

		drhd = (ACPI_DMAR_HARDWARE_UNIT *)hdr;
		drhds[units] = drhd;
		vtdmaps[units] = (struct vtdmap *)PHYS_TO_DMAP(drhd->Address);
		if (++units >= DRHD_MAX_UNITS)
			break;
		remaining -= hdr->Length;
	}

	if (units <= 0)
		return (ENXIO);

skip_dmar:
	drhd_num = units;

	max_domains = 64 * 1024; /* maximum valid value */
	for (i = 0; i < drhd_num; i++){
		vtdmap = vtdmaps[i];

		if (VTD_CAP_CM(vtdmap->cap) != 0)
			panic("vtd_init: invalid caching mode");

		/* take most compatible (minimum) value */
		if ((tmp = vtd_max_domains(vtdmap)) < max_domains)
			max_domains = tmp;
	}

	/*
	 * Set up the root-table to point to the context-entry tables
	 */
	for (i = 0; i < 256; i++) {
		ctx_paddr = vtophys(ctx_tables[i]);
		if (ctx_paddr & PAGE_MASK)
			panic("ctx table (0x%0lx) not page aligned", ctx_paddr);

		root_table[i * 2] = ctx_paddr | VTD_ROOT_PRESENT;
	}

	return (0);
}