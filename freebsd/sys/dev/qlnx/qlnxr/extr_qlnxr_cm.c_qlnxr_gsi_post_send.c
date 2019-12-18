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
struct TYPE_4__ {size_t prod; } ;
struct qlnxr_qp {scalar_t__ state; int /*<<< orphan*/  q_lock; TYPE_2__ sq; TYPE_1__* wqe_wr_id; struct qlnxr_dev* dev; } ;
struct qlnxr_dev {int /*<<< orphan*/  ha; } ;
struct ib_send_wr {scalar_t__ num_sge; scalar_t__ opcode; int send_flags; struct ib_send_wr* next; int /*<<< orphan*/  wr_id; } ;
struct ib_qp {int dummy; } ;
struct ecore_roce_ll2_packet {int dummy; } ;
struct TYPE_3__ {int signaled; int /*<<< orphan*/  opcode; int /*<<< orphan*/  wr_id; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ ECORE_ROCE_QP_STATE_RTS ; 
 int EINVAL ; 
 int IB_SEND_SIGNALED ; 
 int /*<<< orphan*/  IB_WC_SEND ; 
 scalar_t__ IB_WR_SEND ; 
 int /*<<< orphan*/  QL_DPRINT11 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ RDMA_MAX_SGE_PER_SQ_WQE ; 
 struct qlnxr_qp* get_qlnxr_qp (struct ib_qp*) ; 
 int qlnxr_gsi_build_packet (struct qlnxr_dev*,struct qlnxr_qp*,struct ib_send_wr*,struct ecore_roce_ll2_packet**) ; 
 int /*<<< orphan*/  qlnxr_inc_sw_prod (TYPE_2__*) ; 
 int qlnxr_ll2_post_tx (struct qlnxr_dev*,struct ecore_roce_ll2_packet*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
qlnxr_gsi_post_send(struct ib_qp *ibqp,
		struct ib_send_wr *wr,
		struct ib_send_wr **bad_wr)
{
	struct ecore_roce_ll2_packet *pkt = NULL;
	struct qlnxr_qp *qp = get_qlnxr_qp(ibqp);
	struct qlnxr_dev *dev = qp->dev;
	unsigned long flags;
	int rc;

	QL_DPRINT12(dev->ha, "exit\n");

	if (qp->state != ECORE_ROCE_QP_STATE_RTS) {
		QL_DPRINT11(dev->ha,
			"(qp->state != ECORE_ROCE_QP_STATE_RTS)\n");
		*bad_wr = wr;
		return -EINVAL;
	}

	if (wr->num_sge > RDMA_MAX_SGE_PER_SQ_WQE) {
		QL_DPRINT11(dev->ha,
			"(wr->num_sge > RDMA_MAX_SGE_PER_SQ_WQE)\n");
		rc = -EINVAL;
		goto err;
	}

	if (wr->opcode != IB_WR_SEND) {
		QL_DPRINT11(dev->ha, "(wr->opcode > IB_WR_SEND)\n");
		rc = -EINVAL;
		goto err;
	}

	spin_lock_irqsave(&qp->q_lock, flags);

	rc = qlnxr_gsi_build_packet(dev, qp, wr, &pkt);
	if(rc) {
		spin_unlock_irqrestore(&qp->q_lock, flags);
		QL_DPRINT11(dev->ha, "qlnxr_gsi_build_packet failed\n");
		goto err;
	}

	rc = qlnxr_ll2_post_tx(dev, pkt);

	if (!rc) {
		qp->wqe_wr_id[qp->sq.prod].wr_id = wr->wr_id;
		qp->wqe_wr_id[qp->sq.prod].signaled = 
			!!(wr->send_flags & IB_SEND_SIGNALED);
		qp->wqe_wr_id[qp->sq.prod].opcode = IB_WC_SEND;
		qlnxr_inc_sw_prod(&qp->sq);
		QL_DPRINT11(dev->ha, "packet sent over gsi qp\n");
	} else {
		QL_DPRINT11(dev->ha, "qlnxr_ll2_post_tx failed\n");
		rc = -EAGAIN;
		*bad_wr = wr;
	}

	spin_unlock_irqrestore(&qp->q_lock, flags);

	if (wr->next != NULL) {
		*bad_wr = wr->next;
		rc=-EINVAL;
	}

	QL_DPRINT12(dev->ha, "exit\n");
	return rc;

err:
	*bad_wr = wr;
	QL_DPRINT12(dev->ha, "exit error\n");
	return rc;
}