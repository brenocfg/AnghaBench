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
#define  IB_SMINFO_STATE_DISCOVERING 131 
#define  IB_SMINFO_STATE_MASTER 130 
#define  IB_SMINFO_STATE_NOTACTIVE 129 
#define  IB_SMINFO_STATE_STANDBY 128 

__attribute__((used)) static const char *sm_state_str(int state)
{
	switch (state) {
	case IB_SMINFO_STATE_DISCOVERING:
		return "Discovering";
	case IB_SMINFO_STATE_STANDBY:
		return "Standby    ";
	case IB_SMINFO_STATE_NOTACTIVE:
		return "Not Active ";
	case IB_SMINFO_STATE_MASTER:
		return "Master     ";
	}
	return "UNKNOWN    ";
}