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
struct fwnode_handle {int /*<<< orphan*/  secondary; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct fwnode_handle* dev_fwnode (struct device*) ; 
 int /*<<< orphan*/  fwnode_remove_software_node (int /*<<< orphan*/ ) ; 
 scalar_t__ is_software_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_secondary_fwnode (struct device*,int /*<<< orphan*/ *) ; 

void device_remove_properties(struct device *dev)
{
	struct fwnode_handle *fwnode = dev_fwnode(dev);

	if (!fwnode)
		return;

	if (is_software_node(fwnode->secondary)) {
		fwnode_remove_software_node(fwnode->secondary);
		set_secondary_fwnode(dev, NULL);
	}
}