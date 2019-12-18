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
struct TYPE_9__ {TYPE_5__* qos; } ;
struct device {TYPE_4__ power; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_10__ {TYPE_3__* latency_tolerance_req; } ;
struct TYPE_6__ {int /*<<< orphan*/  prio; } ;
struct TYPE_7__ {TYPE_1__ pnode; } ;
struct TYPE_8__ {TYPE_2__ data; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (TYPE_5__*) ; 
 int /*<<< orphan*/  PM_QOS_LATENCY_TOLERANCE_NO_CONSTRAINT ; 
 int /*<<< orphan*/  dev_pm_qos_mtx ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

s32 dev_pm_qos_get_user_latency_tolerance(struct device *dev)
{
	s32 ret;

	mutex_lock(&dev_pm_qos_mtx);
	ret = IS_ERR_OR_NULL(dev->power.qos)
		|| !dev->power.qos->latency_tolerance_req ?
			PM_QOS_LATENCY_TOLERANCE_NO_CONSTRAINT :
			dev->power.qos->latency_tolerance_req->data.pnode.prio;
	mutex_unlock(&dev_pm_qos_mtx);
	return ret;
}