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
struct fwnode_handle {int dummy; } ;
struct device {TYPE_1__* of_node; } ;
struct acpi_device {int dummy; } ;
struct TYPE_2__ {struct fwnode_handle fwnode; } ;

/* Variables and functions */
 struct acpi_device* ACPI_COMPANION (struct device*) ; 
 struct fwnode_handle* acpi_fwnode_handle (struct acpi_device*) ; 
 struct fwnode_handle* fwnode_get_next_child_node (struct fwnode_handle*,struct fwnode_handle*) ; 

struct fwnode_handle *device_get_next_child_node(struct device *dev,
						 struct fwnode_handle *child)
{
	struct acpi_device *adev = ACPI_COMPANION(dev);
	struct fwnode_handle *fwnode = NULL;

	if (dev->of_node)
		fwnode = &dev->of_node->fwnode;
	else if (adev)
		fwnode = acpi_fwnode_handle(adev);

	return fwnode_get_next_child_node(fwnode, child);
}