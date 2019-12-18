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
#define  G_RAID_SUBDISK_S_ACTIVE 135 
#define  G_RAID_SUBDISK_S_FAILED 134 
#define  G_RAID_SUBDISK_S_NEW 133 
#define  G_RAID_SUBDISK_S_NONE 132 
#define  G_RAID_SUBDISK_S_REBUILD 131 
#define  G_RAID_SUBDISK_S_RESYNC 130 
#define  G_RAID_SUBDISK_S_STALE 129 
#define  G_RAID_SUBDISK_S_UNINITIALIZED 128 

const char *
g_raid_subdisk_state2str(int state)
{

	switch (state) {
	case G_RAID_SUBDISK_S_NONE:
		return ("NONE");
	case G_RAID_SUBDISK_S_FAILED:
		return ("FAILED");
	case G_RAID_SUBDISK_S_NEW:
		return ("NEW");
	case G_RAID_SUBDISK_S_REBUILD:
		return ("REBUILD");
	case G_RAID_SUBDISK_S_UNINITIALIZED:
		return ("UNINITIALIZED");
	case G_RAID_SUBDISK_S_STALE:
		return ("STALE");
	case G_RAID_SUBDISK_S_RESYNC:
		return ("RESYNC");
	case G_RAID_SUBDISK_S_ACTIVE:
		return ("ACTIVE");
	default:
		return ("INVALID");
	}
}