#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct inode {struct dev_dax* i_cdev; } ;
struct device {int /*<<< orphan*/  devt; int /*<<< orphan*/  kobj; TYPE_4__* driver; TYPE_3__* parent; scalar_t__ class; } ;
struct TYPE_10__ {int /*<<< orphan*/  type; } ;
struct dev_dax {int /*<<< orphan*/  owner; TYPE_5__ pgmap; TYPE_1__* region; struct dax_device* dax_dev; } ;
struct dax_device {int dummy; } ;
struct cdev {int /*<<< orphan*/  owner; TYPE_5__ pgmap; TYPE_1__* region; struct dax_device* dax_dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  owner; } ;
struct TYPE_8__ {TYPE_2__* driver; } ;
struct TYPE_7__ {int /*<<< orphan*/  owner; } ;
struct TYPE_6__ {struct resource res; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  MEMORY_DEVICE_DEVDAX ; 
 int PTR_ERR (void*) ; 
 int cdev_add (struct dev_dax*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdev_init (struct dev_dax*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cdev_set_parent (struct dev_dax*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dax_fops ; 
 struct inode* dax_inode (struct dax_device*) ; 
 int /*<<< orphan*/  dev_dax_cdev_del ; 
 int /*<<< orphan*/  dev_dax_kill ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,struct resource*) ; 
 int devm_add_action_or_reset (struct device*,int /*<<< orphan*/ ,struct dev_dax*) ; 
 void* devm_memremap_pages (struct device*,TYPE_5__*) ; 
 int /*<<< orphan*/  devm_request_mem_region (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  run_dax (struct dax_device*) ; 
 struct dev_dax* to_dev_dax (struct device*) ; 

int dev_dax_probe(struct device *dev)
{
	struct dev_dax *dev_dax = to_dev_dax(dev);
	struct dax_device *dax_dev = dev_dax->dax_dev;
	struct resource *res = &dev_dax->region->res;
	struct inode *inode;
	struct cdev *cdev;
	void *addr;
	int rc;

	/* 1:1 map region resource range to device-dax instance range */
	if (!devm_request_mem_region(dev, res->start, resource_size(res),
				dev_name(dev))) {
		dev_warn(dev, "could not reserve region %pR\n", res);
		return -EBUSY;
	}

	dev_dax->pgmap.type = MEMORY_DEVICE_DEVDAX;
	addr = devm_memremap_pages(dev, &dev_dax->pgmap);
	if (IS_ERR(addr))
		return PTR_ERR(addr);

	inode = dax_inode(dax_dev);
	cdev = inode->i_cdev;
	cdev_init(cdev, &dax_fops);
	if (dev->class) {
		/* for the CONFIG_DEV_DAX_PMEM_COMPAT case */
		cdev->owner = dev->parent->driver->owner;
	} else
		cdev->owner = dev->driver->owner;
	cdev_set_parent(cdev, &dev->kobj);
	rc = cdev_add(cdev, dev->devt, 1);
	if (rc)
		return rc;

	rc = devm_add_action_or_reset(dev, dev_dax_cdev_del, cdev);
	if (rc)
		return rc;

	run_dax(dax_dev);
	return devm_add_action_or_reset(dev, dev_dax_kill, dev_dax);
}