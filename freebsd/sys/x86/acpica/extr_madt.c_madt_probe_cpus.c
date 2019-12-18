#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  Length; } ;
struct TYPE_6__ {TYPE_1__ Header; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SIG_MADT ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* acpi_map_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_unmap_table (TYPE_2__*) ; 
 TYPE_2__* madt ; 
 int /*<<< orphan*/  madt_length ; 
 int /*<<< orphan*/  madt_physaddr ; 
 int /*<<< orphan*/  madt_probe_cpus_handler ; 
 int /*<<< orphan*/  madt_walk_table (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
madt_probe_cpus(void)
{

	madt = acpi_map_table(madt_physaddr, ACPI_SIG_MADT);
	madt_length = madt->Header.Length;
	KASSERT(madt != NULL, ("Unable to re-map MADT"));
	madt_walk_table(madt_probe_cpus_handler, NULL);
	acpi_unmap_table(madt);
	madt = NULL;
	return (0);
}