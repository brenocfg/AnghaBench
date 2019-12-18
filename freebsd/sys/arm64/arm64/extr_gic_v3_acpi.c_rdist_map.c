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
struct madt_table_data {int /*<<< orphan*/  count; int /*<<< orphan*/  dev; int /*<<< orphan*/  parent; } ;
struct TYPE_5__ {int /*<<< orphan*/  Length; int /*<<< orphan*/  BaseAddress; } ;
struct TYPE_4__ {int Type; } ;
typedef  TYPE_1__ ACPI_SUBTABLE_HEADER ;
typedef  TYPE_2__ ACPI_MADT_GENERIC_REDISTRIBUTOR ;

/* Variables and functions */
#define  ACPI_MADT_TYPE_GENERIC_REDISTRIBUTOR 128 
 int /*<<< orphan*/  BUS_SET_RESOURCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 

__attribute__((used)) static void
rdist_map(ACPI_SUBTABLE_HEADER *entry, void *arg)
{
	ACPI_MADT_GENERIC_REDISTRIBUTOR *redist;
	struct madt_table_data *madt_data;

	madt_data = (struct madt_table_data *)arg;

	switch(entry->Type) {
	case ACPI_MADT_TYPE_GENERIC_REDISTRIBUTOR:
		redist = (ACPI_MADT_GENERIC_REDISTRIBUTOR *)entry;

		madt_data->count++;
		BUS_SET_RESOURCE(madt_data->parent, madt_data->dev,
		    SYS_RES_MEMORY, madt_data->count, redist->BaseAddress,
		    redist->Length);
		break;

	default:
		break;
	}
}