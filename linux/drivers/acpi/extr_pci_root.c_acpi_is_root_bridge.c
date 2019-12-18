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
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int acpi_bus_get_device (int /*<<< orphan*/ ,struct acpi_device**) ; 
 int acpi_match_device_ids (struct acpi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  root_device_ids ; 

int acpi_is_root_bridge(acpi_handle handle)
{
	int ret;
	struct acpi_device *device;

	ret = acpi_bus_get_device(handle, &device);
	if (ret)
		return 0;

	ret = acpi_match_device_ids(device, root_device_ids);
	if (ret)
		return 0;
	else
		return 1;
}