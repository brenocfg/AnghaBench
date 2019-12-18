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
typedef  scalar_t__ vm_paddr_t ;
struct TYPE_7__ {scalar_t__ nregions; } ;
struct gic_v3_softc {TYPE_1__ gic_redists; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_8__ {int Length; } ;
struct TYPE_9__ {TYPE_2__ Header; } ;
typedef  TYPE_3__ ACPI_TABLE_MADT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SIG_MADT ; 
 int ENXIO ; 
 scalar_t__ acpi_find_table (int /*<<< orphan*/ ) ; 
 TYPE_3__* acpi_map_table (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_unmap_table (TYPE_3__*) ; 
 int /*<<< orphan*/  acpi_walk_subtables (TYPE_3__*,char*,int /*<<< orphan*/ ,struct gic_v3_softc*) ; 
 struct gic_v3_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  madt_count_redistrib ; 

__attribute__((used)) static int
gic_v3_acpi_count_regions(device_t dev)
{
	struct gic_v3_softc *sc;
	ACPI_TABLE_MADT *madt;
	vm_paddr_t physaddr;

	sc = device_get_softc(dev);

	physaddr = acpi_find_table(ACPI_SIG_MADT);
	if (physaddr == 0)
		return (ENXIO);

	madt = acpi_map_table(physaddr, ACPI_SIG_MADT);
	if (madt == NULL) {
		device_printf(dev, "Unable to map the MADT\n");
		return (ENXIO);
	}

	acpi_walk_subtables(madt + 1, (char *)madt + madt->Header.Length,
	    madt_count_redistrib, sc);
	acpi_unmap_table(madt);

	return (sc->gic_redists.nregions > 0 ? 0 : ENXIO);
}