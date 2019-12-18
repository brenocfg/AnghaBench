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
struct rdma_cm_id {struct node* context; } ;
struct rdma_cm_event {int event; int status; } ;
struct node {int error; int /*<<< orphan*/  id; int /*<<< orphan*/  retries; } ;
struct list_head {struct rdma_cm_id* id; } ;
struct TYPE_2__ {int /*<<< orphan*/  ai_dst_addr; int /*<<< orphan*/  ai_src_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST (struct list_head*) ; 
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
 int /*<<< orphan*/  addr_handler (struct node*) ; 
 int /*<<< orphan*/  conn_handler (struct node*) ; 
 int /*<<< orphan*/  disc_handler (struct node*) ; 
 int /*<<< orphan*/  disc_work ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 struct list_head* malloc (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_1__* rai ; 
 int /*<<< orphan*/  rdma_ack_cm_event (struct rdma_cm_event*) ; 
 int /*<<< orphan*/  rdma_destroy_id (struct rdma_cm_id*) ; 
 int /*<<< orphan*/  rdma_disconnect (struct rdma_cm_id*) ; 
 char* rdma_event_str (int) ; 
 int /*<<< orphan*/  rdma_reject (struct rdma_cm_id*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_resolve_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_resolve_route (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  req_work ; 
 int /*<<< orphan*/  route_handler (struct node*) ; 
 int /*<<< orphan*/  timeout ; 

__attribute__((used)) static void cma_handler(struct rdma_cm_id *id, struct rdma_cm_event *event)
{
	struct node *n = id->context;
	struct list_head *request;

	switch (event->event) {
	case RDMA_CM_EVENT_ADDR_RESOLVED:
		addr_handler(n);
		break;
	case RDMA_CM_EVENT_ROUTE_RESOLVED:
		route_handler(n);
		break;
	case RDMA_CM_EVENT_CONNECT_REQUEST:
		request = malloc(sizeof *request);
		if (!request) {
			perror("out of memory accepting connect request");
			rdma_reject(id, NULL, 0);
			rdma_destroy_id(id);
		} else {
			INIT_LIST(request);
			request->id = id;
			list_add_tail(&req_work, request);
		}
		break;
	case RDMA_CM_EVENT_ESTABLISHED:
		if (n)
			conn_handler(n);
		break;
	case RDMA_CM_EVENT_ADDR_ERROR:
		if (n->retries--) {
			if (!rdma_resolve_addr(n->id, rai->ai_src_addr,
					       rai->ai_dst_addr, timeout))
				break;
		}
		printf("RDMA_CM_EVENT_ADDR_ERROR, error: %d\n", event->status);
		addr_handler(n);
		n->error = 1;
		break;
	case RDMA_CM_EVENT_ROUTE_ERROR:
		if (n->retries--) {
			if (!rdma_resolve_route(n->id, timeout))
				break;
		}
		printf("RDMA_CM_EVENT_ROUTE_ERROR, error: %d\n", event->status);
		route_handler(n);
		n->error = 1;
		break;
	case RDMA_CM_EVENT_CONNECT_ERROR:
	case RDMA_CM_EVENT_UNREACHABLE:
	case RDMA_CM_EVENT_REJECTED:
		printf("event: %s, error: %d\n",
		       rdma_event_str(event->event), event->status);
		conn_handler(n);
		n->error = 1;
		break;
	case RDMA_CM_EVENT_DISCONNECTED:
		if (!n) {
			request = malloc(sizeof *request);
			if (!request) {
				perror("out of memory queueing disconnect request, handling synchronously");
				rdma_disconnect(id);
				rdma_destroy_id(id);
			} else {
				INIT_LIST(request);
				request->id = id;
				list_add_tail(&disc_work, request);
			}
		} else
			disc_handler(n);
		break;
	case RDMA_CM_EVENT_DEVICE_REMOVAL:
		/* Cleanup will occur after test completes. */
		break;
	default:
		break;
	}
	rdma_ack_cm_event(event);
}