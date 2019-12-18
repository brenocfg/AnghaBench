#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct krping_cb {TYPE_2__* cm_id; int /*<<< orphan*/  qp; int /*<<< orphan*/  pd; TYPE_2__* child_cm_id; scalar_t__ server; int /*<<< orphan*/  cq; int /*<<< orphan*/  txdepth; } ;
struct TYPE_3__ {int max_recv_wr; int max_recv_sge; int max_send_sge; int /*<<< orphan*/  max_send_wr; } ;
struct ib_qp_init_attr {int /*<<< orphan*/  sq_sig_type; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; int /*<<< orphan*/  qp_type; TYPE_1__ cap; } ;
typedef  int /*<<< orphan*/  init_attr ;
struct TYPE_4__ {int /*<<< orphan*/  qp; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_QPT_RC ; 
 int /*<<< orphan*/  IB_SIGNAL_REQ_WR ; 
 int /*<<< orphan*/  memset (struct ib_qp_init_attr*,int /*<<< orphan*/ ,int) ; 
 int rdma_create_qp (TYPE_2__*,int /*<<< orphan*/ ,struct ib_qp_init_attr*) ; 

__attribute__((used)) static int krping_create_qp(struct krping_cb *cb)
{
	struct ib_qp_init_attr init_attr;
	int ret;

	memset(&init_attr, 0, sizeof(init_attr));
	init_attr.cap.max_send_wr = cb->txdepth;
	init_attr.cap.max_recv_wr = 2;
	
	/* For flush_qp() */
	init_attr.cap.max_send_wr++;
	init_attr.cap.max_recv_wr++;

	init_attr.cap.max_recv_sge = 1;
	init_attr.cap.max_send_sge = 1;
	init_attr.qp_type = IB_QPT_RC;
	init_attr.send_cq = cb->cq;
	init_attr.recv_cq = cb->cq;
	init_attr.sq_sig_type = IB_SIGNAL_REQ_WR;

	if (cb->server) {
		ret = rdma_create_qp(cb->child_cm_id, cb->pd, &init_attr);
		if (!ret)
			cb->qp = cb->child_cm_id->qp;
	} else {
		ret = rdma_create_qp(cb->cm_id, cb->pd, &init_attr);
		if (!ret)
			cb->qp = cb->cm_id->qp;
	}

	return ret;
}