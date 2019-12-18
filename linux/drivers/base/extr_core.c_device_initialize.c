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
struct TYPE_3__ {int /*<<< orphan*/  status; int /*<<< orphan*/  suppliers; int /*<<< orphan*/  consumers; } ;
struct TYPE_4__ {int /*<<< orphan*/  kset; } ;
struct device {TYPE_1__ links; int /*<<< orphan*/  msi_list; int /*<<< orphan*/  devres_head; int /*<<< orphan*/  devres_lock; int /*<<< orphan*/  mutex; int /*<<< orphan*/  lockdep_mutex; int /*<<< orphan*/  dma_pools; TYPE_2__ kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  DL_DEV_NO_DRIVER ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_ktype ; 
 int /*<<< orphan*/  device_pm_init (struct device*) ; 
 int /*<<< orphan*/  devices_kset ; 
 int /*<<< orphan*/  kobject_init (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_set_novalidate_class (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_dev_node (struct device*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void device_initialize(struct device *dev)
{
	dev->kobj.kset = devices_kset;
	kobject_init(&dev->kobj, &device_ktype);
	INIT_LIST_HEAD(&dev->dma_pools);
	mutex_init(&dev->mutex);
#ifdef CONFIG_PROVE_LOCKING
	mutex_init(&dev->lockdep_mutex);
#endif
	lockdep_set_novalidate_class(&dev->mutex);
	spin_lock_init(&dev->devres_lock);
	INIT_LIST_HEAD(&dev->devres_head);
	device_pm_init(dev);
	set_dev_node(dev, -1);
#ifdef CONFIG_GENERIC_MSI_IRQ
	INIT_LIST_HEAD(&dev->msi_list);
#endif
	INIT_LIST_HEAD(&dev->links.consumers);
	INIT_LIST_HEAD(&dev->links.suppliers);
	dev->links.status = DL_DEV_NO_DRIVER;
}