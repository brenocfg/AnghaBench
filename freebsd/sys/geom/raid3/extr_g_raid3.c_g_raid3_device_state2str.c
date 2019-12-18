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
#define  G_RAID3_DEVICE_STATE_COMPLETE 130 
#define  G_RAID3_DEVICE_STATE_DEGRADED 129 
#define  G_RAID3_DEVICE_STATE_STARTING 128 

__attribute__((used)) static const char *
g_raid3_device_state2str(int state)
{

	switch (state) {
	case G_RAID3_DEVICE_STATE_STARTING:
		return ("STARTING");
	case G_RAID3_DEVICE_STATE_DEGRADED:
		return ("DEGRADED");
	case G_RAID3_DEVICE_STATE_COMPLETE:
		return ("COMPLETE");
	default:
		return ("INVALID");
	}
}