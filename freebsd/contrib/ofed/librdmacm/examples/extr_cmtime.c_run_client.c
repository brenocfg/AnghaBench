#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pthread_t ;
struct TYPE_10__ {int /*<<< orphan*/  ai_dst_addr; int /*<<< orphan*/  ai_src_addr; int /*<<< orphan*/  ai_connect_len; int /*<<< orphan*/  ai_connect; } ;
struct TYPE_9__ {int responder_resources; int initiator_depth; int /*<<< orphan*/  private_data_len; int /*<<< orphan*/  private_data; void* retry_count; } ;
struct TYPE_8__ {int error; int /*<<< orphan*/  id; void* retries; } ;

/* Variables and functions */
 size_t STEP_BIND ; 
 size_t STEP_CONNECT ; 
 size_t STEP_CREATE_QP ; 
 size_t STEP_DISCONNECT ; 
 size_t STEP_RESOLVE_ADDR ; 
 size_t STEP_RESOLVE_ROUTE ; 
 scalar_t__* completed ; 
 TYPE_2__ conn_param ; 
 int connections ; 
 int /*<<< orphan*/  dst_addr ; 
 int /*<<< orphan*/  end_perf (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  end_time (size_t) ; 
 char* gai_strerror (int) ; 
 int get_rdma_addr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__**) ; 
 int /*<<< orphan*/  hints ; 
 int /*<<< orphan*/  init_qp_attr ; 
 TYPE_1__* nodes ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  port ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  process_events ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* rai ; 
 int rdma_bind_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rdma_connect (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int rdma_create_qp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_disconnect (int /*<<< orphan*/ ) ; 
 int rdma_resolve_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rdma_resolve_route (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* retries ; 
 int /*<<< orphan*/  sched_yield () ; 
 scalar_t__ src_addr ; 
 int /*<<< orphan*/  start_perf (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  start_time (size_t) ; 
 scalar_t__* started ; 
 int /*<<< orphan*/  timeout ; 

__attribute__((used)) static int run_client(void)
{
	pthread_t event_thread;
	int i, ret;

	ret = get_rdma_addr(src_addr, dst_addr, port, &hints, &rai);
	if (ret) {
		printf("getaddrinfo error: %s\n", gai_strerror(ret));
		return ret;
	}

	conn_param.responder_resources = 1;
	conn_param.initiator_depth = 1;
	conn_param.retry_count = retries;
	conn_param.private_data = rai->ai_connect;
	conn_param.private_data_len = rai->ai_connect_len;

	ret = pthread_create(&event_thread, NULL, process_events, NULL);
	if (ret) {
		perror("failure creating event thread");
		return ret;
	}

	if (src_addr) {
		printf("binding source address\n");
		start_time(STEP_BIND);
		for (i = 0; i < connections; i++) {
			start_perf(&nodes[i], STEP_BIND);
			ret = rdma_bind_addr(nodes[i].id, rai->ai_src_addr);
			if (ret) {
				perror("failure bind addr");
				nodes[i].error = 1;
				continue;
			}
			end_perf(&nodes[i], STEP_BIND);
		}
		end_time(STEP_BIND);
	}

	printf("resolving address\n");
	start_time(STEP_RESOLVE_ADDR);
	for (i = 0; i < connections; i++) {
		if (nodes[i].error)
			continue;
		nodes[i].retries = retries;
		start_perf(&nodes[i], STEP_RESOLVE_ADDR);
		ret = rdma_resolve_addr(nodes[i].id, rai->ai_src_addr,
					rai->ai_dst_addr, timeout);
		if (ret) {
			perror("failure getting addr");
			nodes[i].error = 1;
			continue;
		}
		started[STEP_RESOLVE_ADDR]++;
	}
	while (started[STEP_RESOLVE_ADDR] != completed[STEP_RESOLVE_ADDR]) sched_yield();
	end_time(STEP_RESOLVE_ADDR);

	printf("resolving route\n");
	start_time(STEP_RESOLVE_ROUTE);
	for (i = 0; i < connections; i++) {
		if (nodes[i].error)
			continue;
		nodes[i].retries = retries;
		start_perf(&nodes[i], STEP_RESOLVE_ROUTE);
		ret = rdma_resolve_route(nodes[i].id, timeout);
		if (ret) {
			perror("failure resolving route");
			nodes[i].error = 1;
			continue;
		}
		started[STEP_RESOLVE_ROUTE]++;
	}
	while (started[STEP_RESOLVE_ROUTE] != completed[STEP_RESOLVE_ROUTE]) sched_yield();
	end_time(STEP_RESOLVE_ROUTE);

	printf("creating qp\n");
	start_time(STEP_CREATE_QP);
	for (i = 0; i < connections; i++) {
		if (nodes[i].error)
			continue;
		start_perf(&nodes[i], STEP_CREATE_QP);
		ret = rdma_create_qp(nodes[i].id, NULL, &init_qp_attr);
		if (ret) {
			perror("failure creating qp");
			nodes[i].error = 1;
			continue;
		}
		end_perf(&nodes[i], STEP_CREATE_QP);
	}
	end_time(STEP_CREATE_QP);

	printf("connecting\n");
	start_time(STEP_CONNECT);
	for (i = 0; i < connections; i++) {
		if (nodes[i].error)
			continue;
		start_perf(&nodes[i], STEP_CONNECT);
		ret = rdma_connect(nodes[i].id, &conn_param);
		if (ret) {
			perror("failure rconnecting");
			nodes[i].error = 1;
			continue;
		}
		started[STEP_CONNECT]++;
	}
	while (started[STEP_CONNECT] != completed[STEP_CONNECT]) sched_yield();
	end_time(STEP_CONNECT);

	printf("disconnecting\n");
	start_time(STEP_DISCONNECT);
	for (i = 0; i < connections; i++) {
		if (nodes[i].error)
			continue;
		start_perf(&nodes[i], STEP_DISCONNECT);
		rdma_disconnect(nodes[i].id);
		started[STEP_DISCONNECT]++;
	}
	while (started[STEP_DISCONNECT] != completed[STEP_DISCONNECT]) sched_yield();
	end_time(STEP_DISCONNECT);

	return ret;
}