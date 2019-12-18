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
struct TYPE_3__ {int /*<<< orphan*/  entry; } ;
struct device {TYPE_1__ kobj; } ;
struct TYPE_4__ {int /*<<< orphan*/  list_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_name (struct device*) ; 
 TYPE_2__* devices_kset ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void devices_kset_move_before(struct device *deva, struct device *devb)
{
	if (!devices_kset)
		return;
	pr_debug("devices_kset: Moving %s before %s\n",
		 dev_name(deva), dev_name(devb));
	spin_lock(&devices_kset->list_lock);
	list_move_tail(&deva->kobj.entry, &devb->kobj.entry);
	spin_unlock(&devices_kset->list_lock);
}