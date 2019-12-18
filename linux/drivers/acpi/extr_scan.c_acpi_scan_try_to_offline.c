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
struct device {int dummy; } ;
struct acpi_device {int /*<<< orphan*/  handle; } ;
typedef  scalar_t__ acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_TYPE_ANY ; 
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 scalar_t__ AE_SUPPORT ; 
 int EBUSY ; 
 int EPERM ; 
 int /*<<< orphan*/  acpi_bus_offline (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void**) ; 
 int /*<<< orphan*/  acpi_bus_online (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ acpi_walk_namespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 

__attribute__((used)) static int acpi_scan_try_to_offline(struct acpi_device *device)
{
	acpi_handle handle = device->handle;
	struct device *errdev = NULL;
	acpi_status status;

	/*
	 * Carry out two passes here and ignore errors in the first pass,
	 * because if the devices in question are memory blocks and
	 * CONFIG_MEMCG is set, one of the blocks may hold data structures
	 * that the other blocks depend on, but it is not known in advance which
	 * block holds them.
	 *
	 * If the first pass is successful, the second one isn't needed, though.
	 */
	status = acpi_walk_namespace(ACPI_TYPE_ANY, handle, ACPI_UINT32_MAX,
				     NULL, acpi_bus_offline, (void *)false,
				     (void **)&errdev);
	if (status == AE_SUPPORT) {
		dev_warn(errdev, "Offline disabled.\n");
		acpi_walk_namespace(ACPI_TYPE_ANY, handle, ACPI_UINT32_MAX,
				    acpi_bus_online, NULL, NULL, NULL);
		return -EPERM;
	}
	acpi_bus_offline(handle, 0, (void *)false, (void **)&errdev);
	if (errdev) {
		errdev = NULL;
		acpi_walk_namespace(ACPI_TYPE_ANY, handle, ACPI_UINT32_MAX,
				    NULL, acpi_bus_offline, (void *)true,
				    (void **)&errdev);
		if (!errdev)
			acpi_bus_offline(handle, 0, (void *)true,
					 (void **)&errdev);

		if (errdev) {
			dev_warn(errdev, "Offline failed.\n");
			acpi_bus_online(handle, 0, NULL, NULL);
			acpi_walk_namespace(ACPI_TYPE_ANY, handle,
					    ACPI_UINT32_MAX, acpi_bus_online,
					    NULL, NULL, NULL);
			return -EBUSY;
		}
	}
	return 0;
}