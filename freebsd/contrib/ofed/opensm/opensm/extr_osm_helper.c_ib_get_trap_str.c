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
typedef  int /*<<< orphan*/  ib_net16_t ;

/* Variables and functions */
#define  SM_BAD_MKEY_TRAP 143 
#define  SM_BAD_PKEY_TRAP 142 
#define  SM_BAD_QKEY_TRAP 141 
#define  SM_BAD_SWITCH_PKEY_TRAP 140 
#define  SM_BUFFER_OVERRUN_THRESHOLD_TRAP 139 
#define  SM_GID_IN_SERVICE_TRAP 138 
#define  SM_GID_OUT_OF_SERVICE_TRAP 137 
#define  SM_LINK_INTEGRITY_THRESHOLD_TRAP 136 
#define  SM_LINK_STATE_CHANGED_TRAP 135 
#define  SM_LOCAL_CHANGES_TRAP 134 
#define  SM_MGID_CREATED_TRAP 133 
#define  SM_MGID_DESTROYED_TRAP 132 
#define  SM_REPATH_TRAP 131 
#define  SM_SYS_IMG_GUID_CHANGED_TRAP 130 
#define  SM_UNPATH_TRAP 129 
#define  SM_WATCHDOG_TIMER_EXPIRED_TRAP 128 
 int cl_ntoh16 (int /*<<< orphan*/ ) ; 

const char *ib_get_trap_str(ib_net16_t trap_num)
{
	switch (cl_ntoh16(trap_num)) {
	case SM_GID_IN_SERVICE_TRAP:	/* 64 */
		return "GID in service";
	case SM_GID_OUT_OF_SERVICE_TRAP: /* 65 */
		return "GID out of service";
	case SM_MGID_CREATED_TRAP:	/* 66 */
		return "New mcast group created";
	case SM_MGID_DESTROYED_TRAP:	/* 67 */
		return "Mcast group deleted";
	case SM_UNPATH_TRAP:		/* 68 */
		return "UnPath, Path no longer valid";
	case SM_REPATH_TRAP:		/* 69 */
		return "RePath, Path recomputed";
	case SM_LINK_STATE_CHANGED_TRAP: /* 128 */
		return "Link state change";
	case SM_LINK_INTEGRITY_THRESHOLD_TRAP: /* 129 */
		return "Local Link integrity threshold reached";
	case SM_BUFFER_OVERRUN_THRESHOLD_TRAP: /* 130 */
		return "Excessive Buffer Overrun Threshold reached";
	case SM_WATCHDOG_TIMER_EXPIRED_TRAP:   /* 131 */
		return "Flow Control Update watchdog timer expired";
	case SM_LOCAL_CHANGES_TRAP:	/* 144 */
		return
		    "CapabilityMask, NodeDescription, Link [Width|Speed] Enabled, SM priority changed";
	case SM_SYS_IMG_GUID_CHANGED_TRAP: /* 145 */
		return "System Image GUID changed";
	case SM_BAD_MKEY_TRAP:		/* 256 */
		return "Bad M_Key";
	case SM_BAD_PKEY_TRAP:		/* 257 */
		return "Bad P_Key";
	case SM_BAD_QKEY_TRAP:		/* 258 */
		return "Bad Q_Key";
	case SM_BAD_SWITCH_PKEY_TRAP:	/* 259 */
		return "Bad P_Key (switch external port)";
	default:
		break;
	}
	return "Unknown";
}