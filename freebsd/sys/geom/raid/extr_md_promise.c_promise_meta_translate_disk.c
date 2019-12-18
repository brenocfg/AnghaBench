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
struct g_raid_volume {scalar_t__ v_raid_level; int v_disks_count; } ;

/* Variables and functions */
 scalar_t__ G_RAID_VOLUME_RL_RAID1E ; 

__attribute__((used)) static int
promise_meta_translate_disk(struct g_raid_volume *vol, int md_disk_pos)
{
	int disk_pos, width;

	if (md_disk_pos >= 0 && vol->v_raid_level == G_RAID_VOLUME_RL_RAID1E) {
		width = vol->v_disks_count / 2;
		disk_pos = (md_disk_pos / width) +
		    (md_disk_pos % width) * width;
	} else
		disk_pos = md_disk_pos;
	return (disk_pos);
}