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
typedef  scalar_t__ uint64_t ;
struct promise_raid_conf {int total_disks; TYPE_1__* disks; } ;
struct TYPE_2__ {scalar_t__ id; } ;

/* Variables and functions */

__attribute__((used)) static int
promise_meta_find_disk(struct promise_raid_conf *meta, uint64_t id)
{
	int pos;

	for (pos = 0; pos < meta->total_disks; pos++) {
		if (meta->disks[pos].id == id)
			return (pos);
	}
	return (-1);
}