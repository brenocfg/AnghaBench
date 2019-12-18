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
struct TYPE_3__ {TYPE_2__* qos; } ;
struct device {TYPE_1__ power; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_4__ {int /*<<< orphan*/  flags_req; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR_OR_NULL (TYPE_2__*) ; 
 int __dev_pm_qos_update_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_pm_qos_mtx ; 
 int /*<<< orphan*/  dev_pm_qos_requested_flags (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put (struct device*) ; 

int dev_pm_qos_update_flags(struct device *dev, s32 mask, bool set)
{
	s32 value;
	int ret;

	pm_runtime_get_sync(dev);
	mutex_lock(&dev_pm_qos_mtx);

	if (IS_ERR_OR_NULL(dev->power.qos) || !dev->power.qos->flags_req) {
		ret = -EINVAL;
		goto out;
	}

	value = dev_pm_qos_requested_flags(dev);
	if (set)
		value |= mask;
	else
		value &= ~mask;

	ret = __dev_pm_qos_update_request(dev->power.qos->flags_req, value);

 out:
	mutex_unlock(&dev_pm_qos_mtx);
	pm_runtime_put(dev);
	return ret;
}