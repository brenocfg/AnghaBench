#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct rdma_cm_id {int dummy; } ;
typedef  int /*<<< orphan*/  pthread_t ;
struct TYPE_10__ {int /*<<< orphan*/  cond; int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct TYPE_9__ {int /*<<< orphan*/  ai_port_space; } ;
struct TYPE_8__ {int /*<<< orphan*/  ai_src_addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  cond; int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  channel ; 
 int /*<<< orphan*/  disc_handler_thread ; 
 TYPE_6__ disc_work ; 
 int /*<<< orphan*/  dst_addr ; 
 char* gai_strerror (int) ; 
 int get_rdma_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,TYPE_2__**) ; 
 TYPE_3__ hints ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  port ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  process_events (int /*<<< orphan*/ *) ; 
 int pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* rai ; 
 int rdma_bind_addr (struct rdma_cm_id*,int /*<<< orphan*/ ) ; 
 int rdma_create_id (int /*<<< orphan*/ ,struct rdma_cm_id**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_destroy_id (struct rdma_cm_id*) ; 
 int rdma_listen (struct rdma_cm_id*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  req_handler_thread ; 
 TYPE_1__ req_work ; 
 int /*<<< orphan*/  src_addr ; 

__attribute__((used)) static int run_server(void)
{
	pthread_t req_thread, disc_thread;
	struct rdma_cm_id *listen_id;
	int ret;

	INIT_LIST(&req_work.list);
	INIT_LIST(&disc_work.list);
	ret = pthread_mutex_init(&req_work.lock, NULL);
	if (ret) {
		perror("initializing mutex for req work");
		return ret;
	}

	ret = pthread_mutex_init(&disc_work.lock, NULL);
	if (ret) {
		perror("initializing mutex for disc work");
		return ret;
	}

	ret = pthread_cond_init(&req_work.cond, NULL);
	if (ret) {
		perror("initializing cond for req work");
		return ret;
	}

	ret = pthread_cond_init(&disc_work.cond, NULL);
	if (ret) {
		perror("initializing cond for disc work");
		return ret;
	}

	ret = pthread_create(&req_thread, NULL, req_handler_thread, NULL);
	if (ret) {
		perror("failed to create req handler thread");
		return ret;
	}

	ret = pthread_create(&disc_thread, NULL, disc_handler_thread, NULL);
	if (ret) {
		perror("failed to create disconnect handler thread");
		return ret;
	}

	ret = rdma_create_id(channel, &listen_id, NULL, hints.ai_port_space);
	if (ret) {
		perror("listen request failed");
		return ret;
	}

	ret = get_rdma_addr(src_addr, dst_addr, port, &hints, &rai);
	if (ret) {
		printf("getrdmaaddr error: %s\n", gai_strerror(ret));
		goto out;
	}

	ret = rdma_bind_addr(listen_id, rai->ai_src_addr);
	if (ret) {
		perror("bind address failed");
		goto out;
	}

	ret = rdma_listen(listen_id, 0);
	if (ret) {
		perror("failure trying to listen");
		goto out;
	}

	process_events(NULL);
 out:
	rdma_destroy_id(listen_id);
	return ret;
}