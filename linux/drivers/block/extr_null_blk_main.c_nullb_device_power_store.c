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
struct nullb_device {int power; int /*<<< orphan*/  flags; int /*<<< orphan*/  nullb; } ;
struct config_item {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  NULLB_DEV_FL_CONFIGURED ; 
 int /*<<< orphan*/  NULLB_DEV_FL_UP ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ null_add_dev (struct nullb_device*) ; 
 int /*<<< orphan*/  null_del_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ nullb_device_bool_attr_store (int*,char const*,size_t) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct nullb_device* to_nullb_device (struct config_item*) ; 

__attribute__((used)) static ssize_t nullb_device_power_store(struct config_item *item,
				     const char *page, size_t count)
{
	struct nullb_device *dev = to_nullb_device(item);
	bool newp = false;
	ssize_t ret;

	ret = nullb_device_bool_attr_store(&newp, page, count);
	if (ret < 0)
		return ret;

	if (!dev->power && newp) {
		if (test_and_set_bit(NULLB_DEV_FL_UP, &dev->flags))
			return count;
		if (null_add_dev(dev)) {
			clear_bit(NULLB_DEV_FL_UP, &dev->flags);
			return -ENOMEM;
		}

		set_bit(NULLB_DEV_FL_CONFIGURED, &dev->flags);
		dev->power = newp;
	} else if (dev->power && !newp) {
		if (test_and_clear_bit(NULLB_DEV_FL_UP, &dev->flags)) {
			mutex_lock(&lock);
			dev->power = newp;
			null_del_dev(dev->nullb);
			mutex_unlock(&lock);
		}
		clear_bit(NULLB_DEV_FL_CONFIGURED, &dev->flags);
	}

	return count;
}