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
struct TYPE_2__ {int /*<<< orphan*/  lock; struct dev_pm_qos* qos; } ;
struct device {TYPE_1__ power; } ;
struct dev_pm_qos {int /*<<< orphan*/  resume_latency; } ;
typedef  scalar_t__ s32 ;
typedef  enum dev_pm_qos_req_type { ____Placeholder_dev_pm_qos_req_type } dev_pm_qos_req_type ;

/* Variables and functions */
 int DEV_PM_QOS_RESUME_LATENCY ; 
 scalar_t__ IS_ERR_OR_NULL (struct dev_pm_qos*) ; 
 scalar_t__ PM_QOS_RESUME_LATENCY_NO_CONSTRAINT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ pm_qos_read_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

s32 dev_pm_qos_read_value(struct device *dev, enum dev_pm_qos_req_type type)
{
	struct dev_pm_qos *qos = dev->power.qos;
	unsigned long flags;
	s32 ret;

	spin_lock_irqsave(&dev->power.lock, flags);

	if (type == DEV_PM_QOS_RESUME_LATENCY) {
		ret = IS_ERR_OR_NULL(qos) ? PM_QOS_RESUME_LATENCY_NO_CONSTRAINT
			: pm_qos_read_value(&qos->resume_latency);
	} else {
		WARN_ON(1);
		ret = 0;
	}

	spin_unlock_irqrestore(&dev->power.lock, flags);

	return ret;
}