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
struct list_head {int dummy; } ;
struct acpi_device_id {char* member_0; } ;
struct acpi_device {int /*<<< orphan*/  fwnode; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int /*<<< orphan*/  acpi_check_serial_bus_slave ; 
 int /*<<< orphan*/  acpi_dev_free_resource_list (struct list_head*) ; 
 int /*<<< orphan*/  acpi_dev_get_resources (struct acpi_device*,struct list_head*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ acpi_is_indirect_io_slave (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_match_device_ids (struct acpi_device*,struct acpi_device_id const*) ; 
 scalar_t__ fwnode_property_present (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ x86_apple_machine ; 

__attribute__((used)) static bool acpi_device_enumeration_by_parent(struct acpi_device *device)
{
	struct list_head resource_list;
	bool is_serial_bus_slave = false;
	/*
	 * These devices have multiple I2cSerialBus resources and an i2c-client
	 * must be instantiated for each, each with its own i2c_device_id.
	 * Normally we only instantiate an i2c-client for the first resource,
	 * using the ACPI HID as id. These special cases are handled by the
	 * drivers/platform/x86/i2c-multi-instantiate.c driver, which knows
	 * which i2c_device_id to use for each resource.
	 */
	static const struct acpi_device_id i2c_multi_instantiate_ids[] = {
		{"BSG1160", },
		{"BSG2150", },
		{"INT33FE", },
		{"INT3515", },
		{}
	};

	if (acpi_is_indirect_io_slave(device))
		return true;

	/* Macs use device properties in lieu of _CRS resources */
	if (x86_apple_machine &&
	    (fwnode_property_present(&device->fwnode, "spiSclkPeriod") ||
	     fwnode_property_present(&device->fwnode, "i2cAddress") ||
	     fwnode_property_present(&device->fwnode, "baud")))
		return true;

	/* Instantiate a pdev for the i2c-multi-instantiate drv to bind to */
	if (!acpi_match_device_ids(device, i2c_multi_instantiate_ids))
		return false;

	INIT_LIST_HEAD(&resource_list);
	acpi_dev_get_resources(device, &resource_list,
			       acpi_check_serial_bus_slave,
			       &is_serial_bus_slave);
	acpi_dev_free_resource_list(&resource_list);

	return is_serial_bus_slave;
}