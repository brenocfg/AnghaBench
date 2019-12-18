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
struct swnode {int /*<<< orphan*/  kobj; } ;
struct fwnode_handle {struct fwnode_handle* secondary; } ;
struct device {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
#define  KOBJ_ADD 129 
#define  KOBJ_REMOVE 128 
 struct fwnode_handle* dev_fwnode (struct device*) ; 
 char* dev_name (struct device*) ; 
 int /*<<< orphan*/  is_software_node (struct fwnode_handle*) ; 
 int /*<<< orphan*/  kobject_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int sysfs_create_link (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 
 struct swnode* to_swnode (struct fwnode_handle*) ; 

int software_node_notify(struct device *dev, unsigned long action)
{
	struct fwnode_handle *fwnode = dev_fwnode(dev);
	struct swnode *swnode;
	int ret;

	if (!fwnode)
		return 0;

	if (!is_software_node(fwnode))
		fwnode = fwnode->secondary;
	if (!is_software_node(fwnode))
		return 0;

	swnode = to_swnode(fwnode);

	switch (action) {
	case KOBJ_ADD:
		ret = sysfs_create_link(&dev->kobj, &swnode->kobj,
					"software_node");
		if (ret)
			break;

		ret = sysfs_create_link(&swnode->kobj, &dev->kobj,
					dev_name(dev));
		if (ret) {
			sysfs_remove_link(&dev->kobj, "software_node");
			break;
		}
		kobject_get(&swnode->kobj);
		break;
	case KOBJ_REMOVE:
		sysfs_remove_link(&swnode->kobj, dev_name(dev));
		sysfs_remove_link(&dev->kobj, "software_node");
		kobject_put(&swnode->kobj);
		break;
	default:
		break;
	}

	return 0;
}