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
struct inode {int /*<<< orphan*/  i_rdev; } ;
struct device {int /*<<< orphan*/  release; int /*<<< orphan*/  groups; struct device* parent; int /*<<< orphan*/  class; int /*<<< orphan*/ * bus; int /*<<< orphan*/  devt; } ;
struct dev_pagemap {int dummy; } ;
struct dev_dax {int /*<<< orphan*/  target_node; struct dax_region* region; struct dax_device* dax_dev; struct device dev; int /*<<< orphan*/  pgmap; } ;
struct dax_region {struct device* dev; int /*<<< orphan*/  id; int /*<<< orphan*/  kref; int /*<<< orphan*/  target_node; } ;
struct dax_device {int dummy; } ;
typedef  enum dev_dax_subsys { ____Placeholder_dev_dax_subsys } dev_dax_subsys ;

/* Variables and functions */
 int /*<<< orphan*/  DAXDEV_F_SYNC ; 
 int DEV_DAX_BUS ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct dev_dax* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct dax_device* alloc_dax (struct dev_dax*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dax_attribute_groups ; 
 int /*<<< orphan*/  dax_bus_type ; 
 int /*<<< orphan*/  dax_class ; 
 struct inode* dax_inode (struct dax_device*) ; 
 int /*<<< orphan*/  dev_dax_release ; 
 int /*<<< orphan*/  dev_set_name (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 int device_add (struct device*) ; 
 int /*<<< orphan*/  device_initialize (struct device*) ; 
 int devm_add_action_or_reset (struct device*,int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  kfree (struct dev_dax*) ; 
 int /*<<< orphan*/  kill_dax (struct dax_device*) ; 
 int /*<<< orphan*/  kill_dev_dax (struct dev_dax*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 struct dev_dax* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct dev_pagemap*,int) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  unregister_dev_dax ; 

struct dev_dax *__devm_create_dev_dax(struct dax_region *dax_region, int id,
		struct dev_pagemap *pgmap, enum dev_dax_subsys subsys)
{
	struct device *parent = dax_region->dev;
	struct dax_device *dax_dev;
	struct dev_dax *dev_dax;
	struct inode *inode;
	struct device *dev;
	int rc = -ENOMEM;

	if (id < 0)
		return ERR_PTR(-EINVAL);

	dev_dax = kzalloc(sizeof(*dev_dax), GFP_KERNEL);
	if (!dev_dax)
		return ERR_PTR(-ENOMEM);

	memcpy(&dev_dax->pgmap, pgmap, sizeof(*pgmap));

	/*
	 * No 'host' or dax_operations since there is no access to this
	 * device outside of mmap of the resulting character device.
	 */
	dax_dev = alloc_dax(dev_dax, NULL, NULL, DAXDEV_F_SYNC);
	if (!dax_dev)
		goto err;

	/* a device_dax instance is dead while the driver is not attached */
	kill_dax(dax_dev);

	/* from here on we're committed to teardown via dax_dev_release() */
	dev = &dev_dax->dev;
	device_initialize(dev);

	dev_dax->dax_dev = dax_dev;
	dev_dax->region = dax_region;
	dev_dax->target_node = dax_region->target_node;
	kref_get(&dax_region->kref);

	inode = dax_inode(dax_dev);
	dev->devt = inode->i_rdev;
	if (subsys == DEV_DAX_BUS)
		dev->bus = &dax_bus_type;
	else
		dev->class = dax_class;
	dev->parent = parent;
	dev->groups = dax_attribute_groups;
	dev->release = dev_dax_release;
	dev_set_name(dev, "dax%d.%d", dax_region->id, id);

	rc = device_add(dev);
	if (rc) {
		kill_dev_dax(dev_dax);
		put_device(dev);
		return ERR_PTR(rc);
	}

	rc = devm_add_action_or_reset(dax_region->dev, unregister_dev_dax, dev);
	if (rc)
		return ERR_PTR(rc);

	return dev_dax;

 err:
	kfree(dev_dax);

	return ERR_PTR(rc);
}