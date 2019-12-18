#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_paddr_t ;
struct arm_gic_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_6__ {int Length; } ;
struct TYPE_7__ {TYPE_1__ Header; } ;
typedef  TYPE_2__ ACPI_TABLE_MADT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SIG_MADT ; 
 scalar_t__ acpi_find_table (int /*<<< orphan*/ ) ; 
 TYPE_2__* acpi_map_table (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_unmap_table (TYPE_2__*) ; 
 int /*<<< orphan*/  acpi_walk_subtables (TYPE_2__*,char*,int /*<<< orphan*/ ,struct arm_gic_softc*) ; 
 struct arm_gic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  madt_gicv2m_handler ; 

__attribute__((used)) static bool
arm_gic_add_children(device_t dev)
{
	struct arm_gic_softc *sc = device_get_softc(dev);
	ACPI_TABLE_MADT *madt;
	vm_paddr_t physaddr;

	/* This should return a valid address as it did in gic_acpi_identify */
	physaddr = acpi_find_table(ACPI_SIG_MADT);
	if (physaddr == 0)
		return (false);

	madt = acpi_map_table(physaddr, ACPI_SIG_MADT);
	if (madt == NULL) {
		device_printf(dev, "gic: Unable to map the MADT\n");
		return (false);
	}

	acpi_walk_subtables(madt + 1, (char *)madt + madt->Header.Length,
	    madt_gicv2m_handler, sc);

	acpi_unmap_table(madt);

	return (true);
}