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
struct TYPE_2__ {unsigned int runtime_status; int /*<<< orphan*/  lock; scalar_t__ runtime_error; int /*<<< orphan*/  child_count; int /*<<< orphan*/  ignore_children; scalar_t__ disable_depth; } ;
struct device {TYPE_1__ power; struct device* parent; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int EINVAL ; 
 unsigned int RPM_ACTIVE ; 
 unsigned int RPM_SUSPENDED ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int /*<<< orphan*/  __update_runtime_status (struct device*,unsigned int) ; 
 int /*<<< orphan*/  atomic_add_unless (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int device_links_read_lock () ; 
 int /*<<< orphan*/  device_links_read_unlock (int) ; 
 int /*<<< orphan*/  pm_request_idle (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int rpm_get_suppliers (struct device*) ; 
 int /*<<< orphan*/  rpm_put_suppliers (struct device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int __pm_runtime_set_status(struct device *dev, unsigned int status)
{
	struct device *parent = dev->parent;
	bool notify_parent = false;
	int error = 0;

	if (status != RPM_ACTIVE && status != RPM_SUSPENDED)
		return -EINVAL;

	spin_lock_irq(&dev->power.lock);

	/*
	 * Prevent PM-runtime from being enabled for the device or return an
	 * error if it is enabled already and working.
	 */
	if (dev->power.runtime_error || dev->power.disable_depth)
		dev->power.disable_depth++;
	else
		error = -EAGAIN;

	spin_unlock_irq(&dev->power.lock);

	if (error)
		return error;

	/*
	 * If the new status is RPM_ACTIVE, the suppliers can be activated
	 * upfront regardless of the current status, because next time
	 * rpm_put_suppliers() runs, the rpm_active refcounts of the links
	 * involved will be dropped down to one anyway.
	 */
	if (status == RPM_ACTIVE) {
		int idx = device_links_read_lock();

		error = rpm_get_suppliers(dev);
		if (error)
			status = RPM_SUSPENDED;

		device_links_read_unlock(idx);
	}

	spin_lock_irq(&dev->power.lock);

	if (dev->power.runtime_status == status || !parent)
		goto out_set;

	if (status == RPM_SUSPENDED) {
		atomic_add_unless(&parent->power.child_count, -1, 0);
		notify_parent = !parent->power.ignore_children;
	} else {
		spin_lock_nested(&parent->power.lock, SINGLE_DEPTH_NESTING);

		/*
		 * It is invalid to put an active child under a parent that is
		 * not active, has runtime PM enabled and the
		 * 'power.ignore_children' flag unset.
		 */
		if (!parent->power.disable_depth
		    && !parent->power.ignore_children
		    && parent->power.runtime_status != RPM_ACTIVE) {
			dev_err(dev, "runtime PM trying to activate child device %s but parent (%s) is not active\n",
				dev_name(dev),
				dev_name(parent));
			error = -EBUSY;
		} else if (dev->power.runtime_status == RPM_SUSPENDED) {
			atomic_inc(&parent->power.child_count);
		}

		spin_unlock(&parent->power.lock);

		if (error) {
			status = RPM_SUSPENDED;
			goto out;
		}
	}

 out_set:
	__update_runtime_status(dev, status);
	if (!error)
		dev->power.runtime_error = 0;

 out:
	spin_unlock_irq(&dev->power.lock);

	if (notify_parent)
		pm_request_idle(parent);

	if (status == RPM_SUSPENDED) {
		int idx = device_links_read_lock();

		rpm_put_suppliers(dev);

		device_links_read_unlock(idx);
	}

	pm_runtime_enable(dev);

	return error;
}