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
struct zram {unsigned long disksize; int /*<<< orphan*/  init_lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  ZRAM_IDLE ; 
 int /*<<< orphan*/  ZRAM_UNDER_WB ; 
 struct zram* dev_to_zram (struct device*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_done (struct zram*) ; 
 int /*<<< orphan*/  sysfs_streq (char const*,char*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 scalar_t__ zram_allocated (struct zram*,int) ; 
 int /*<<< orphan*/  zram_set_flag (struct zram*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zram_slot_lock (struct zram*,int) ; 
 int /*<<< orphan*/  zram_slot_unlock (struct zram*,int) ; 
 int /*<<< orphan*/  zram_test_flag (struct zram*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t idle_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t len)
{
	struct zram *zram = dev_to_zram(dev);
	unsigned long nr_pages = zram->disksize >> PAGE_SHIFT;
	int index;

	if (!sysfs_streq(buf, "all"))
		return -EINVAL;

	down_read(&zram->init_lock);
	if (!init_done(zram)) {
		up_read(&zram->init_lock);
		return -EINVAL;
	}

	for (index = 0; index < nr_pages; index++) {
		/*
		 * Do not mark ZRAM_UNDER_WB slot as ZRAM_IDLE to close race.
		 * See the comment in writeback_store.
		 */
		zram_slot_lock(zram, index);
		if (zram_allocated(zram, index) &&
				!zram_test_flag(zram, index, ZRAM_UNDER_WB))
			zram_set_flag(zram, index, ZRAM_IDLE);
		zram_slot_unlock(zram, index);
	}

	up_read(&zram->init_lock);

	return len;
}