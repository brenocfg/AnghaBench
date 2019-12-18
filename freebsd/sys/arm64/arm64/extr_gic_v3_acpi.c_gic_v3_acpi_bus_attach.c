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
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_6__ {int Length; } ;
struct TYPE_7__ {TYPE_1__ Header; } ;
typedef  TYPE_2__ ACPI_TABLE_MADT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SIG_MADT ; 
 scalar_t__ acpi_find_table (int /*<<< orphan*/ ) ; 
 TYPE_2__* acpi_map_table (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_unmap_table (TYPE_2__*) ; 
 int /*<<< orphan*/  acpi_walk_subtables (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gic_v3_add_children ; 

__attribute__((used)) static void
gic_v3_acpi_bus_attach(device_t dev)
{
	ACPI_TABLE_MADT *madt;
	vm_paddr_t physaddr;

	physaddr = acpi_find_table(ACPI_SIG_MADT);
	if (physaddr == 0)
		return;

	madt = acpi_map_table(physaddr, ACPI_SIG_MADT);
	if (madt == NULL) {
		device_printf(dev, "Unable to map the MADT to add children\n");
		return;
	}

	acpi_walk_subtables(madt + 1, (char *)madt + madt->Header.Length,
	    gic_v3_add_children, dev);

	acpi_unmap_table(madt);

	bus_generic_attach(dev);
}