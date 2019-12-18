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
struct jmicron_raid_conf {scalar_t__* disks; } ;

/* Variables and functions */
 int JMICRON_MAX_DISKS ; 

__attribute__((used)) static int
jmicron_meta_total_disks(struct jmicron_raid_conf *meta)
{
	int pos;

	for (pos = 0; pos < JMICRON_MAX_DISKS; pos++) {
		if (meta->disks[pos] == 0)
			break;
	}
	return (pos);
}