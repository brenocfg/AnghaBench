#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  nregions; } ;
struct gic_v3_softc {TYPE_1__ gic_redists; } ;
struct TYPE_5__ {scalar_t__ Type; } ;
typedef  TYPE_2__ ACPI_SUBTABLE_HEADER ;

/* Variables and functions */
 scalar_t__ ACPI_MADT_TYPE_GENERIC_REDISTRIBUTOR ; 

__attribute__((used)) static void
madt_count_redistrib(ACPI_SUBTABLE_HEADER *entry, void *arg)
{
	struct gic_v3_softc *sc = arg;

	if (entry->Type == ACPI_MADT_TYPE_GENERIC_REDISTRIBUTOR)
		sc->gic_redists.nregions++;
}