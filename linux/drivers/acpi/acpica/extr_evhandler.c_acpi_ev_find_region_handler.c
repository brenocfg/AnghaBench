#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ space_id; union acpi_operand_object* next; } ;
union acpi_operand_object {TYPE_1__ address_space; } ;
typedef  scalar_t__ acpi_adr_space_type ;

/* Variables and functions */

union acpi_operand_object *acpi_ev_find_region_handler(acpi_adr_space_type
						       space_id,
						       union acpi_operand_object
						       *handler_obj)
{

	/* Walk the handler list for this device */

	while (handler_obj) {

		/* Same space_id indicates a handler is installed */

		if (handler_obj->address_space.space_id == space_id) {
			return (handler_obj);
		}

		/* Next handler object */

		handler_obj = handler_obj->address_space.next;
	}

	return (NULL);
}