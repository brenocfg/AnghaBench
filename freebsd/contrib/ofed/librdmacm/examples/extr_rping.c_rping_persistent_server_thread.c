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
struct rping_cb {int /*<<< orphan*/  cqthread; int /*<<< orphan*/  child_cm_id; int /*<<< orphan*/  rq_wr; int /*<<< orphan*/  qp; } ;
struct ibv_recv_wr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cq_thread ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free_cb (struct rping_cb*) ; 
 int ibv_post_recv (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ibv_recv_wr**) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  pthread_cancel (int /*<<< orphan*/ ) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct rping_cb*) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_destroy_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_disconnect (int /*<<< orphan*/ ) ; 
 int rping_accept (struct rping_cb*) ; 
 int /*<<< orphan*/  rping_free_buffers (struct rping_cb*) ; 
 int /*<<< orphan*/  rping_free_qp (struct rping_cb*) ; 
 int rping_setup_buffers (struct rping_cb*) ; 
 int rping_setup_qp (struct rping_cb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rping_test_server (struct rping_cb*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void *rping_persistent_server_thread(void *arg)
{
	struct rping_cb *cb = arg;
	struct ibv_recv_wr *bad_wr;
	int ret;

	ret = rping_setup_qp(cb, cb->child_cm_id);
	if (ret) {
		fprintf(stderr, "setup_qp failed: %d\n", ret);
		goto err0;
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
		goto err3;
	}

	rping_test_server(cb);
	rdma_disconnect(cb->child_cm_id);
	pthread_join(cb->cqthread, NULL);
	rping_free_buffers(cb);
	rping_free_qp(cb);
	rdma_destroy_id(cb->child_cm_id);
	free_cb(cb);
	return NULL;
err3:
	pthread_cancel(cb->cqthread);
	pthread_join(cb->cqthread, NULL);
err2:
	rping_free_buffers(cb);
err1:
	rping_free_qp(cb);
err0:
	free_cb(cb);
	return NULL;
}