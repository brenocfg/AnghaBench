#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct acpi_interface_info {int flags; struct acpi_interface_info* next; struct acpi_interface_info* name; } ;
typedef  int /*<<< orphan*/  acpi_string ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (struct acpi_interface_info*) ; 
 int ACPI_OSI_DYNAMIC ; 
 int ACPI_OSI_INVALID ; 
 int /*<<< orphan*/  AE_NOT_EXIST ; 
 int /*<<< orphan*/  AE_OK ; 
 struct acpi_interface_info* acpi_gbl_supported_interfaces ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,struct acpi_interface_info*) ; 

acpi_status acpi_ut_remove_interface(acpi_string interface_name)
{
	struct acpi_interface_info *previous_interface;
	struct acpi_interface_info *next_interface;

	previous_interface = next_interface = acpi_gbl_supported_interfaces;
	while (next_interface) {
		if (!strcmp(interface_name, next_interface->name)) {
			/*
			 * Found: name is in either the static list
			 * or was added at runtime
			 */
			if (next_interface->flags & ACPI_OSI_DYNAMIC) {

				/* Interface was added dynamically, remove and free it */

				if (previous_interface == next_interface) {
					acpi_gbl_supported_interfaces =
					    next_interface->next;
				} else {
					previous_interface->next =
					    next_interface->next;
				}

				ACPI_FREE(next_interface->name);
				ACPI_FREE(next_interface);
			} else {
				/*
				 * Interface is in static list. If marked invalid, then
				 * it does not actually exist. Else, mark it invalid.
				 */
				if (next_interface->flags & ACPI_OSI_INVALID) {
					return (AE_NOT_EXIST);
				}

				next_interface->flags |= ACPI_OSI_INVALID;
			}

			return (AE_OK);
		}

		previous_interface = next_interface;
		next_interface = next_interface->next;
	}

	/* Interface was not found */

	return (AE_NOT_EXIST);
}