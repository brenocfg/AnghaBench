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
struct acpi_resource {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ ACPI_RESOURCE_TYPE_SERIAL_BUS ; 

__attribute__((used)) static int acpi_check_serial_bus_slave(struct acpi_resource *ares, void *data)
{
	bool *is_serial_bus_slave_p = data;

	if (ares->type != ACPI_RESOURCE_TYPE_SERIAL_BUS)
		return 1;

	*is_serial_bus_slave_p = true;

	 /* no need to do more checking */
	return -1;
}