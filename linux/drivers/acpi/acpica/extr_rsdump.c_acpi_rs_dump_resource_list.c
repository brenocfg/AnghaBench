#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_3__ {size_t type; } ;
struct TYPE_4__ {TYPE_1__ common_serial_bus; } ;
struct acpi_resource {size_t type; TYPE_2__ data; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 int /*<<< orphan*/  ACPI_IS_DEBUG_ENABLED (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_LV_RESOURCES ; 
 struct acpi_resource* ACPI_NEXT_RESOURCE (struct acpi_resource*) ; 
 size_t ACPI_RESOURCE_TYPE_END_TAG ; 
 size_t ACPI_RESOURCE_TYPE_MAX ; 
 size_t ACPI_RESOURCE_TYPE_SERIAL_BUS ; 
 int /*<<< orphan*/  _COMPONENT ; 
 int /*<<< orphan*/ * acpi_gbl_dump_resource_dispatch ; 
 int /*<<< orphan*/ * acpi_gbl_dump_serial_bus_dispatch ; 
 int /*<<< orphan*/  acpi_os_printf (char*,...) ; 
 int /*<<< orphan*/  acpi_rs_dump_descriptor (TYPE_2__*,int /*<<< orphan*/ ) ; 

void acpi_rs_dump_resource_list(struct acpi_resource *resource_list)
{
	u32 count = 0;
	u32 type;

	ACPI_FUNCTION_ENTRY();

	/* Check if debug output enabled */

	if (!ACPI_IS_DEBUG_ENABLED(ACPI_LV_RESOURCES, _COMPONENT)) {
		return;
	}

	/* Walk list and dump all resource descriptors (END_TAG terminates) */

	do {
		acpi_os_printf("\n[%02X] ", count);
		count++;

		/* Validate Type before dispatch */

		type = resource_list->type;
		if (type > ACPI_RESOURCE_TYPE_MAX) {
			acpi_os_printf
			    ("Invalid descriptor type (%X) in resource list\n",
			     resource_list->type);
			return;
		}

		/* Sanity check the length. It must not be zero, or we loop forever */

		if (!resource_list->length) {
			acpi_os_printf
			    ("Invalid zero length descriptor in resource list\n");
			return;
		}

		/* Dump the resource descriptor */

		if (type == ACPI_RESOURCE_TYPE_SERIAL_BUS) {
			acpi_rs_dump_descriptor(&resource_list->data,
						acpi_gbl_dump_serial_bus_dispatch
						[resource_list->data.
						 common_serial_bus.type]);
		} else {
			acpi_rs_dump_descriptor(&resource_list->data,
						acpi_gbl_dump_resource_dispatch
						[type]);
		}

		/* Point to the next resource structure */

		resource_list = ACPI_NEXT_RESOURCE(resource_list);

		/* Exit when END_TAG descriptor is reached */

	} while (type != ACPI_RESOURCE_TYPE_END_TAG);
}