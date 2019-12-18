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
struct TYPE_5__ {int /*<<< orphan*/  pbl_info; TYPE_3__* pbl_tbl; int /*<<< orphan*/  umem; } ;
struct TYPE_4__ {int /*<<< orphan*/  pbl_info; TYPE_3__* pbl_tbl; int /*<<< orphan*/  umem; } ;
struct qlnxr_qp {TYPE_2__ urq; int /*<<< orphan*/  srq; TYPE_1__ usq; } ;
struct qlnxr_dev {int /*<<< orphan*/ * ha; } ;
struct ecore_rdma_create_qp_out_params {int /*<<< orphan*/  rq_pbl_phys; int /*<<< orphan*/  rq_pbl_virt; int /*<<< orphan*/  sq_pbl_phys; int /*<<< orphan*/  sq_pbl_virt; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;
struct TYPE_6__ {int /*<<< orphan*/  pa; int /*<<< orphan*/  va; } ;

/* Variables and functions */
 int /*<<< orphan*/  QL_DPRINT11 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  qlnxr_populate_pbls (struct qlnxr_dev*,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
qlnxr_iwarp_populate_user_qp(struct qlnxr_dev *dev,
	struct qlnxr_qp *qp,
	struct ecore_rdma_create_qp_out_params *out_params)
{
	qlnx_host_t	*ha;

	ha = dev->ha;

	QL_DPRINT12(ha, "enter\n");

	qp->usq.pbl_tbl->va = out_params->sq_pbl_virt;
	qp->usq.pbl_tbl->pa = out_params->sq_pbl_phys;

	qlnxr_populate_pbls(dev, qp->usq.umem, qp->usq.pbl_tbl,
			   &qp->usq.pbl_info);

	if (qp->srq) {
		QL_DPRINT11(ha, "qp->srq = %p\n", qp->srq);
		return;
	}

	qp->urq.pbl_tbl->va = out_params->rq_pbl_virt;
	qp->urq.pbl_tbl->pa = out_params->rq_pbl_phys;

	qlnxr_populate_pbls(dev, qp->urq.umem, qp->urq.pbl_tbl,
			   &qp->urq.pbl_info);

	QL_DPRINT12(ha, "exit\n");
	return;
}