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
typedef  enum skd_drvr_state { ____Placeholder_skd_drvr_state } skd_drvr_state ;

/* Variables and functions */
#define  SKD_DRVR_STATE_BUSY 144 
#define  SKD_DRVR_STATE_BUSY_ERASE 143 
#define  SKD_DRVR_STATE_BUSY_IMMINENT 142 
#define  SKD_DRVR_STATE_BUSY_SANITIZE 141 
#define  SKD_DRVR_STATE_DISAPPEARED 140 
#define  SKD_DRVR_STATE_FAULT 139 
#define  SKD_DRVR_STATE_IDLE 138 
#define  SKD_DRVR_STATE_LOAD 137 
#define  SKD_DRVR_STATE_ONLINE 136 
#define  SKD_DRVR_STATE_PAUSED 135 
#define  SKD_DRVR_STATE_PAUSING 134 
#define  SKD_DRVR_STATE_RESTARTING 133 
#define  SKD_DRVR_STATE_RESUMING 132 
#define  SKD_DRVR_STATE_STARTING 131 
#define  SKD_DRVR_STATE_STOPPING 130 
#define  SKD_DRVR_STATE_SYNCING 129 
#define  SKD_DRVR_STATE_WAIT_BOOT 128 

const char *skd_skdev_state_to_str(enum skd_drvr_state state)
{
	switch (state) {
	case SKD_DRVR_STATE_LOAD:
		return "LOAD";
	case SKD_DRVR_STATE_IDLE:
		return "IDLE";
	case SKD_DRVR_STATE_BUSY:
		return "BUSY";
	case SKD_DRVR_STATE_STARTING:
		return "STARTING";
	case SKD_DRVR_STATE_ONLINE:
		return "ONLINE";
	case SKD_DRVR_STATE_PAUSING:
		return "PAUSING";
	case SKD_DRVR_STATE_PAUSED:
		return "PAUSED";
	case SKD_DRVR_STATE_RESTARTING:
		return "RESTARTING";
	case SKD_DRVR_STATE_RESUMING:
		return "RESUMING";
	case SKD_DRVR_STATE_STOPPING:
		return "STOPPING";
	case SKD_DRVR_STATE_SYNCING:
		return "SYNCING";
	case SKD_DRVR_STATE_FAULT:
		return "FAULT";
	case SKD_DRVR_STATE_DISAPPEARED:
		return "DISAPPEARED";
	case SKD_DRVR_STATE_BUSY_ERASE:
		return "BUSY_ERASE";
	case SKD_DRVR_STATE_BUSY_SANITIZE:
		return "BUSY_SANITIZE";
	case SKD_DRVR_STATE_BUSY_IMMINENT:
		return "BUSY_IMMINENT";
	case SKD_DRVR_STATE_WAIT_BOOT:
		return "WAIT_BOOT";

	default:
		return "???";
	}
}