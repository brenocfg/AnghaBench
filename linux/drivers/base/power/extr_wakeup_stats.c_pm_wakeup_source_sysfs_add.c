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
struct TYPE_3__ {TYPE_2__* wakeup; } ;
struct device {TYPE_1__ power; } ;
struct TYPE_4__ {scalar_t__ dev; } ;

/* Variables and functions */
 int wakeup_source_sysfs_add (struct device*,TYPE_2__*) ; 

int pm_wakeup_source_sysfs_add(struct device *parent)
{
	if (!parent->power.wakeup || parent->power.wakeup->dev)
		return 0;

	return wakeup_source_sysfs_add(parent, parent->power.wakeup);
}