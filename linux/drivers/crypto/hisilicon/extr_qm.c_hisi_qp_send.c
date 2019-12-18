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
typedef  int u16 ;
struct hisi_qp_status {int sq_tail; int /*<<< orphan*/  used; int /*<<< orphan*/  flags; } ;
struct hisi_qp {struct hisi_qp_status qp_status; int /*<<< orphan*/  qp_id; TYPE_2__* qm; } ;
struct TYPE_4__ {int /*<<< orphan*/  sqe_size; TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int /*<<< orphan*/  QM_DOORBELL_CMD_SQ ; 
 int QM_Q_DEPTH ; 
 int /*<<< orphan*/  QP_STOP ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_db (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 void* qm_get_avail_sqe (struct hisi_qp*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int hisi_qp_send(struct hisi_qp *qp, const void *msg)
{
	struct hisi_qp_status *qp_status = &qp->qp_status;
	u16 sq_tail = qp_status->sq_tail;
	u16 sq_tail_next = (sq_tail + 1) % QM_Q_DEPTH;
	void *sqe = qm_get_avail_sqe(qp);

	if (unlikely(test_bit(QP_STOP, &qp->qp_status.flags))) {
		dev_info(&qp->qm->pdev->dev, "QP is stopped or resetting\n");
		return -EAGAIN;
	}

	if (!sqe)
		return -EBUSY;

	memcpy(sqe, msg, qp->qm->sqe_size);

	qm_db(qp->qm, qp->qp_id, QM_DOORBELL_CMD_SQ, sq_tail_next, 0);
	atomic_inc(&qp->qp_status.used);
	qp_status->sq_tail = sq_tail_next;

	return 0;
}