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
 int DDF_MAX_DISKS_HARD ; 
 int G_RAID_VOLUME_RLQ_NONE ; 
 int G_RAID_VOLUME_RLQ_R1EA ; 
 int G_RAID_VOLUME_RLQ_R1EO ; 
 int G_RAID_VOLUME_RLQ_R1MM ; 
 int G_RAID_VOLUME_RLQ_R1SM ; 
 int G_RAID_VOLUME_RLQ_R3P0 ; 
 int G_RAID_VOLUME_RLQ_R3PN ; 
 int G_RAID_VOLUME_RLQ_R4P0 ; 
 int G_RAID_VOLUME_RLQ_R4PN ; 
 int G_RAID_VOLUME_RLQ_R5EELA ; 
 int G_RAID_VOLUME_RLQ_R5EELS ; 
 int G_RAID_VOLUME_RLQ_R5EERA ; 
 int G_RAID_VOLUME_RLQ_R5EERS ; 
 int G_RAID_VOLUME_RLQ_R5ELA ; 
 int G_RAID_VOLUME_RLQ_R5ELS ; 
 int G_RAID_VOLUME_RLQ_R5ERA ; 
 int G_RAID_VOLUME_RLQ_R5ERS ; 
 int G_RAID_VOLUME_RLQ_R5LA ; 
 int G_RAID_VOLUME_RLQ_R5LS ; 
 int G_RAID_VOLUME_RLQ_R5RA ; 
 int G_RAID_VOLUME_RLQ_R5RLA ; 
 int G_RAID_VOLUME_RLQ_R5RLS ; 
 int G_RAID_VOLUME_RLQ_R5RRA ; 
 int G_RAID_VOLUME_RLQ_R5RRS ; 
 int G_RAID_VOLUME_RLQ_R5RS ; 
 int G_RAID_VOLUME_RLQ_R6LA ; 
 int G_RAID_VOLUME_RLQ_R6LS ; 
 int G_RAID_VOLUME_RLQ_R6RA ; 
 int G_RAID_VOLUME_RLQ_R6RS ; 
 int G_RAID_VOLUME_RLQ_RMDFLA ; 
 int G_RAID_VOLUME_RLQ_RMDFLS ; 
 int G_RAID_VOLUME_RLQ_RMDFRA ; 
 int G_RAID_VOLUME_RLQ_RMDFRS ; 
#define  G_RAID_VOLUME_RL_CONCAT 140 
#define  G_RAID_VOLUME_RL_RAID0 139 
#define  G_RAID_VOLUME_RL_RAID1 138 
#define  G_RAID_VOLUME_RL_RAID1E 137 
#define  G_RAID_VOLUME_RL_RAID3 136 
#define  G_RAID_VOLUME_RL_RAID4 135 
#define  G_RAID_VOLUME_RL_RAID5 134 
#define  G_RAID_VOLUME_RL_RAID5E 133 
#define  G_RAID_VOLUME_RL_RAID5EE 132 
#define  G_RAID_VOLUME_RL_RAID5R 131 
#define  G_RAID_VOLUME_RL_RAID6 130 
#define  G_RAID_VOLUME_RL_RAIDMDF 129 
#define  G_RAID_VOLUME_RL_SINGLE 128 

__attribute__((used)) static int
g_raid_md_ddf_supported(int level, int qual, int disks, int force)
{

	if (disks > DDF_MAX_DISKS_HARD)
		return (0);
	switch (level) {
	case G_RAID_VOLUME_RL_RAID0:
		if (qual != G_RAID_VOLUME_RLQ_NONE)
			return (0);
		if (disks < 1)
			return (0);
		if (!force && disks < 2)
			return (0);
		break;
	case G_RAID_VOLUME_RL_RAID1:
		if (disks < 1)
			return (0);
		if (qual == G_RAID_VOLUME_RLQ_R1SM) {
			if (!force && disks != 2)
				return (0);
		} else if (qual == G_RAID_VOLUME_RLQ_R1MM) {
			if (!force && disks != 3)
				return (0);
		} else 
			return (0);
		break;
	case G_RAID_VOLUME_RL_RAID3:
		if (qual != G_RAID_VOLUME_RLQ_R3P0 &&
		    qual != G_RAID_VOLUME_RLQ_R3PN)
			return (0);
		if (disks < 3)
			return (0);
		break;
	case G_RAID_VOLUME_RL_RAID4:
		if (qual != G_RAID_VOLUME_RLQ_R4P0 &&
		    qual != G_RAID_VOLUME_RLQ_R4PN)
			return (0);
		if (disks < 3)
			return (0);
		break;
	case G_RAID_VOLUME_RL_RAID5:
		if (qual != G_RAID_VOLUME_RLQ_R5RA &&
		    qual != G_RAID_VOLUME_RLQ_R5RS &&
		    qual != G_RAID_VOLUME_RLQ_R5LA &&
		    qual != G_RAID_VOLUME_RLQ_R5LS)
			return (0);
		if (disks < 3)
			return (0);
		break;
	case G_RAID_VOLUME_RL_RAID6:
		if (qual != G_RAID_VOLUME_RLQ_R6RA &&
		    qual != G_RAID_VOLUME_RLQ_R6RS &&
		    qual != G_RAID_VOLUME_RLQ_R6LA &&
		    qual != G_RAID_VOLUME_RLQ_R6LS)
			return (0);
		if (disks < 4)
			return (0);
		break;
	case G_RAID_VOLUME_RL_RAIDMDF:
		if (qual != G_RAID_VOLUME_RLQ_RMDFRA &&
		    qual != G_RAID_VOLUME_RLQ_RMDFRS &&
		    qual != G_RAID_VOLUME_RLQ_RMDFLA &&
		    qual != G_RAID_VOLUME_RLQ_RMDFLS)
			return (0);
		if (disks < 4)
			return (0);
		break;
	case G_RAID_VOLUME_RL_RAID1E:
		if (qual != G_RAID_VOLUME_RLQ_R1EA &&
		    qual != G_RAID_VOLUME_RLQ_R1EO)
			return (0);
		if (disks < 3)
			return (0);
		break;
	case G_RAID_VOLUME_RL_SINGLE:
		if (qual != G_RAID_VOLUME_RLQ_NONE)
			return (0);
		if (disks != 1)
			return (0);
		break;
	case G_RAID_VOLUME_RL_CONCAT:
		if (qual != G_RAID_VOLUME_RLQ_NONE)
			return (0);
		if (disks < 2)
			return (0);
		break;
	case G_RAID_VOLUME_RL_RAID5E:
		if (qual != G_RAID_VOLUME_RLQ_R5ERA &&
		    qual != G_RAID_VOLUME_RLQ_R5ERS &&
		    qual != G_RAID_VOLUME_RLQ_R5ELA &&
		    qual != G_RAID_VOLUME_RLQ_R5ELS)
			return (0);
		if (disks < 4)
			return (0);
		break;
	case G_RAID_VOLUME_RL_RAID5EE:
		if (qual != G_RAID_VOLUME_RLQ_R5EERA &&
		    qual != G_RAID_VOLUME_RLQ_R5EERS &&
		    qual != G_RAID_VOLUME_RLQ_R5EELA &&
		    qual != G_RAID_VOLUME_RLQ_R5EELS)
			return (0);
		if (disks < 4)
			return (0);
		break;
	case G_RAID_VOLUME_RL_RAID5R:
		if (qual != G_RAID_VOLUME_RLQ_R5RRA &&
		    qual != G_RAID_VOLUME_RLQ_R5RRS &&
		    qual != G_RAID_VOLUME_RLQ_R5RLA &&
		    qual != G_RAID_VOLUME_RLQ_R5RLS)
			return (0);
		if (disks < 3)
			return (0);
		break;
	default:
		return (0);
	}
	return (1);
}