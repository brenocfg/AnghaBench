#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t prod; } ;
struct qlnxr_qp {scalar_t__ state; int /*<<< orphan*/  q_lock; TYPE_2__ rq; TYPE_3__* rqe_wr_id; } ;
struct qlnxr_dev {int /*<<< orphan*/  ha; int /*<<< orphan*/  gsi_ll2_handle; int /*<<< orphan*/  rdma_ctx; } ;
struct ib_recv_wr {scalar_t__ num_sge; struct ib_recv_wr* next; int /*<<< orphan*/  wr_id; TYPE_1__* sg_list; } ;
struct ib_qp {int /*<<< orphan*/  device; } ;
struct TYPE_6__ {int /*<<< orphan*/  wr_id; TYPE_1__* sg_list; } ;
struct TYPE_4__ {int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 scalar_t__ ECORE_ROCE_QP_STATE_RTR ; 
 scalar_t__ ECORE_ROCE_QP_STATE_RTS ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ QLNXR_GSI_MAX_RECV_SGE ; 
 int /*<<< orphan*/  QL_DPRINT11 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ ,char*,...) ; 
 int ecore_ll2_post_rx_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct qlnxr_dev* get_qlnxr_dev (int /*<<< orphan*/ ) ; 
 struct qlnxr_qp* get_qlnxr_qp (struct ib_qp*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qlnxr_inc_sw_prod (TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
qlnxr_gsi_post_recv(struct ib_qp *ibqp,
		struct ib_recv_wr *wr,
		struct ib_recv_wr **bad_wr)
{
	struct qlnxr_dev *dev = get_qlnxr_dev((ibqp->device));
	struct qlnxr_qp *qp = get_qlnxr_qp(ibqp);
	unsigned long flags;
	int rc = 0;

	QL_DPRINT12(dev->ha, "enter, wr: %p\n", wr);

	if ((qp->state != ECORE_ROCE_QP_STATE_RTR) &&
	    (qp->state != ECORE_ROCE_QP_STATE_RTS)) {
		*bad_wr = wr;
		QL_DPRINT11(dev->ha, "exit 0\n");
		return -EINVAL;
	}

	spin_lock_irqsave(&qp->q_lock, flags);

	while (wr) {
		if (wr->num_sge > QLNXR_GSI_MAX_RECV_SGE) {
			QL_DPRINT11(dev->ha, "exit 1\n");
			goto err;
		}

		rc = ecore_ll2_post_rx_buffer(dev->rdma_ctx,
				dev->gsi_ll2_handle,
				wr->sg_list[0].addr,
				wr->sg_list[0].length,
				0 /* cookie */,
				1 /* notify_fw */);
		if (rc) {
			QL_DPRINT11(dev->ha, "exit 2\n");
			goto err;
		}

		memset(&qp->rqe_wr_id[qp->rq.prod], 0,
			sizeof(qp->rqe_wr_id[qp->rq.prod]));
		qp->rqe_wr_id[qp->rq.prod].sg_list[0] = wr->sg_list[0];
		qp->rqe_wr_id[qp->rq.prod].wr_id = wr->wr_id;

		qlnxr_inc_sw_prod(&qp->rq);

		wr = wr->next;
	}

	spin_unlock_irqrestore(&qp->q_lock, flags);

	QL_DPRINT12(dev->ha, "exit rc = %d\n", rc);
	return rc;
err:

	spin_unlock_irqrestore(&qp->q_lock, flags);
	*bad_wr = wr;

	QL_DPRINT12(dev->ha, "exit with -ENOMEM\n");
	return -ENOMEM;
}