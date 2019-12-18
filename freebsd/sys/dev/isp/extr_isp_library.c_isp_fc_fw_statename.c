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
#define  FW_CONFIG_WAIT 135 
#define  FW_ERROR 134 
#define  FW_LOSS_OF_SYNC 133 
#define  FW_NON_PART 132 
#define  FW_READY 131 
#define  FW_REINIT 130 
#define  FW_WAIT_LINK 129 
#define  FW_WAIT_LOGIN 128 

const char *
isp_fc_fw_statename(int state)
{
	switch (state) {
	case FW_CONFIG_WAIT:	return "Config Wait";
	case FW_WAIT_LINK:	return "Wait Link";
	case FW_WAIT_LOGIN:	return "Wait Login";
	case FW_READY:		return "Ready";
	case FW_LOSS_OF_SYNC:	return "Loss Of Sync";
	case FW_ERROR:		return "Error";
	case FW_REINIT:		return "Re-Init";
	case FW_NON_PART:	return "Nonparticipating";
	default:		return "?????";
	}
}