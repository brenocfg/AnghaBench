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
#define  G_RAID3_DISK_STATE_ACTIVE 134 
#define  G_RAID3_DISK_STATE_DISCONNECTED 133 
#define  G_RAID3_DISK_STATE_NEW 132 
#define  G_RAID3_DISK_STATE_NODISK 131 
#define  G_RAID3_DISK_STATE_NONE 130 
#define  G_RAID3_DISK_STATE_STALE 129 
#define  G_RAID3_DISK_STATE_SYNCHRONIZING 128 

__attribute__((used)) static const char *
g_raid3_disk_state2str(int state)
{

	switch (state) {
	case G_RAID3_DISK_STATE_NODISK:
		return ("NODISK");
	case G_RAID3_DISK_STATE_NONE:
		return ("NONE");
	case G_RAID3_DISK_STATE_NEW:
		return ("NEW");
	case G_RAID3_DISK_STATE_ACTIVE:
		return ("ACTIVE");
	case G_RAID3_DISK_STATE_STALE:
		return ("STALE");
	case G_RAID3_DISK_STATE_SYNCHRONIZING:
		return ("SYNCHRONIZING");
	case G_RAID3_DISK_STATE_DISCONNECTED:
		return ("DISCONNECTED");
	default:
		return ("INVALID");
	}
}