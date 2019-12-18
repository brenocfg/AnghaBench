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
typedef  int /*<<< orphan*/  u32 ;
struct roce_destroy_qp_req_ramrod_data {int /*<<< orphan*/  output_params_addr; } ;
struct roce_destroy_qp_req_output_params {int /*<<< orphan*/  cq_prod; int /*<<< orphan*/  num_bound_mw; } ;
struct TYPE_5__ {struct roce_destroy_qp_req_ramrod_data roce_destroy_qp_req; } ;
struct ecore_spq_entry {TYPE_2__ ramrod; } ;
struct ecore_sp_init_data {int cid; int /*<<< orphan*/  comp_mode; int /*<<< orphan*/  opaque_fid; } ;
struct TYPE_6__ {int /*<<< orphan*/  req; } ;
struct ecore_rdma_qp {int icid; int req_offloaded; int orq_num_pages; int /*<<< orphan*/  orq_phys_addr; struct roce_destroy_qp_req_output_params* orq; TYPE_3__ cq_prod; int /*<<< orphan*/  has_req; } ;
struct TYPE_4__ {int /*<<< orphan*/  opaque_fid; } ;
struct ecore_hwfn {int /*<<< orphan*/  p_dev; TYPE_1__ hw_info; } ;
typedef  int /*<<< orphan*/  init_data ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_REGPAIR_LE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ECORE_MSG_RDMA ; 
 int ECORE_NOMEM ; 
 int /*<<< orphan*/  ECORE_SPQ_MODE_EBLOCK ; 
 int ECORE_SUCCESS ; 
 scalar_t__ OSAL_DMA_ALLOC_COHERENT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  OSAL_DMA_FREE_COHERENT (int /*<<< orphan*/ ,struct roce_destroy_qp_req_output_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OSAL_LE32_TO_CPU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_MEMSET (struct ecore_sp_init_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OSAL_NULL ; 
 int /*<<< orphan*/  PROTOCOLID_ROCE ; 
 int RDMA_RING_PAGE_SIZE ; 
 int /*<<< orphan*/  ROCE_RAMROD_DESTROY_QP ; 
 int ecore_sp_init_request (struct ecore_hwfn*,struct ecore_spq_entry**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ecore_sp_init_data*) ; 
 int ecore_spq_post (struct ecore_hwfn*,struct ecore_spq_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum _ecore_status_t ecore_roce_sp_destroy_qp_requester(
	struct ecore_hwfn    *p_hwfn,
	struct ecore_rdma_qp *qp,
	u32                  *num_bound_mw,
	u32                  *cq_prod)
{
	struct roce_destroy_qp_req_output_params	*p_ramrod_res;
	struct roce_destroy_qp_req_ramrod_data	*p_ramrod;
	struct ecore_sp_init_data		init_data;
	struct ecore_spq_entry			*p_ent;
	dma_addr_t				ramrod_res_phys;
	enum _ecore_status_t			rc;

	if (!qp->has_req) {
		*num_bound_mw = 0;
		*cq_prod = 0;
		return ECORE_SUCCESS;
	}

	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "icid = %08x\n", qp->icid);

	if (!qp->req_offloaded) {
		*cq_prod = qp->cq_prod.req;
		return ECORE_SUCCESS;
	}

	p_ramrod_res = (struct roce_destroy_qp_req_output_params *)
			OSAL_DMA_ALLOC_COHERENT(p_hwfn->p_dev, &ramrod_res_phys,
				sizeof(*p_ramrod_res));
	if (!p_ramrod_res)
	{
		DP_NOTICE(p_hwfn, false,
			  "ecore destroy requester failed: cannot allocate memory (ramrod)\n");
		return ECORE_NOMEM;
	}

	/* Get SPQ entry */
	OSAL_MEMSET(&init_data, 0, sizeof(init_data));
	init_data.cid = qp->icid + 1;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = ECORE_SPQ_MODE_EBLOCK;

	rc = ecore_sp_init_request(p_hwfn, &p_ent, ROCE_RAMROD_DESTROY_QP,
				   PROTOCOLID_ROCE, &init_data);
	if (rc != ECORE_SUCCESS)
		goto err;

	p_ramrod = &p_ent->ramrod.roce_destroy_qp_req;
	DMA_REGPAIR_LE(p_ramrod->output_params_addr, ramrod_res_phys);

	rc = ecore_spq_post(p_hwfn, p_ent, OSAL_NULL);
	if (rc != ECORE_SUCCESS)
		goto err;

	*num_bound_mw = OSAL_LE32_TO_CPU(p_ramrod_res->num_bound_mw);
	*cq_prod = OSAL_LE32_TO_CPU(p_ramrod_res->cq_prod);
	qp->cq_prod.req = *cq_prod;

	/* Free ORQ - only if ramrod succeeded, in case FW is still using it */
	OSAL_DMA_FREE_COHERENT(p_hwfn->p_dev,
			       qp->orq,
			       qp->orq_phys_addr,
			       qp->orq_num_pages *
			       RDMA_RING_PAGE_SIZE);

	qp->req_offloaded = false;

	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "Destroy requester, rc = %d\n", rc);

	/* "fall through" */

err:
	OSAL_DMA_FREE_COHERENT(p_hwfn->p_dev, p_ramrod_res, ramrod_res_phys,
			       sizeof(*p_ramrod_res));

	return rc;
}