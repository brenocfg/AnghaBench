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
struct property_entry {int dummy; } ;
struct fwnode_handle {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct fwnode_handle*) ; 
 int PTR_ERR (struct fwnode_handle*) ; 
 struct fwnode_handle* fwnode_create_software_node (struct property_entry const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_secondary_fwnode (struct device*,struct fwnode_handle*) ; 

int device_add_properties(struct device *dev,
			  const struct property_entry *properties)
{
	struct fwnode_handle *fwnode;

	fwnode = fwnode_create_software_node(properties, NULL);
	if (IS_ERR(fwnode))
		return PTR_ERR(fwnode);

	set_secondary_fwnode(dev, fwnode);
	return 0;
}