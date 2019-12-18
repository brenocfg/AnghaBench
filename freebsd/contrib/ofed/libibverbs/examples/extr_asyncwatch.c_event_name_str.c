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
typedef  enum ibv_event_type { ____Placeholder_ibv_event_type } ibv_event_type ;

/* Variables and functions */
#define  IBV_EVENT_CLIENT_REREGISTER 146 
#define  IBV_EVENT_COMM_EST 145 
#define  IBV_EVENT_CQ_ERR 144 
#define  IBV_EVENT_DEVICE_FATAL 143 
#define  IBV_EVENT_GID_CHANGE 142 
#define  IBV_EVENT_LID_CHANGE 141 
#define  IBV_EVENT_PATH_MIG 140 
#define  IBV_EVENT_PATH_MIG_ERR 139 
#define  IBV_EVENT_PKEY_CHANGE 138 
#define  IBV_EVENT_PORT_ACTIVE 137 
#define  IBV_EVENT_PORT_ERR 136 
#define  IBV_EVENT_QP_ACCESS_ERR 135 
#define  IBV_EVENT_QP_FATAL 134 
#define  IBV_EVENT_QP_LAST_WQE_REACHED 133 
#define  IBV_EVENT_QP_REQ_ERR 132 
#define  IBV_EVENT_SM_CHANGE 131 
#define  IBV_EVENT_SQ_DRAINED 130 
#define  IBV_EVENT_SRQ_ERR 129 
#define  IBV_EVENT_SRQ_LIMIT_REACHED 128 

__attribute__((used)) static const char *event_name_str(enum ibv_event_type event_type)
{
	switch (event_type) {
	case IBV_EVENT_DEVICE_FATAL:
		return "IBV_EVENT_DEVICE_FATAL";
	case IBV_EVENT_PORT_ACTIVE:
		return "IBV_EVENT_PORT_ACTIVE";
	case IBV_EVENT_PORT_ERR:
		return "IBV_EVENT_PORT_ERR";
	case IBV_EVENT_LID_CHANGE:
		return "IBV_EVENT_LID_CHANGE";
	case IBV_EVENT_PKEY_CHANGE:
		return "IBV_EVENT_PKEY_CHANGE";
	case IBV_EVENT_SM_CHANGE:
		return "IBV_EVENT_SM_CHANGE";
	case IBV_EVENT_CLIENT_REREGISTER:
		return "IBV_EVENT_CLIENT_REREGISTER";
	case IBV_EVENT_GID_CHANGE:
		return "IBV_EVENT_GID_CHANGE";

	case IBV_EVENT_CQ_ERR:
	case IBV_EVENT_QP_FATAL:
	case IBV_EVENT_QP_REQ_ERR:
	case IBV_EVENT_QP_ACCESS_ERR:
	case IBV_EVENT_COMM_EST:
	case IBV_EVENT_SQ_DRAINED:
	case IBV_EVENT_PATH_MIG:
	case IBV_EVENT_PATH_MIG_ERR:
	case IBV_EVENT_SRQ_ERR:
	case IBV_EVENT_SRQ_LIMIT_REACHED:
	case IBV_EVENT_QP_LAST_WQE_REACHED:
	default:
		return "unexpected";
	}
}