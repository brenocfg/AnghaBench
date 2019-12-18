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
typedef  int /*<<< orphan*/  u32 ;
struct acpi_device {int dummy; } ;
typedef  int acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ acpi_bus_get_device (int /*<<< orphan*/ ,struct acpi_device**) ; 
 void* acpi_driver_data (struct acpi_device*) ; 

__attribute__((used)) static acpi_status longhaul_walk_callback(acpi_handle obj_handle,
					  u32 nesting_level,
					  void *context, void **return_value)
{
	struct acpi_device *d;

	if (acpi_bus_get_device(obj_handle, &d))
		return 0;

	*return_value = acpi_driver_data(d);
	return 1;
}