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
struct acpi_device {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  acpi_get_data_full (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,void (*) (void*)) ; 
 int /*<<< orphan*/  acpi_scan_drop_device ; 

__attribute__((used)) static int acpi_get_device_data(acpi_handle handle, struct acpi_device **device,
				void (*callback)(void *))
{
	acpi_status status;

	if (!device)
		return -EINVAL;

	status = acpi_get_data_full(handle, acpi_scan_drop_device,
				    (void **)device, callback);
	if (ACPI_FAILURE(status) || !*device) {
		ACPI_DEBUG_PRINT((ACPI_DB_INFO, "No context for object [%p]\n",
				  handle));
		return -ENODEV;
	}
	return 0;
}