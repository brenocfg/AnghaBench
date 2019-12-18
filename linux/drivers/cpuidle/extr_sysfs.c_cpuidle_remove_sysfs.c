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
struct cpuidle_device_kobj {int /*<<< orphan*/  kobj_unregister; int /*<<< orphan*/  kobj; } ;
struct cpuidle_device {struct cpuidle_device_kobj* kobj_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct cpuidle_device_kobj*) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void cpuidle_remove_sysfs(struct cpuidle_device *dev)
{
	struct cpuidle_device_kobj *kdev = dev->kobj_dev;

	kobject_put(&kdev->kobj);
	wait_for_completion(&kdev->kobj_unregister);
	kfree(kdev);
}