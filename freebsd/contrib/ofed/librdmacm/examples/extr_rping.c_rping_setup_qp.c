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
struct rping_cb {int /*<<< orphan*/  pd; int /*<<< orphan*/  channel; int /*<<< orphan*/  cq; int /*<<< orphan*/  qp; } ;
struct rdma_cm_id {int /*<<< orphan*/  verbs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_LOG (char*,int /*<<< orphan*/ ) ; 
 int RPING_SQ_DEPTH ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ibv_alloc_pd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibv_create_comp_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibv_create_cq (int /*<<< orphan*/ ,int,struct rping_cb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibv_dealloc_pd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibv_destroy_comp_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibv_destroy_cq (int /*<<< orphan*/ ) ; 
 int ibv_req_notify_cq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int rping_create_qp (struct rping_cb*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int rping_setup_qp(struct rping_cb *cb, struct rdma_cm_id *cm_id)
{
	int ret;

	cb->pd = ibv_alloc_pd(cm_id->verbs);
	if (!cb->pd) {
		fprintf(stderr, "ibv_alloc_pd failed\n");
		return errno;
	}
	DEBUG_LOG("created pd %p\n", cb->pd);

	cb->channel = ibv_create_comp_channel(cm_id->verbs);
	if (!cb->channel) {
		fprintf(stderr, "ibv_create_comp_channel failed\n");
		ret = errno;
		goto err1;
	}
	DEBUG_LOG("created channel %p\n", cb->channel);

	cb->cq = ibv_create_cq(cm_id->verbs, RPING_SQ_DEPTH * 2, cb,
				cb->channel, 0);
	if (!cb->cq) {
		fprintf(stderr, "ibv_create_cq failed\n");
		ret = errno;
		goto err2;
	}
	DEBUG_LOG("created cq %p\n", cb->cq);

	ret = ibv_req_notify_cq(cb->cq, 0);
	if (ret) {
		fprintf(stderr, "ibv_create_cq failed\n");
		ret = errno;
		goto err3;
	}

	ret = rping_create_qp(cb);
	if (ret) {
		perror("rdma_create_qp");
		goto err3;
	}
	DEBUG_LOG("created qp %p\n", cb->qp);
	return 0;

err3:
	ibv_destroy_cq(cb->cq);
err2:
	ibv_destroy_comp_channel(cb->channel);
err1:
	ibv_dealloc_pd(cb->pd);
	return ret;
}