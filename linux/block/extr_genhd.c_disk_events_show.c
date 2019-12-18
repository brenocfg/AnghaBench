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
struct gendisk {int event_flags; int /*<<< orphan*/  events; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int DISK_EVENT_FLAG_UEVENT ; 
 int /*<<< orphan*/  __disk_events_show (int /*<<< orphan*/ ,char*) ; 
 struct gendisk* dev_to_disk (struct device*) ; 

__attribute__((used)) static ssize_t disk_events_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct gendisk *disk = dev_to_disk(dev);

	if (!(disk->event_flags & DISK_EVENT_FLAG_UEVENT))
		return 0;

	return __disk_events_show(disk->events, buf);
}