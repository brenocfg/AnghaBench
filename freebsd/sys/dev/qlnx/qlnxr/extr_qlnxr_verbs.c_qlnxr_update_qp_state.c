#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_8__ {int /*<<< orphan*/  raw; } ;
struct TYPE_7__ {int /*<<< orphan*/  raw; } ;
struct TYPE_10__ {int /*<<< orphan*/  cons; int /*<<< orphan*/  prod; TYPE_2__ iwarp_db2_data; scalar_t__ iwarp_db2; TYPE_1__ db_data; scalar_t__ db; } ;
struct qlnxr_qp {int state; TYPE_4__ sq; TYPE_4__ rq; int /*<<< orphan*/  srq; int /*<<< orphan*/  prev_wqe_size; } ;
struct qlnxr_dev {TYPE_3__* ha; } ;
struct ecore_dev {scalar_t__ doorbells; } ;
struct TYPE_9__ {int /*<<< orphan*/  pci_dbells; struct ecore_dev cdev; } ;
typedef  TYPE_3__ qlnx_host_t ;
typedef  enum ecore_roce_qp_state { ____Placeholder_ecore_roce_qp_state } ecore_roce_qp_state ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_BARRIER_READ ; 
#define  ECORE_ROCE_QP_STATE_ERR 133 
#define  ECORE_ROCE_QP_STATE_INIT 132 
#define  ECORE_ROCE_QP_STATE_RESET 131 
#define  ECORE_ROCE_QP_STATE_RTR 130 
#define  ECORE_ROCE_QP_STATE_RTS 129 
#define  ECORE_ROCE_QP_STATE_SQD 128 
 int EINVAL ; 
 int /*<<< orphan*/  QLNX_IS_IWARP (struct qlnxr_dev*) ; 
 int /*<<< orphan*/  QL_DPRINT11 (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QL_DPRINT12 (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  bus_barrier (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  qlnxr_reset_qp_hwq_info (TYPE_4__*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int
qlnxr_update_qp_state(struct qlnxr_dev *dev,
	struct qlnxr_qp *qp,
	enum ecore_roce_qp_state new_state)
{
	int		status = 0;
	uint32_t	reg_addr;
	struct ecore_dev *cdev;
	qlnx_host_t	*ha;

	ha = dev->ha;
	cdev = &ha->cdev;

	QL_DPRINT12(ha, "enter qp = %p new_state = 0x%x qp->state = 0x%x\n",
		qp, new_state, qp->state);

	if (new_state == qp->state) {
		return 0;
	}

	switch (qp->state) {
	case ECORE_ROCE_QP_STATE_RESET:
		switch (new_state) {
		case ECORE_ROCE_QP_STATE_INIT:
			qp->prev_wqe_size = 0;
			qlnxr_reset_qp_hwq_info(&qp->sq);
			if (!(qp->srq))
				qlnxr_reset_qp_hwq_info(&qp->rq);
			break;
		default:
			status = -EINVAL;
			break;
		};
		break;
	case ECORE_ROCE_QP_STATE_INIT:
		/* INIT->XXX */
		switch (new_state) {
		case ECORE_ROCE_QP_STATE_RTR:
		/* Update doorbell (in case post_recv was done before move to RTR) */
			if (qp->srq)
				break;
			wmb();
			//writel(qp->rq.db_data.raw, qp->rq.db);
			//if (QLNX_IS_IWARP(dev))
			//	writel(qp->rq.iwarp_db2_data.raw,
			//	       qp->rq.iwarp_db2);

			reg_addr = (uint32_t)((uint8_t *)qp->rq.db -
					(uint8_t *)cdev->doorbells);

			bus_write_4(ha->pci_dbells, reg_addr, qp->rq.db_data.raw);
			bus_barrier(ha->pci_dbells,  0, 0, BUS_SPACE_BARRIER_READ);

			if (QLNX_IS_IWARP(dev)) {
				reg_addr = (uint32_t)((uint8_t *)qp->rq.iwarp_db2 -
					(uint8_t *)cdev->doorbells);
				bus_write_4(ha->pci_dbells, reg_addr,\
					qp->rq.iwarp_db2_data.raw);
				bus_barrier(ha->pci_dbells,  0, 0,\
					BUS_SPACE_BARRIER_READ);
			}

			
			mmiowb();
			break;
		case ECORE_ROCE_QP_STATE_ERR:
			/* TBD:flush qps... */
			break;
		default:
			/* invalid state change. */
			status = -EINVAL;
			break;
		};
		break;
	case ECORE_ROCE_QP_STATE_RTR:
		/* RTR->XXX */
		switch (new_state) {
		case ECORE_ROCE_QP_STATE_RTS:
			break;
		case ECORE_ROCE_QP_STATE_ERR:
			break;
		default:
			/* invalid state change. */
			status = -EINVAL;
			break;
		};
		break;
	case ECORE_ROCE_QP_STATE_RTS:
		/* RTS->XXX */
		switch (new_state) {
		case ECORE_ROCE_QP_STATE_SQD:
			break;
		case ECORE_ROCE_QP_STATE_ERR:
			break;
		default:
			/* invalid state change. */
			status = -EINVAL;
			break;
		};
		break;
	case ECORE_ROCE_QP_STATE_SQD:
		/* SQD->XXX */
		switch (new_state) {
		case ECORE_ROCE_QP_STATE_RTS:
		case ECORE_ROCE_QP_STATE_ERR:
			break;
		default:
			/* invalid state change. */
			status = -EINVAL;
			break;
		};
		break;
	case ECORE_ROCE_QP_STATE_ERR:
		/* ERR->XXX */
		switch (new_state) {
		case ECORE_ROCE_QP_STATE_RESET:
			if ((qp->rq.prod != qp->rq.cons) ||
			    (qp->sq.prod != qp->sq.cons)) {
				QL_DPRINT11(ha,
					"Error->Reset with rq/sq "
					"not empty rq.prod=0x%x rq.cons=0x%x"
					" sq.prod=0x%x sq.cons=0x%x\n",
					qp->rq.prod, qp->rq.cons,
					qp->sq.prod, qp->sq.cons);
				status = -EINVAL;
			}
			break;
		default:
			status = -EINVAL;
			break;
		};
		break;
	default:
		status = -EINVAL;
		break;
	};

	QL_DPRINT12(ha, "exit\n");
	return status;
}