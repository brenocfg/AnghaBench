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
struct rdma_cm_id {struct iser_conn* context; } ;
struct rdma_cm_event {int event; int /*<<< orphan*/  status; } ;
struct iser_conn {int /*<<< orphan*/  state_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISER_ERR (char*,int) ; 
 int /*<<< orphan*/  ISER_INFO (char*,int,int /*<<< orphan*/ ,struct iser_conn*,struct rdma_cm_id*) ; 
#define  RDMA_CM_EVENT_ADDR_CHANGE 138 
#define  RDMA_CM_EVENT_ADDR_ERROR 137 
#define  RDMA_CM_EVENT_ADDR_RESOLVED 136 
#define  RDMA_CM_EVENT_CONNECT_ERROR 135 
#define  RDMA_CM_EVENT_DISCONNECTED 134 
#define  RDMA_CM_EVENT_ESTABLISHED 133 
#define  RDMA_CM_EVENT_REJECTED 132 
#define  RDMA_CM_EVENT_ROUTE_ERROR 131 
#define  RDMA_CM_EVENT_ROUTE_RESOLVED 130 
#define  RDMA_CM_EVENT_TIMEWAIT_EXIT 129 
#define  RDMA_CM_EVENT_UNREACHABLE 128 
 int /*<<< orphan*/  iser_addr_handler (struct rdma_cm_id*) ; 
 int /*<<< orphan*/  iser_cleanup_handler (struct rdma_cm_id*,int) ; 
 int /*<<< orphan*/  iser_connect_error (struct rdma_cm_id*) ; 
 int /*<<< orphan*/  iser_connected_handler (struct rdma_cm_id*) ; 
 int /*<<< orphan*/  iser_route_handler (struct rdma_cm_id*) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

int
iser_cma_handler(struct rdma_cm_id *cma_id, struct rdma_cm_event *event)
{
	struct iser_conn *iser_conn;
	int ret = 0;

	iser_conn = cma_id->context;
	ISER_INFO("event %d status %d conn %p id %p",
		  event->event, event->status, cma_id->context, cma_id);

	sx_xlock(&iser_conn->state_mutex);
	switch (event->event) {
	case RDMA_CM_EVENT_ADDR_RESOLVED:
		iser_addr_handler(cma_id);
		break;
	case RDMA_CM_EVENT_ROUTE_RESOLVED:
		iser_route_handler(cma_id);
		break;
	case RDMA_CM_EVENT_ESTABLISHED:
		iser_connected_handler(cma_id);
		break;
	case RDMA_CM_EVENT_ADDR_ERROR:
	case RDMA_CM_EVENT_ROUTE_ERROR:
	case RDMA_CM_EVENT_CONNECT_ERROR:
	case RDMA_CM_EVENT_UNREACHABLE:
	case RDMA_CM_EVENT_REJECTED:
		iser_connect_error(cma_id);
		break;
	case RDMA_CM_EVENT_DISCONNECTED:
	case RDMA_CM_EVENT_ADDR_CHANGE:
	case RDMA_CM_EVENT_TIMEWAIT_EXIT:
		iser_cleanup_handler(cma_id, false);
		break;
	default:
		ISER_ERR("Unexpected RDMA CM event (%d)", event->event);
		break;
	}
	sx_xunlock(&iser_conn->state_mutex);

	return (ret);
}