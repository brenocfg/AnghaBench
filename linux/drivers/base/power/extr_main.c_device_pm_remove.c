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
struct TYPE_4__ {int in_dpm_list; int /*<<< orphan*/  entry; int /*<<< orphan*/  completion; } ;
struct device {TYPE_2__ power; TYPE_1__* bus; } ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  device_pm_check_callbacks (struct device*) ; 
 scalar_t__ device_pm_not_required (struct device*) ; 
 int /*<<< orphan*/  device_wakeup_disable (struct device*) ; 
 int /*<<< orphan*/  dpm_list_mtx ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_remove (struct device*) ; 
 int /*<<< orphan*/  pr_debug (char*,char*,int /*<<< orphan*/ ) ; 

void device_pm_remove(struct device *dev)
{
	if (device_pm_not_required(dev))
		return;

	pr_debug("Removing info for %s:%s\n",
		 dev->bus ? dev->bus->name : "No Bus", dev_name(dev));
	complete_all(&dev->power.completion);
	mutex_lock(&dpm_list_mtx);
	list_del_init(&dev->power.entry);
	dev->power.in_dpm_list = false;
	mutex_unlock(&dpm_list_mtx);
	device_wakeup_disable(dev);
	pm_runtime_remove(dev);
	device_pm_check_callbacks(dev);
}