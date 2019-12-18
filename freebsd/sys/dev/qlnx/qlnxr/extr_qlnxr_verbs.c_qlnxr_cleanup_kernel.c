#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qlnxr_qp {int /*<<< orphan*/  rqe_wr_id; int /*<<< orphan*/  wqe_wr_id; } ;
struct qlnxr_dev {TYPE_1__* ha; } ;
struct TYPE_3__ {int qlnxr_debug; } ;
typedef  TYPE_1__ qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  QL_DPRINT12 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 scalar_t__ qlnxr_qp_has_rq (struct qlnxr_qp*) ; 
 scalar_t__ qlnxr_qp_has_sq (struct qlnxr_qp*) ; 

__attribute__((used)) static void
qlnxr_cleanup_kernel(struct qlnxr_dev *dev, struct qlnxr_qp *qp)
{
	qlnx_host_t	*ha;

	ha = dev->ha;

	QL_DPRINT12(ha, "enter\n");
 
	if (qlnxr_qp_has_sq(qp)) {
		QL_DPRINT12(ha, "freeing SQ\n");
		ha->qlnxr_debug = 1;
//		ecore_chain_free(dev->cdev, &qp->sq.pbl);
		ha->qlnxr_debug = 0;
		kfree(qp->wqe_wr_id);
	}

	if (qlnxr_qp_has_rq(qp)) {
		QL_DPRINT12(ha, "freeing RQ\n");
		ha->qlnxr_debug = 1;
	//	ecore_chain_free(dev->cdev, &qp->rq.pbl);
		ha->qlnxr_debug = 0;
		kfree(qp->rqe_wr_id);
	}

	QL_DPRINT12(ha, "exit\n");
	return;
}