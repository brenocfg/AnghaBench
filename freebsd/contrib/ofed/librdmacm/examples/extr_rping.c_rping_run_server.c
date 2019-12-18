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
struct rping_cb {scalar_t__ state; int /*<<< orphan*/  child_cm_id; int /*<<< orphan*/  cqthread; int /*<<< orphan*/  rq_wr; int /*<<< orphan*/  qp; int /*<<< orphan*/  sem; } ;
struct ibv_recv_wr {int dummy; } ;

/* Variables and functions */
 scalar_t__ CONNECT_REQUEST ; 
 int /*<<< orphan*/  cq_thread ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int ibv_post_recv (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ibv_recv_wr**) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct rping_cb*) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_destroy_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_disconnect (int /*<<< orphan*/ ) ; 
 int rping_accept (struct rping_cb*) ; 
 int rping_bind_server (struct rping_cb*) ; 
 int /*<<< orphan*/  rping_free_buffers (struct rping_cb*) ; 
 int /*<<< orphan*/  rping_free_qp (struct rping_cb*) ; 
 int rping_setup_buffers (struct rping_cb*) ; 
 int rping_setup_qp (struct rping_cb*,int /*<<< orphan*/ ) ; 
 int rping_test_server (struct rping_cb*) ; 
 int /*<<< orphan*/  sem_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int rping_run_server(struct rping_cb *cb)
{
	struct ibv_recv_wr *bad_wr;
	int ret;

	ret = rping_bind_server(cb);
	if (ret)
		return ret;

	sem_wait(&cb->sem);
	if (cb->state != CONNECT_REQUEST) {
		fprintf(stderr, "wait for CONNECT_REQUEST state %d\n",
			cb->state);
		return -1;
	}

	ret = rping_setup_qp(cb, cb->child_cm_id);
	if (ret) {
		fprintf(stderr, "setup_qp failed: %d\n", ret);
		return ret;
	}

	ret = rping_setup_buffers(cb);
	if (ret) {
		fprintf(stderr, "rping_setup_buffers failed: %d\n", ret);
		goto err1;
	}

	ret = ibv_post_recv(cb->qp, &cb->rq_wr, &bad_wr);
	if (ret) {
		fprintf(stderr, "ibv_post_recv failed: %d\n", ret);
		goto err2;
	}

	ret = pthread_create(&cb->cqthread, NULL, cq_thread, cb);
	if (ret) {
		perror("pthread_create");
		goto err2;
	}

	ret = rping_accept(cb);
	if (ret) {
		fprintf(stderr, "connect error %d\n", ret);
		goto err2;
	}

	ret = rping_test_server(cb);
	if (ret) {
		fprintf(stderr, "rping server failed: %d\n", ret);
		goto err3;
	}

	ret = 0;
err3:
	rdma_disconnect(cb->child_cm_id);
	pthread_join(cb->cqthread, NULL);
	rdma_destroy_id(cb->child_cm_id);
err2:
	rping_free_buffers(cb);
err1:
	rping_free_qp(cb);

	return ret;
}