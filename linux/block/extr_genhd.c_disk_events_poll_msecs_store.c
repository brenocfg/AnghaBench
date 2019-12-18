#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gendisk {TYPE_1__* ev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {long poll_msecs; } ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t ENODEV ; 
 int /*<<< orphan*/  __disk_unblock_events (struct gendisk*,int) ; 
 struct gendisk* dev_to_disk (struct device*) ; 
 int /*<<< orphan*/  disk_block_events (struct gendisk*) ; 
 int /*<<< orphan*/  sscanf (char const*,char*,long*) ; 

__attribute__((used)) static ssize_t disk_events_poll_msecs_store(struct device *dev,
					    struct device_attribute *attr,
					    const char *buf, size_t count)
{
	struct gendisk *disk = dev_to_disk(dev);
	long intv;

	if (!count || !sscanf(buf, "%ld", &intv))
		return -EINVAL;

	if (intv < 0 && intv != -1)
		return -EINVAL;

	if (!disk->ev)
		return -ENODEV;

	disk_block_events(disk);
	disk->ev->poll_msecs = intv;
	__disk_unblock_events(disk, true);

	return count;
}