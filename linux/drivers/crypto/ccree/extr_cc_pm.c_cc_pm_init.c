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
 int /*<<< orphan*/  CC_SUSPEND_TIMEOUT ; 
 struct device* drvdata_to_dev (struct cc_drvdata*) ; 
 int pm_runtime_set_active (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (struct device*) ; 

int cc_pm_init(struct cc_drvdata *drvdata)
{
	struct device *dev = drvdata_to_dev(drvdata);

	/* must be before the enabling to avoid resdundent suspending */
	pm_runtime_set_autosuspend_delay(dev, CC_SUSPEND_TIMEOUT);
	pm_runtime_use_autosuspend(dev);
	/* activate the PM module */
	return pm_runtime_set_active(dev);
}