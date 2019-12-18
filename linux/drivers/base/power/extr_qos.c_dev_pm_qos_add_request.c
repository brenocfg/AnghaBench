#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct device {int dummy; } ;
struct dev_pm_qos_request {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  enum dev_pm_qos_req_type { ____Placeholder_dev_pm_qos_req_type } dev_pm_qos_req_type ;

/* Variables and functions */
 int __dev_pm_qos_add_request (struct device*,struct dev_pm_qos_request*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_pm_qos_mtx ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int dev_pm_qos_add_request(struct device *dev, struct dev_pm_qos_request *req,
			   enum dev_pm_qos_req_type type, s32 value)
{
	int ret;

	mutex_lock(&dev_pm_qos_mtx);
	ret = __dev_pm_qos_add_request(dev, req, type, value);
	mutex_unlock(&dev_pm_qos_mtx);
	return ret;
}