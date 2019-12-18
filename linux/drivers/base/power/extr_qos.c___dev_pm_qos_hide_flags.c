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
struct TYPE_4__ {scalar_t__ flags_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_PM_QOS_FLAGS ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (TYPE_2__*) ; 
 int /*<<< orphan*/  __dev_pm_qos_drop_user_request (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __dev_pm_qos_hide_flags(struct device *dev)
{
	if (!IS_ERR_OR_NULL(dev->power.qos) && dev->power.qos->flags_req)
		__dev_pm_qos_drop_user_request(dev, DEV_PM_QOS_FLAGS);
}