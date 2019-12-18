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
struct cc_drvdata {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  cc_req_queue_suspended (struct cc_drvdata*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct cc_drvdata* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (struct device*) ; 
 int pm_runtime_put_autosuspend (struct device*) ; 

int cc_pm_put_suspend(struct device *dev)
{
	int rc = 0;
	struct cc_drvdata *drvdata = dev_get_drvdata(dev);

	if (!cc_req_queue_suspended(drvdata)) {
		pm_runtime_mark_last_busy(dev);
		rc = pm_runtime_put_autosuspend(dev);
	} else {
		/* Something wrong happens*/
		dev_err(dev, "request to suspend already suspended queue");
		rc = -EBUSY;
	}
	return rc;
}