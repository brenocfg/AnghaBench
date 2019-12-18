#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct qm_cqe {int sq_head; } ;
struct TYPE_2__ {int cq_head; scalar_t__ cqc_phase; int /*<<< orphan*/  used; } ;
struct hisi_qp {TYPE_1__ qp_status; int /*<<< orphan*/  qp_id; struct qm_cqe* cqe; scalar_t__ sqe; int /*<<< orphan*/  (* req_cb ) (struct hisi_qp*,scalar_t__) ;} ;
struct hisi_qm {int sqe_size; } ;

/* Variables and functions */
 scalar_t__ QM_CQE_PHASE (struct qm_cqe*) ; 
 int /*<<< orphan*/  QM_DOORBELL_CMD_CQ ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_rmb () ; 
 int /*<<< orphan*/  qm_cq_head_update (struct hisi_qp*) ; 
 int /*<<< orphan*/  qm_db (struct hisi_qm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub1 (struct hisi_qp*,scalar_t__) ; 

__attribute__((used)) static void qm_poll_qp(struct hisi_qp *qp, struct hisi_qm *qm)
{
	struct qm_cqe *cqe = qp->cqe + qp->qp_status.cq_head;

	if (qp->req_cb) {
		while (QM_CQE_PHASE(cqe) == qp->qp_status.cqc_phase) {
			dma_rmb();
			qp->req_cb(qp, qp->sqe + qm->sqe_size * cqe->sq_head);
			qm_cq_head_update(qp);
			cqe = qp->cqe + qp->qp_status.cq_head;
			qm_db(qm, qp->qp_id, QM_DOORBELL_CMD_CQ,
			      qp->qp_status.cq_head, 0);
			atomic_dec(&qp->qp_status.used);
		}

		/* set c_flag */
		qm_db(qm, qp->qp_id, QM_DOORBELL_CMD_CQ,
		      qp->qp_status.cq_head, 1);
	}
}