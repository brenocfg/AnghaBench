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
struct rdma_cm_event {int event; int status; } ;
struct TYPE_2__ {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
#define  RDMA_CM_EVENT_ADDR_CHANGE 129 
#define  RDMA_CM_EVENT_MULTICAST_ERROR 128 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 
 int /*<<< orphan*/  rdma_ack_cm_event (struct rdma_cm_event*) ; 
 char* rdma_event_str (int) ; 
 int rdma_get_cm_event (int /*<<< orphan*/ ,struct rdma_cm_event**) ; 
 TYPE_1__ test ; 

__attribute__((used)) static void *cma_thread(void *arg)
{
	struct rdma_cm_event *event;
	int ret;

	while (1) {
		ret = rdma_get_cm_event(test.channel, &event);
		if (ret) {
			perror("rdma_get_cm_event");
			break;
		}

		switch (event->event) {
		case RDMA_CM_EVENT_MULTICAST_ERROR:
		case RDMA_CM_EVENT_ADDR_CHANGE:
			printf("mckey: event: %s, status: %d\n",
			       rdma_event_str(event->event), event->status);
			break;
		default:
			break;
		}

		rdma_ack_cm_event(event);
	}
	return NULL;
}