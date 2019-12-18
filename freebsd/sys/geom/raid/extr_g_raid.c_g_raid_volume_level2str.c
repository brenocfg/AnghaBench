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
 int G_RAID_VOLUME_RLQ_R1EA ; 
 int G_RAID_VOLUME_RLQ_R1EO ; 
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

const char *
g_raid_volume_level2str(int level, int qual)
{

	switch (level) {
	case G_RAID_VOLUME_RL_RAID0:
		return ("RAID0");
	case G_RAID_VOLUME_RL_RAID1:
		return ("RAID1");
	case G_RAID_VOLUME_RL_RAID3:
		if (qual == G_RAID_VOLUME_RLQ_R3P0)
			return ("RAID3-P0");
		if (qual == G_RAID_VOLUME_RLQ_R3PN)
			return ("RAID3-PN");
		return ("RAID3");
	case G_RAID_VOLUME_RL_RAID4:
		if (qual == G_RAID_VOLUME_RLQ_R4P0)
			return ("RAID4-P0");
		if (qual == G_RAID_VOLUME_RLQ_R4PN)
			return ("RAID4-PN");
		return ("RAID4");
	case G_RAID_VOLUME_RL_RAID5:
		if (qual == G_RAID_VOLUME_RLQ_R5RA)
			return ("RAID5-RA");
		if (qual == G_RAID_VOLUME_RLQ_R5RS)
			return ("RAID5-RS");
		if (qual == G_RAID_VOLUME_RLQ_R5LA)
			return ("RAID5-LA");
		if (qual == G_RAID_VOLUME_RLQ_R5LS)
			return ("RAID5-LS");
		return ("RAID5");
	case G_RAID_VOLUME_RL_RAID6:
		if (qual == G_RAID_VOLUME_RLQ_R6RA)
			return ("RAID6-RA");
		if (qual == G_RAID_VOLUME_RLQ_R6RS)
			return ("RAID6-RS");
		if (qual == G_RAID_VOLUME_RLQ_R6LA)
			return ("RAID6-LA");
		if (qual == G_RAID_VOLUME_RLQ_R6LS)
			return ("RAID6-LS");
		return ("RAID6");
	case G_RAID_VOLUME_RL_RAIDMDF:
		if (qual == G_RAID_VOLUME_RLQ_RMDFRA)
			return ("RAIDMDF-RA");
		if (qual == G_RAID_VOLUME_RLQ_RMDFRS)
			return ("RAIDMDF-RS");
		if (qual == G_RAID_VOLUME_RLQ_RMDFLA)
			return ("RAIDMDF-LA");
		if (qual == G_RAID_VOLUME_RLQ_RMDFLS)
			return ("RAIDMDF-LS");
		return ("RAIDMDF");
	case G_RAID_VOLUME_RL_RAID1E:
		if (qual == G_RAID_VOLUME_RLQ_R1EA)
			return ("RAID1E-A");
		if (qual == G_RAID_VOLUME_RLQ_R1EO)
			return ("RAID1E-O");
		return ("RAID1E");
	case G_RAID_VOLUME_RL_SINGLE:
		return ("SINGLE");
	case G_RAID_VOLUME_RL_CONCAT:
		return ("CONCAT");
	case G_RAID_VOLUME_RL_RAID5E:
		if (qual == G_RAID_VOLUME_RLQ_R5ERA)
			return ("RAID5E-RA");
		if (qual == G_RAID_VOLUME_RLQ_R5ERS)
			return ("RAID5E-RS");
		if (qual == G_RAID_VOLUME_RLQ_R5ELA)
			return ("RAID5E-LA");
		if (qual == G_RAID_VOLUME_RLQ_R5ELS)
			return ("RAID5E-LS");
		return ("RAID5E");
	case G_RAID_VOLUME_RL_RAID5EE:
		if (qual == G_RAID_VOLUME_RLQ_R5EERA)
			return ("RAID5EE-RA");
		if (qual == G_RAID_VOLUME_RLQ_R5EERS)
			return ("RAID5EE-RS");
		if (qual == G_RAID_VOLUME_RLQ_R5EELA)
			return ("RAID5EE-LA");
		if (qual == G_RAID_VOLUME_RLQ_R5EELS)
			return ("RAID5EE-LS");
		return ("RAID5EE");
	case G_RAID_VOLUME_RL_RAID5R:
		if (qual == G_RAID_VOLUME_RLQ_R5RRA)
			return ("RAID5R-RA");
		if (qual == G_RAID_VOLUME_RLQ_R5RRS)
			return ("RAID5R-RS");
		if (qual == G_RAID_VOLUME_RLQ_R5RLA)
			return ("RAID5R-LA");
		if (qual == G_RAID_VOLUME_RLQ_R5RLS)
			return ("RAID5R-LS");
		return ("RAID5E");
	default:
		return ("UNKNOWN");
	}
}