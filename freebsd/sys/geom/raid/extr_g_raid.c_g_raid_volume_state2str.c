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
#define  G_RAID_VOLUME_S_BROKEN 134 
#define  G_RAID_VOLUME_S_DEGRADED 133 
#define  G_RAID_VOLUME_S_OPTIMAL 132 
#define  G_RAID_VOLUME_S_STARTING 131 
#define  G_RAID_VOLUME_S_STOPPED 130 
#define  G_RAID_VOLUME_S_SUBOPTIMAL 129 
#define  G_RAID_VOLUME_S_UNSUPPORTED 128 

const char *
g_raid_volume_state2str(int state)
{

	switch (state) {
	case G_RAID_VOLUME_S_STARTING:
		return ("STARTING");
	case G_RAID_VOLUME_S_BROKEN:
		return ("BROKEN");
	case G_RAID_VOLUME_S_DEGRADED:
		return ("DEGRADED");
	case G_RAID_VOLUME_S_SUBOPTIMAL:
		return ("SUBOPTIMAL");
	case G_RAID_VOLUME_S_OPTIMAL:
		return ("OPTIMAL");
	case G_RAID_VOLUME_S_UNSUPPORTED:
		return ("UNSUPPORTED");
	case G_RAID_VOLUME_S_STOPPED:
		return ("STOPPED");
	default:
		return ("INVALID");
	}
}