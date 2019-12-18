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
struct memory_block {int online_type; int /*<<< orphan*/  dev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
#define  MMOP_OFFLINE 131 
#define  MMOP_ONLINE_KEEP 130 
#define  MMOP_ONLINE_KERNEL 129 
#define  MMOP_ONLINE_MOVABLE 128 
 int device_offline (int /*<<< orphan*/ *) ; 
 int device_online (int /*<<< orphan*/ *) ; 
 int lock_device_hotplug_sysfs () ; 
 scalar_t__ sysfs_streq (char const*,char*) ; 
 struct memory_block* to_memory_block (struct device*) ; 
 int /*<<< orphan*/  unlock_device_hotplug () ; 

__attribute__((used)) static ssize_t state_store(struct device *dev, struct device_attribute *attr,
			   const char *buf, size_t count)
{
	struct memory_block *mem = to_memory_block(dev);
	int ret, online_type;

	ret = lock_device_hotplug_sysfs();
	if (ret)
		return ret;

	if (sysfs_streq(buf, "online_kernel"))
		online_type = MMOP_ONLINE_KERNEL;
	else if (sysfs_streq(buf, "online_movable"))
		online_type = MMOP_ONLINE_MOVABLE;
	else if (sysfs_streq(buf, "online"))
		online_type = MMOP_ONLINE_KEEP;
	else if (sysfs_streq(buf, "offline"))
		online_type = MMOP_OFFLINE;
	else {
		ret = -EINVAL;
		goto err;
	}

	switch (online_type) {
	case MMOP_ONLINE_KERNEL:
	case MMOP_ONLINE_MOVABLE:
	case MMOP_ONLINE_KEEP:
		/* mem->online_type is protected by device_hotplug_lock */
		mem->online_type = online_type;
		ret = device_online(&mem->dev);
		break;
	case MMOP_OFFLINE:
		ret = device_offline(&mem->dev);
		break;
	default:
		ret = -EINVAL; /* should never happen */
	}

err:
	unlock_device_hotplug();

	if (ret < 0)
		return ret;
	if (ret)
		return -EINVAL;

	return count;
}