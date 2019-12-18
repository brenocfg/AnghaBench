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
struct device {TYPE_1__* driver; } ;
struct acpi_device_id {scalar_t__ driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  acpi_match_table; } ;

/* Variables and functions */
 struct acpi_device_id* acpi_match_device (int /*<<< orphan*/ ,struct device const*) ; 
 void const* acpi_of_device_get_match_data (struct device const*) ; 

const void *acpi_device_get_match_data(const struct device *dev)
{
	const struct acpi_device_id *match;

	if (!dev->driver->acpi_match_table)
		return acpi_of_device_get_match_data(dev);

	match = acpi_match_device(dev->driver->acpi_match_table, dev);
	if (!match)
		return NULL;

	return (const void *)match->driver_data;
}