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
typedef  enum rdma_cm_event_type { ____Placeholder_rdma_cm_event_type } rdma_cm_event_type ;

/* Variables and functions */
#define  RDMA_CM_EVENT_ADDR_CHANGE 143 
#define  RDMA_CM_EVENT_ADDR_ERROR 142 
#define  RDMA_CM_EVENT_ADDR_RESOLVED 141 
#define  RDMA_CM_EVENT_CONNECT_ERROR 140 
#define  RDMA_CM_EVENT_CONNECT_REQUEST 139 
#define  RDMA_CM_EVENT_CONNECT_RESPONSE 138 
#define  RDMA_CM_EVENT_DEVICE_REMOVAL 137 
#define  RDMA_CM_EVENT_DISCONNECTED 136 
#define  RDMA_CM_EVENT_ESTABLISHED 135 
#define  RDMA_CM_EVENT_MULTICAST_ERROR 134 
#define  RDMA_CM_EVENT_MULTICAST_JOIN 133 
#define  RDMA_CM_EVENT_REJECTED 132 
#define  RDMA_CM_EVENT_ROUTE_ERROR 131 
#define  RDMA_CM_EVENT_ROUTE_RESOLVED 130 
#define  RDMA_CM_EVENT_TIMEWAIT_EXIT 129 
#define  RDMA_CM_EVENT_UNREACHABLE 128 

const char *rdma_event_str(enum rdma_cm_event_type event)
{
	switch (event) {
	case RDMA_CM_EVENT_ADDR_RESOLVED:
		return "RDMA_CM_EVENT_ADDR_RESOLVED";
	case RDMA_CM_EVENT_ADDR_ERROR:
		return "RDMA_CM_EVENT_ADDR_ERROR";
	case RDMA_CM_EVENT_ROUTE_RESOLVED:
		return "RDMA_CM_EVENT_ROUTE_RESOLVED";
	case RDMA_CM_EVENT_ROUTE_ERROR:
		return "RDMA_CM_EVENT_ROUTE_ERROR";
	case RDMA_CM_EVENT_CONNECT_REQUEST:
		return "RDMA_CM_EVENT_CONNECT_REQUEST";
	case RDMA_CM_EVENT_CONNECT_RESPONSE:
		return "RDMA_CM_EVENT_CONNECT_RESPONSE";
	case RDMA_CM_EVENT_CONNECT_ERROR:
		return "RDMA_CM_EVENT_CONNECT_ERROR";
	case RDMA_CM_EVENT_UNREACHABLE:
		return "RDMA_CM_EVENT_UNREACHABLE";
	case RDMA_CM_EVENT_REJECTED:
		return "RDMA_CM_EVENT_REJECTED";
	case RDMA_CM_EVENT_ESTABLISHED:
		return "RDMA_CM_EVENT_ESTABLISHED";
	case RDMA_CM_EVENT_DISCONNECTED:
		return "RDMA_CM_EVENT_DISCONNECTED";
	case RDMA_CM_EVENT_DEVICE_REMOVAL:
		return "RDMA_CM_EVENT_DEVICE_REMOVAL";
	case RDMA_CM_EVENT_MULTICAST_JOIN:
		return "RDMA_CM_EVENT_MULTICAST_JOIN";
	case RDMA_CM_EVENT_MULTICAST_ERROR:
		return "RDMA_CM_EVENT_MULTICAST_ERROR";
	case RDMA_CM_EVENT_ADDR_CHANGE:
		return "RDMA_CM_EVENT_ADDR_CHANGE";
	case RDMA_CM_EVENT_TIMEWAIT_EXIT:
		return "RDMA_CM_EVENT_TIMEWAIT_EXIT";
	default:
		return "UNKNOWN EVENT";
	}
}