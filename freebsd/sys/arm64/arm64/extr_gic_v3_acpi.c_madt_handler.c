#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct madt_table_data {int /*<<< orphan*/ * dist; int /*<<< orphan*/  parent; } ;
struct TYPE_3__ {int Type; } ;
typedef  TYPE_1__ ACPI_SUBTABLE_HEADER ;
typedef  int /*<<< orphan*/  ACPI_MADT_GENERIC_DISTRIBUTOR ;

/* Variables and functions */
#define  ACPI_MADT_TYPE_GENERIC_DISTRIBUTOR 129 
#define  ACPI_MADT_TYPE_GENERIC_REDISTRIBUTOR 128 
 int /*<<< orphan*/  bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
madt_handler(ACPI_SUBTABLE_HEADER *entry, void *arg)
{
	struct madt_table_data *madt_data;

	madt_data = (struct madt_table_data *)arg;

	switch(entry->Type) {
	case ACPI_MADT_TYPE_GENERIC_DISTRIBUTOR:
		if (madt_data->dist != NULL) {
			if (bootverbose)
				device_printf(madt_data->parent,
				    "gic: Already have a distributor table");
			break;
		}
		madt_data->dist = (ACPI_MADT_GENERIC_DISTRIBUTOR *)entry;
		break;

	case ACPI_MADT_TYPE_GENERIC_REDISTRIBUTOR:
		break;

	default:
		break;
	}
}