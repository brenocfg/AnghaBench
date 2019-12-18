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
struct TYPE_4__ {TYPE_1__* qos; } ;
struct device {TYPE_2__ power; } ;
struct dev_pm_qos_request {int dummy; } ;
typedef  enum dev_pm_qos_req_type { ____Placeholder_dev_pm_qos_req_type } dev_pm_qos_req_type ;
struct TYPE_3__ {struct dev_pm_qos_request* flags_req; struct dev_pm_qos_request* latency_tolerance_req; struct dev_pm_qos_request* resume_latency_req; } ;

/* Variables and functions */
#define  DEV_PM_QOS_FLAGS 130 
#define  DEV_PM_QOS_LATENCY_TOLERANCE 129 
#define  DEV_PM_QOS_RESUME_LATENCY 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __dev_pm_qos_remove_request (struct dev_pm_qos_request*) ; 
 int /*<<< orphan*/  kfree (struct dev_pm_qos_request*) ; 

__attribute__((used)) static void __dev_pm_qos_drop_user_request(struct device *dev,
					   enum dev_pm_qos_req_type type)
{
	struct dev_pm_qos_request *req = NULL;

	switch(type) {
	case DEV_PM_QOS_RESUME_LATENCY:
		req = dev->power.qos->resume_latency_req;
		dev->power.qos->resume_latency_req = NULL;
		break;
	case DEV_PM_QOS_LATENCY_TOLERANCE:
		req = dev->power.qos->latency_tolerance_req;
		dev->power.qos->latency_tolerance_req = NULL;
		break;
	case DEV_PM_QOS_FLAGS:
		req = dev->power.qos->flags_req;
		dev->power.qos->flags_req = NULL;
		break;
	default:
		WARN_ON(1);
		return;
	}
	__dev_pm_qos_remove_request(req);
	kfree(req);
}