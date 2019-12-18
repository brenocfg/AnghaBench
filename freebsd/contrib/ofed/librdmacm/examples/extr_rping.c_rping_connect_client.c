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
struct rping_cb {scalar_t__ state; int /*<<< orphan*/  sem; int /*<<< orphan*/  cm_id; } ;
struct rdma_conn_param {int responder_resources; int initiator_depth; int retry_count; } ;

/* Variables and functions */
 scalar_t__ CONNECTED ; 
 int /*<<< orphan*/  DEBUG_LOG (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct rdma_conn_param*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int rdma_connect (int /*<<< orphan*/ ,struct rdma_conn_param*) ; 
 int /*<<< orphan*/  sem_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int rping_connect_client(struct rping_cb *cb)
{
	struct rdma_conn_param conn_param;
	int ret;

	memset(&conn_param, 0, sizeof conn_param);
	conn_param.responder_resources = 1;
	conn_param.initiator_depth = 1;
	conn_param.retry_count = 7;

	ret = rdma_connect(cb->cm_id, &conn_param);
	if (ret) {
		perror("rdma_connect");
		return ret;
	}

	sem_wait(&cb->sem);
	if (cb->state != CONNECTED) {
		fprintf(stderr, "wait for CONNECTED state %d\n", cb->state);
		return -1;
	}

	DEBUG_LOG("rmda_connect successful\n");
	return 0;
}