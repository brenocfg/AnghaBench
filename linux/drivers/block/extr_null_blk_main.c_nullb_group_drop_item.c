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
struct nullb_device {int power; int /*<<< orphan*/  nullb; int /*<<< orphan*/  flags; } ;
struct config_item {int dummy; } ;
struct config_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NULLB_DEV_FL_UP ; 
 int /*<<< orphan*/  config_item_put (struct config_item*) ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  null_del_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct nullb_device* to_nullb_device (struct config_item*) ; 

__attribute__((used)) static void
nullb_group_drop_item(struct config_group *group, struct config_item *item)
{
	struct nullb_device *dev = to_nullb_device(item);

	if (test_and_clear_bit(NULLB_DEV_FL_UP, &dev->flags)) {
		mutex_lock(&lock);
		dev->power = false;
		null_del_dev(dev->nullb);
		mutex_unlock(&lock);
	}

	config_item_put(item);
}