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
struct rping_cb {int /*<<< orphan*/  cm_channel; } ;
struct rdma_cm_event {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  rdma_ack_cm_event (struct rdma_cm_event*) ; 
 int rdma_get_cm_event (int /*<<< orphan*/ ,struct rdma_cm_event**) ; 
 int rping_cma_event_handler (int /*<<< orphan*/ ,struct rdma_cm_event*) ; 

__attribute__((used)) static void *cm_thread(void *arg)
{
	struct rping_cb *cb = arg;
	struct rdma_cm_event *event;
	int ret;

	while (1) {
		ret = rdma_get_cm_event(cb->cm_channel, &event);
		if (ret) {
			perror("rdma_get_cm_event");
			exit(ret);
		}
		ret = rping_cma_event_handler(event->id, event);
		rdma_ack_cm_event(event);
		if (ret)
			exit(ret);
	}
}