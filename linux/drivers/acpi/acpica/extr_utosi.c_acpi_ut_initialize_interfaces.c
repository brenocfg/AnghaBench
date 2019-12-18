#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  size_t acpi_size ;
struct TYPE_4__ {struct TYPE_4__* next; } ;

/* Variables and functions */
 int ACPI_ARRAY_LENGTH (TYPE_1__*) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_WAIT_FOREVER ; 
 int /*<<< orphan*/  AE_OK ; 
 TYPE_1__* acpi_default_supported_interfaces ; 
 int /*<<< orphan*/  acpi_gbl_osi_mutex ; 
 TYPE_1__* acpi_gbl_supported_interfaces ; 
 int /*<<< orphan*/  acpi_os_acquire_mutex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_os_release_mutex (int /*<<< orphan*/ ) ; 

acpi_status acpi_ut_initialize_interfaces(void)
{
	acpi_status status;
	u32 i;

	status = acpi_os_acquire_mutex(acpi_gbl_osi_mutex, ACPI_WAIT_FOREVER);
	if (ACPI_FAILURE(status)) {
		return (status);
	}

	acpi_gbl_supported_interfaces = acpi_default_supported_interfaces;

	/* Link the static list of supported interfaces */

	for (i = 0;
	     i < (ACPI_ARRAY_LENGTH(acpi_default_supported_interfaces) - 1);
	     i++) {
		acpi_default_supported_interfaces[i].next =
		    &acpi_default_supported_interfaces[(acpi_size)i + 1];
	}

	acpi_os_release_mutex(acpi_gbl_osi_mutex);
	return (AE_OK);
}