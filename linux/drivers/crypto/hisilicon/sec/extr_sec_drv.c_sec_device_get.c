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
struct sec_dev_info {int queues_in_use; } ;

/* Variables and functions */
 int SEC_MAX_DEVICES ; 
 int SEC_Q_NUM ; 
 struct sec_dev_info** sec_devices ; 

__attribute__((used)) static struct sec_dev_info *sec_device_get(void)
{
	struct sec_dev_info *sec_dev = NULL;
	struct sec_dev_info *this_sec_dev;
	int least_busy_n = SEC_Q_NUM + 1;
	int i;

	/* Find which one is least busy and use that first */
	for (i = 0; i < SEC_MAX_DEVICES; i++) {
		this_sec_dev = sec_devices[i];
		if (this_sec_dev &&
		    this_sec_dev->queues_in_use < least_busy_n) {
			least_busy_n = this_sec_dev->queues_in_use;
			sec_dev = this_sec_dev;
		}
	}

	return sec_dev;
}