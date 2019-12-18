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
typedef  int uint32_t ;
struct jmicron_raid_conf {int* disks; int* spare; } ;

/* Variables and functions */
 int JMICRON_DISK_MASK ; 
 int JMICRON_MAX_DISKS ; 
 int JMICRON_MAX_SPARE ; 

__attribute__((used)) static int
jmicron_meta_find_disk(struct jmicron_raid_conf *meta, uint32_t id)
{
	int pos;

	id &= JMICRON_DISK_MASK;
	for (pos = 0; pos < JMICRON_MAX_DISKS; pos++) {
		if ((meta->disks[pos] & JMICRON_DISK_MASK) == id)
			return (pos);
	}
	for (pos = 0; pos < JMICRON_MAX_SPARE; pos++) {
		if ((meta->spare[pos] & JMICRON_DISK_MASK) == id)
			return (-3);
	}
	return (-1);
}