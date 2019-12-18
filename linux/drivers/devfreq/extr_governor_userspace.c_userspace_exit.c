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
struct TYPE_4__ {scalar_t__ sd; } ;
struct TYPE_3__ {TYPE_2__ kobj; } ;
struct devfreq {int /*<<< orphan*/ * data; TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_group ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void userspace_exit(struct devfreq *devfreq)
{
	/*
	 * Remove the sysfs entry, unless this is being called after
	 * device_del(), which should have done this already via kobject_del().
	 */
	if (devfreq->dev.kobj.sd)
		sysfs_remove_group(&devfreq->dev.kobj, &dev_attr_group);

	kfree(devfreq->data);
	devfreq->data = NULL;
}