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
struct acpi_interface_info {int flags; struct acpi_interface_info* name; struct acpi_interface_info* next; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (struct acpi_interface_info*) ; 
 int ACPI_OSI_DEFAULT_INVALID ; 
 int ACPI_OSI_DYNAMIC ; 
 int ACPI_OSI_INVALID ; 
 int /*<<< orphan*/  ACPI_WAIT_FOREVER ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_gbl_osi_mutex ; 
 struct acpi_interface_info* acpi_gbl_supported_interfaces ; 
 int /*<<< orphan*/  acpi_os_acquire_mutex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_os_release_mutex (int /*<<< orphan*/ ) ; 

acpi_status acpi_ut_interface_terminate(void)
{
	acpi_status status;
	struct acpi_interface_info *next_interface;

	status = acpi_os_acquire_mutex(acpi_gbl_osi_mutex, ACPI_WAIT_FOREVER);
	if (ACPI_FAILURE(status)) {
		return (status);
	}

	next_interface = acpi_gbl_supported_interfaces;
	while (next_interface) {
		acpi_gbl_supported_interfaces = next_interface->next;

		if (next_interface->flags & ACPI_OSI_DYNAMIC) {

			/* Only interfaces added at runtime can be freed */

			ACPI_FREE(next_interface->name);
			ACPI_FREE(next_interface);
		} else {
			/* Interface is in static list. Reset it to invalid or valid. */

			if (next_interface->flags & ACPI_OSI_DEFAULT_INVALID) {
				next_interface->flags |= ACPI_OSI_INVALID;
			} else {
				next_interface->flags &= ~ACPI_OSI_INVALID;
			}
		}

		next_interface = acpi_gbl_supported_interfaces;
	}

	acpi_os_release_mutex(acpi_gbl_osi_mutex);
	return (AE_OK);
}