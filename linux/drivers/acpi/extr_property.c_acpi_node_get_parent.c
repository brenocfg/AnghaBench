#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fwnode_handle {int dummy; } ;
struct acpi_device {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_handle ;
struct TYPE_4__ {struct fwnode_handle* parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_bus_get_device (int /*<<< orphan*/ ,struct acpi_device**) ; 
 struct fwnode_handle* acpi_fwnode_handle (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_get_parent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ is_acpi_data_node (struct fwnode_handle const*) ; 
 scalar_t__ is_acpi_device_node (struct fwnode_handle const*) ; 
 TYPE_2__* to_acpi_data_node (struct fwnode_handle const*) ; 
 TYPE_1__* to_acpi_device_node (struct fwnode_handle const*) ; 

struct fwnode_handle *acpi_node_get_parent(const struct fwnode_handle *fwnode)
{
	if (is_acpi_data_node(fwnode)) {
		/* All data nodes have parent pointer so just return that */
		return to_acpi_data_node(fwnode)->parent;
	} else if (is_acpi_device_node(fwnode)) {
		acpi_handle handle, parent_handle;

		handle = to_acpi_device_node(fwnode)->handle;
		if (ACPI_SUCCESS(acpi_get_parent(handle, &parent_handle))) {
			struct acpi_device *adev;

			if (!acpi_bus_get_device(parent_handle, &adev))
				return acpi_fwnode_handle(adev);
		}
	}

	return NULL;
}