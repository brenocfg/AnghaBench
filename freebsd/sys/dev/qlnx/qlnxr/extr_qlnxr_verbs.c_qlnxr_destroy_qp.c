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
struct qlnxr_qp {scalar_t__ qp_type; int destroyed; int state; int /*<<< orphan*/  qp_id; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  sig; struct qlnxr_dev* dev; } ;
struct qlnxr_dev {int /*<<< orphan*/ * ha; } ;
struct ib_qp_attr {int /*<<< orphan*/  qp_state; } ;
struct ib_qp {int dummy; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;

/* Variables and functions */
 int ECORE_ROCE_QP_STATE_ERR ; 
 int ECORE_ROCE_QP_STATE_INIT ; 
 int ECORE_ROCE_QP_STATE_RESET ; 
 int /*<<< orphan*/  IB_QPS_ERR ; 
 scalar_t__ IB_QPT_GSI ; 
 int IB_QP_STATE ; 
 scalar_t__ QLNX_IS_ROCE (struct qlnxr_dev*) ; 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 struct qlnxr_qp* get_qlnxr_qp (struct ib_qp*) ; 
 int /*<<< orphan*/  kfree (struct qlnxr_qp*) ; 
 int /*<<< orphan*/  qlnxr_destroy_gsi_qp (struct qlnxr_dev*) ; 
 int /*<<< orphan*/  qlnxr_free_qp_resources (struct qlnxr_dev*,struct qlnxr_qp*) ; 
 int /*<<< orphan*/  qlnxr_idr_remove (struct qlnxr_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlnxr_modify_qp (struct ib_qp*,struct ib_qp_attr*,int,int /*<<< orphan*/ *) ; 

int
qlnxr_destroy_qp(struct ib_qp *ibqp)
{
	struct qlnxr_qp *qp = get_qlnxr_qp(ibqp);
	struct qlnxr_dev *dev = qp->dev;
	int rc = 0;
	struct ib_qp_attr attr;
	int attr_mask = 0;
	qlnx_host_t	*ha;

	ha = dev->ha;

	QL_DPRINT12(ha, "enter qp = %p, qp_type=%d\n", qp, qp->qp_type);

	qp->destroyed = 1;

	if (QLNX_IS_ROCE(dev) && (qp->state != (ECORE_ROCE_QP_STATE_RESET |
				  ECORE_ROCE_QP_STATE_ERR |
				  ECORE_ROCE_QP_STATE_INIT))) {

		attr.qp_state = IB_QPS_ERR;
		attr_mask |= IB_QP_STATE;

		/* change the QP state to ERROR */
		qlnxr_modify_qp(ibqp, &attr, attr_mask, NULL);
	}

	if (qp->qp_type == IB_QPT_GSI)
		qlnxr_destroy_gsi_qp(dev);

	qp->sig = ~qp->sig;

	qlnxr_free_qp_resources(dev, qp);

	if (atomic_dec_and_test(&qp->refcnt)) {
		/* TODO: only for iWARP? */
		qlnxr_idr_remove(dev, qp->qp_id);
		kfree(qp);
	}

	QL_DPRINT12(ha, "exit\n");
	return rc;
}