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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  pbl; } ;
struct TYPE_3__ {int /*<<< orphan*/  pbl; } ;
struct qlnxr_qp {int /*<<< orphan*/  icid; int /*<<< orphan*/  qp_id; int /*<<< orphan*/  ecore_qp; TYPE_2__ rq; int /*<<< orphan*/  srq; TYPE_1__ sq; } ;
struct qlnxr_dev {int /*<<< orphan*/  rdma_ctx; int /*<<< orphan*/  cdev; int /*<<< orphan*/ * ha; } ;
struct ecore_rdma_create_qp_out_params {int /*<<< orphan*/  icid; int /*<<< orphan*/  qp_id; } ;
struct ecore_rdma_create_qp_in_params {void* rq_pbl_ptr; void* rq_num_pages; void* sq_pbl_ptr; void* sq_num_pages; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_CHAIN_CNT_TYPE_U32 ; 
 int /*<<< orphan*/  ECORE_CHAIN_MODE_PBL ; 
 int /*<<< orphan*/  ECORE_CHAIN_USE_TO_CONSUME_PRODUCE ; 
 int /*<<< orphan*/  ECORE_CHAIN_USE_TO_PRODUCE ; 
 int EINVAL ; 
 int /*<<< orphan*/  QLNXR_RQE_ELEMENT_SIZE ; 
 int /*<<< orphan*/  QLNXR_SQE_ELEMENT_SIZE ; 
 int /*<<< orphan*/  QL_DPRINT11 (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*) ; 
 int ecore_chain_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* ecore_chain_get_page_cnt (int /*<<< orphan*/ *) ; 
 void* ecore_chain_get_pbl_phys (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecore_rdma_create_qp (int /*<<< orphan*/ ,struct ecore_rdma_create_qp_in_params*,struct ecore_rdma_create_qp_out_params*) ; 
 int /*<<< orphan*/  qlnxr_set_roce_db_info (struct qlnxr_dev*,struct qlnxr_qp*) ; 

__attribute__((used)) static int
qlnxr_roce_create_kernel_qp(struct qlnxr_dev *dev,
	struct qlnxr_qp *qp,
	struct ecore_rdma_create_qp_in_params *in_params,
	u32 n_sq_elems,
	u32 n_rq_elems)
{
	struct ecore_rdma_create_qp_out_params out_params;
	int		rc;
	qlnx_host_t	*ha;

	ha = dev->ha;

	QL_DPRINT12(ha, "enter\n");

        rc = ecore_chain_alloc(
                dev->cdev,
                ECORE_CHAIN_USE_TO_PRODUCE,
                ECORE_CHAIN_MODE_PBL,
                ECORE_CHAIN_CNT_TYPE_U32,
                n_sq_elems,
                QLNXR_SQE_ELEMENT_SIZE,
                &qp->sq.pbl,
                NULL);

	if (rc) {
		QL_DPRINT11(ha, "ecore_chain_alloc qp->sq.pbl failed[%d]\n", rc);
		return rc;
	}

	in_params->sq_num_pages = ecore_chain_get_page_cnt(&qp->sq.pbl);
	in_params->sq_pbl_ptr = ecore_chain_get_pbl_phys(&qp->sq.pbl);

	if (!qp->srq) {

                rc = ecore_chain_alloc(
                        dev->cdev,
                        ECORE_CHAIN_USE_TO_CONSUME_PRODUCE,
                        ECORE_CHAIN_MODE_PBL,
                        ECORE_CHAIN_CNT_TYPE_U32,
                        n_rq_elems,
                        QLNXR_RQE_ELEMENT_SIZE,
                        &qp->rq.pbl,
                        NULL);

		if (rc) {
			QL_DPRINT11(ha,
				"ecore_chain_alloc qp->rq.pbl failed[%d]\n", rc);
			return rc;
		}

		in_params->rq_num_pages = ecore_chain_get_page_cnt(&qp->rq.pbl);
		in_params->rq_pbl_ptr = ecore_chain_get_pbl_phys(&qp->rq.pbl);
	}

	qp->ecore_qp = ecore_rdma_create_qp(dev->rdma_ctx, in_params, &out_params);

	if (!qp->ecore_qp) {
		QL_DPRINT11(ha, "qp->ecore_qp == NULL\n");
		return -EINVAL;
	}

	qp->qp_id = out_params.qp_id;
	qp->icid = out_params.icid;

	qlnxr_set_roce_db_info(dev, qp);

	QL_DPRINT12(ha, "exit\n");
	return 0;
}