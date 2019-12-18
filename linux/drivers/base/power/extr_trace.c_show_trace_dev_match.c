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
struct list_head {struct list_head* prev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVHASH ; 
 int /*<<< orphan*/  DEVSEED ; 
 unsigned int FILEHASH ; 
 unsigned int USERHASH ; 
 char* dev_driver_string (struct device*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  device_pm_lock () ; 
 int /*<<< orphan*/  device_pm_unlock () ; 
 struct list_head dpm_list ; 
 unsigned int hash_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int hash_value_early_read ; 
 int snprintf (char*,size_t,char*,char*) ; 
 struct device* to_device (struct list_head*) ; 

int show_trace_dev_match(char *buf, size_t size)
{
	unsigned int value = hash_value_early_read / (USERHASH * FILEHASH);
	int ret = 0;
	struct list_head *entry;

	/*
	 * It's possible that multiple devices will match the hash and we can't
	 * tell which is the culprit, so it's best to output them all.
	 */
	device_pm_lock();
	entry = dpm_list.prev;
	while (size && entry != &dpm_list) {
		struct device *dev = to_device(entry);
		unsigned int hash = hash_string(DEVSEED, dev_name(dev),
						DEVHASH);
		if (hash == value) {
			int len = snprintf(buf, size, "%s\n",
					    dev_driver_string(dev));
			if (len > size)
				len = size;
			buf += len;
			ret += len;
			size -= len;
		}
		entry = entry->prev;
	}
	device_pm_unlock();
	return ret;
}