#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rdma_cm_id {scalar_t__ context; } ;
struct rdma_cm_event {int event; int status; } ;
struct cmatest_node {int connected; } ;
struct TYPE_2__ {int /*<<< orphan*/  disconnects_left; int /*<<< orphan*/  connects_left; } ;

/* Variables and functions */
#define  RDMA_CM_EVENT_ADDR_ERROR 138 
#define  RDMA_CM_EVENT_ADDR_RESOLVED 137 
#define  RDMA_CM_EVENT_CONNECT_ERROR 136 
#define  RDMA_CM_EVENT_CONNECT_REQUEST 135 
#define  RDMA_CM_EVENT_DEVICE_REMOVAL 134 
#define  RDMA_CM_EVENT_DISCONNECTED 133 
#define  RDMA_CM_EVENT_ESTABLISHED 132 
#define  RDMA_CM_EVENT_REJECTED 131 
#define  RDMA_CM_EVENT_ROUTE_ERROR 130 
#define  RDMA_CM_EVENT_ROUTE_RESOLVED 129 
#define  RDMA_CM_EVENT_UNREACHABLE 128 
 int addr_handler (scalar_t__) ; 
 int /*<<< orphan*/  connect_error () ; 
 int connect_handler (struct rdma_cm_id*) ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 
 int /*<<< orphan*/  rdma_disconnect (struct rdma_cm_id*) ; 
 char* rdma_event_str (int) ; 
 int route_handler (scalar_t__) ; 
 TYPE_1__ test ; 

__attribute__((used)) static int cma_handler(struct rdma_cm_id *cma_id, struct rdma_cm_event *event)
{
	int ret = 0;

	switch (event->event) {
	case RDMA_CM_EVENT_ADDR_RESOLVED:
		ret = addr_handler(cma_id->context);
		break;
	case RDMA_CM_EVENT_ROUTE_RESOLVED:
		ret = route_handler(cma_id->context);
		break;
	case RDMA_CM_EVENT_CONNECT_REQUEST:
		ret = connect_handler(cma_id);
		break;
	case RDMA_CM_EVENT_ESTABLISHED:
		((struct cmatest_node *) cma_id->context)->connected = 1;
		test.connects_left--;
		test.disconnects_left++;
		break;
	case RDMA_CM_EVENT_ADDR_ERROR:
	case RDMA_CM_EVENT_ROUTE_ERROR:
	case RDMA_CM_EVENT_CONNECT_ERROR:
	case RDMA_CM_EVENT_UNREACHABLE:
	case RDMA_CM_EVENT_REJECTED:
		printf("cmatose: event: %s, error: %d\n",
		       rdma_event_str(event->event), event->status);
		connect_error();
		ret = event->status;
		break;
	case RDMA_CM_EVENT_DISCONNECTED:
		rdma_disconnect(cma_id);
		test.disconnects_left--;
		break;
	case RDMA_CM_EVENT_DEVICE_REMOVAL:
		/* Cleanup will occur after test completes. */
		break;
	default:
		break;
	}
	return ret;
}