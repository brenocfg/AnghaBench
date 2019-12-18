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

/* Variables and functions */
 int G_RAID_VOLUME_RLQ_NONE ; 
 int G_RAID_VOLUME_RLQ_R5LA ; 
 int G_RAID_VOLUME_RLQ_R5LS ; 
#define  G_RAID_VOLUME_RL_CONCAT 133 
#define  G_RAID_VOLUME_RL_RAID0 132 
#define  G_RAID_VOLUME_RL_RAID1 131 
#define  G_RAID_VOLUME_RL_RAID1E 130 
#define  G_RAID_VOLUME_RL_RAID5 129 
#define  G_RAID_VOLUME_RL_SINGLE 128 

__attribute__((used)) static int
g_raid_md_nvidia_supported(int level, int qual, int disks, int force)
{

	switch (level) {
	case G_RAID_VOLUME_RL_RAID0:
		if (disks < 1)
			return (0);
		if (!force && (disks < 2 || disks > 6))
			return (0);
		break;
	case G_RAID_VOLUME_RL_RAID1:
		if (disks < 1)
			return (0);
		if (!force && (disks != 2))
			return (0);
		break;
	case G_RAID_VOLUME_RL_RAID1E:
		if (disks < 2)
			return (0);
		if (disks % 2 != 0)
			return (0);
		if (!force && (disks < 4))
			return (0);
		break;
	case G_RAID_VOLUME_RL_SINGLE:
		if (disks != 1)
			return (0);
		break;
	case G_RAID_VOLUME_RL_CONCAT:
		if (disks < 2)
			return (0);
		break;
	case G_RAID_VOLUME_RL_RAID5:
		if (disks < 3)
			return (0);
		if (qual != G_RAID_VOLUME_RLQ_R5LA &&
		    qual != G_RAID_VOLUME_RLQ_R5LS)
			return (0);
		break;
	default:
		return (0);
	}
	if (level != G_RAID_VOLUME_RL_RAID5 && qual != G_RAID_VOLUME_RLQ_NONE)
		return (0);
	return (1);
}