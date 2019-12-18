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
struct dev_pm_qos_request {int dummy; } ;
typedef  scalar_t__ s32 ;
struct TYPE_4__ {struct dev_pm_qos_request* latency_tolerance_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_PM_QOS_LATENCY_TOLERANCE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR_OR_NULL (TYPE_2__*) ; 
 scalar_t__ PM_QOS_LATENCY_TOLERANCE_NO_CONSTRAINT ; 
 int __dev_pm_qos_add_request (struct device*,struct dev_pm_qos_request*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  __dev_pm_qos_drop_user_request (struct device*,int /*<<< orphan*/ ) ; 
 int __dev_pm_qos_update_request (struct dev_pm_qos_request*,scalar_t__) ; 
 int /*<<< orphan*/  dev_pm_qos_mtx ; 
 int /*<<< orphan*/  kfree (struct dev_pm_qos_request*) ; 
 struct dev_pm_qos_request* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int dev_pm_qos_update_user_latency_tolerance(struct device *dev, s32 val)
{
	int ret;

	mutex_lock(&dev_pm_qos_mtx);

	if (IS_ERR_OR_NULL(dev->power.qos)
	    || !dev->power.qos->latency_tolerance_req) {
		struct dev_pm_qos_request *req;

		if (val < 0) {
			if (val == PM_QOS_LATENCY_TOLERANCE_NO_CONSTRAINT)
				ret = 0;
			else
				ret = -EINVAL;
			goto out;
		}
		req = kzalloc(sizeof(*req), GFP_KERNEL);
		if (!req) {
			ret = -ENOMEM;
			goto out;
		}
		ret = __dev_pm_qos_add_request(dev, req, DEV_PM_QOS_LATENCY_TOLERANCE, val);
		if (ret < 0) {
			kfree(req);
			goto out;
		}
		dev->power.qos->latency_tolerance_req = req;
	} else {
		if (val < 0) {
			__dev_pm_qos_drop_user_request(dev, DEV_PM_QOS_LATENCY_TOLERANCE);
			ret = 0;
		} else {
			ret = __dev_pm_qos_update_request(dev->power.qos->latency_tolerance_req, val);
		}
	}

 out:
	mutex_unlock(&dev_pm_qos_mtx);
	return ret;
}