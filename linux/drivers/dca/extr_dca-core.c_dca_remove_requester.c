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
struct device {int dummy; } ;
struct dca_provider {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* remove_requester ) (struct dca_provider*,struct device*) ;} ;

/* Variables and functions */
 int EFAULT ; 
 int ENODEV ; 
 struct dca_provider* dca_find_provider_by_dev (struct device*) ; 
 int /*<<< orphan*/  dca_lock ; 
 int /*<<< orphan*/  dca_sysfs_remove_req (struct dca_provider*,int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct dca_provider*,struct device*) ; 

int dca_remove_requester(struct device *dev)
{
	struct dca_provider *dca;
	int slot;
	unsigned long flags;

	if (!dev)
		return -EFAULT;

	raw_spin_lock_irqsave(&dca_lock, flags);
	dca = dca_find_provider_by_dev(dev);
	if (!dca) {
		raw_spin_unlock_irqrestore(&dca_lock, flags);
		return -ENODEV;
	}
	slot = dca->ops->remove_requester(dca, dev);
	raw_spin_unlock_irqrestore(&dca_lock, flags);

	if (slot < 0)
		return slot;

	dca_sysfs_remove_req(dca, slot);

	return 0;
}