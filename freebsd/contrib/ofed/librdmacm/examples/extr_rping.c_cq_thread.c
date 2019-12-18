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
struct rping_cb {struct ibv_cq* cq; int /*<<< orphan*/  channel; } ;
struct ibv_cq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_LOG (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ibv_ack_cq_events (struct ibv_cq*,int) ; 
 int ibv_get_cq_event (int /*<<< orphan*/ ,struct ibv_cq**,void**) ; 
 int ibv_req_notify_cq (struct ibv_cq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_testcancel () ; 
 int rping_cq_event_handler (struct rping_cb*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void *cq_thread(void *arg)
{
	struct rping_cb *cb = arg;
	struct ibv_cq *ev_cq;
	void *ev_ctx;
	int ret;
	
	DEBUG_LOG("cq_thread started.\n");

	while (1) {	
		pthread_testcancel();

		ret = ibv_get_cq_event(cb->channel, &ev_cq, &ev_ctx);
		if (ret) {
			fprintf(stderr, "Failed to get cq event!\n");
			pthread_exit(NULL);
		}
		if (ev_cq != cb->cq) {
			fprintf(stderr, "Unknown CQ!\n");
			pthread_exit(NULL);
		}
		ret = ibv_req_notify_cq(cb->cq, 0);
		if (ret) {
			fprintf(stderr, "Failed to set notify!\n");
			pthread_exit(NULL);
		}
		ret = rping_cq_event_handler(cb);
		ibv_ack_cq_events(cb->cq, 1);
		if (ret)
			pthread_exit(NULL);
	}
}