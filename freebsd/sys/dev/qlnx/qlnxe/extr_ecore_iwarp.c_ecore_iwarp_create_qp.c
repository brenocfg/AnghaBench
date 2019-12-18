#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_6__ {void* lo; void* hi; } ;
struct iwarp_create_qp_ramrod_data {void* physical_q1; void* physical_q0; void* dpi; void* cq_cid_for_rq; void* cq_cid_for_sq; TYPE_2__ qp_handle_for_cqe; int /*<<< orphan*/  rq_num_pages; int /*<<< orphan*/  sq_num_pages; int /*<<< orphan*/  pd; int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {struct iwarp_create_qp_ramrod_data iwarp_create_qp; } ;
struct ecore_spq_entry {TYPE_1__ ramrod; } ;
struct ecore_sp_init_data {int opaque_fid; int /*<<< orphan*/  comp_mode; scalar_t__ cid; } ;
struct TYPE_7__ {int hi; int lo; } ;
struct ecore_rdma_qp {int shared_queue_phys_addr; int sq_cq_id; int rq_cq_id; scalar_t__ shared_queue; scalar_t__ dpi; TYPE_3__ qp_handle; int /*<<< orphan*/  rq_num_pages; int /*<<< orphan*/  sq_num_pages; int /*<<< orphan*/  pd; int /*<<< orphan*/  use_srq; int /*<<< orphan*/  incoming_atomic_en; int /*<<< orphan*/  incoming_rdma_write_en; int /*<<< orphan*/  incoming_rdma_read_en; int /*<<< orphan*/  signal_all; int /*<<< orphan*/  fmr_and_reserved_lkey; scalar_t__ icid; } ;
struct ecore_rdma_create_qp_out_params {int sq_pbl_phys; int rq_pbl_phys; int /*<<< orphan*/ * rq_pbl_virt; int /*<<< orphan*/ * sq_pbl_virt; } ;
struct TYPE_8__ {int opaque_fid; } ;
struct ecore_hwfn {int /*<<< orphan*/  p_dev; TYPE_4__ hw_info; } ;
typedef  int /*<<< orphan*/  init_data ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*) ; 
 int ECORE_NOMEM ; 
 int /*<<< orphan*/  ECORE_SPQ_MODE_EBLOCK ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  IWARP_CREATE_QP_RAMROD_DATA_ATOMIC_EN ; 
 int /*<<< orphan*/  IWARP_CREATE_QP_RAMROD_DATA_FMR_AND_RESERVED_EN ; 
 int /*<<< orphan*/  IWARP_CREATE_QP_RAMROD_DATA_RDMA_RD_EN ; 
 int /*<<< orphan*/  IWARP_CREATE_QP_RAMROD_DATA_RDMA_WR_EN ; 
 int /*<<< orphan*/  IWARP_CREATE_QP_RAMROD_DATA_SIGNALED_COMP ; 
 int /*<<< orphan*/  IWARP_CREATE_QP_RAMROD_DATA_SRQ_FLG ; 
 int /*<<< orphan*/  IWARP_RAMROD_CMD_ID_CREATE_QP ; 
 int IWARP_SHARED_QUEUE_PAGE_RQ_PBL_OFFSET ; 
 int /*<<< orphan*/  IWARP_SHARED_QUEUE_PAGE_SIZE ; 
 int IWARP_SHARED_QUEUE_PAGE_SQ_PBL_OFFSET ; 
 void* OSAL_CPU_TO_LE16 (scalar_t__) ; 
 void* OSAL_CPU_TO_LE32 (int) ; 
 scalar_t__ OSAL_DMA_ALLOC_COHERENT (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_DMA_FREE_COHERENT (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_MEMSET (struct ecore_sp_init_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OSAL_NULL ; 
 int /*<<< orphan*/  PQ_FLAGS_ACK ; 
 int /*<<< orphan*/  PQ_FLAGS_OFLD ; 
 int /*<<< orphan*/  PROTOCOLID_IWARP ; 
 int /*<<< orphan*/  SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ecore_get_cm_pq_idx (struct ecore_hwfn*,int /*<<< orphan*/ ) ; 
 int ecore_iwarp_alloc_cid (struct ecore_hwfn*,scalar_t__*) ; 
 int ecore_sp_init_request (struct ecore_hwfn*,struct ecore_spq_entry**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ecore_sp_init_data*) ; 
 int ecore_spq_post (struct ecore_hwfn*,struct ecore_spq_entry*,int /*<<< orphan*/ ) ; 

enum _ecore_status_t
ecore_iwarp_create_qp(struct ecore_hwfn *p_hwfn,
		      struct ecore_rdma_qp *qp,
		      struct ecore_rdma_create_qp_out_params *out_params)
{
	struct iwarp_create_qp_ramrod_data *p_ramrod;
	struct ecore_sp_init_data init_data;
	struct ecore_spq_entry *p_ent;
	enum _ecore_status_t rc;
	u16 physical_queue;
	u32 cid;

	qp->shared_queue =
		OSAL_DMA_ALLOC_COHERENT(p_hwfn->p_dev,
					&qp->shared_queue_phys_addr,
					IWARP_SHARED_QUEUE_PAGE_SIZE);
	if (!qp->shared_queue) {
		DP_NOTICE(p_hwfn, false,
			  "ecore iwarp create qp failed: cannot allocate memory (shared queue).\n");
		return ECORE_NOMEM;
	} else {
		out_params->sq_pbl_virt = (u8 *)qp->shared_queue +
			IWARP_SHARED_QUEUE_PAGE_SQ_PBL_OFFSET;
		out_params->sq_pbl_phys = qp->shared_queue_phys_addr +
			IWARP_SHARED_QUEUE_PAGE_SQ_PBL_OFFSET;
		out_params->rq_pbl_virt = (u8 *)qp->shared_queue +
			IWARP_SHARED_QUEUE_PAGE_RQ_PBL_OFFSET;
		out_params->rq_pbl_phys = qp->shared_queue_phys_addr +
			IWARP_SHARED_QUEUE_PAGE_RQ_PBL_OFFSET;
	}

	rc = ecore_iwarp_alloc_cid(p_hwfn, &cid);
	if (rc != ECORE_SUCCESS)
		goto err1;

	qp->icid = (u16)cid;

	OSAL_MEMSET(&init_data, 0, sizeof(init_data));
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.cid = qp->icid;
	init_data.comp_mode = ECORE_SPQ_MODE_EBLOCK;

	rc = ecore_sp_init_request(p_hwfn, &p_ent,
				   IWARP_RAMROD_CMD_ID_CREATE_QP,
				   PROTOCOLID_IWARP, &init_data);
	if (rc != ECORE_SUCCESS)
		return rc;

	p_ramrod = &p_ent->ramrod.iwarp_create_qp;

	SET_FIELD(p_ramrod->flags,
		  IWARP_CREATE_QP_RAMROD_DATA_FMR_AND_RESERVED_EN,
		  qp->fmr_and_reserved_lkey);

	SET_FIELD(p_ramrod->flags,
		  IWARP_CREATE_QP_RAMROD_DATA_SIGNALED_COMP,
		  qp->signal_all);

	SET_FIELD(p_ramrod->flags,
		  IWARP_CREATE_QP_RAMROD_DATA_RDMA_RD_EN,
		  qp->incoming_rdma_read_en);

	SET_FIELD(p_ramrod->flags,
		  IWARP_CREATE_QP_RAMROD_DATA_RDMA_WR_EN,
		  qp->incoming_rdma_write_en);

	SET_FIELD(p_ramrod->flags,
		  IWARP_CREATE_QP_RAMROD_DATA_ATOMIC_EN,
		  qp->incoming_atomic_en);

	SET_FIELD(p_ramrod->flags,
		  IWARP_CREATE_QP_RAMROD_DATA_SRQ_FLG,
		  qp->use_srq);

	p_ramrod->pd = qp->pd;
	p_ramrod->sq_num_pages = qp->sq_num_pages;
	p_ramrod->rq_num_pages = qp->rq_num_pages;

	p_ramrod->qp_handle_for_cqe.hi = OSAL_CPU_TO_LE32(qp->qp_handle.hi);
	p_ramrod->qp_handle_for_cqe.lo = OSAL_CPU_TO_LE32(qp->qp_handle.lo);

	p_ramrod->cq_cid_for_sq =
		OSAL_CPU_TO_LE32((p_hwfn->hw_info.opaque_fid << 16) |
				 qp->sq_cq_id);
	p_ramrod->cq_cid_for_rq =
		OSAL_CPU_TO_LE32((p_hwfn->hw_info.opaque_fid << 16) |
				 qp->rq_cq_id);

	p_ramrod->dpi = OSAL_CPU_TO_LE16(qp->dpi);

	physical_queue = ecore_get_cm_pq_idx(p_hwfn, PQ_FLAGS_OFLD);
	p_ramrod->physical_q0 = OSAL_CPU_TO_LE16(physical_queue);
	physical_queue = ecore_get_cm_pq_idx(p_hwfn, PQ_FLAGS_ACK);
	p_ramrod->physical_q1 = OSAL_CPU_TO_LE16(physical_queue);

	rc = ecore_spq_post(p_hwfn, p_ent, OSAL_NULL);

	if (rc != ECORE_SUCCESS)
		goto err1;

	return rc;

err1:
	OSAL_DMA_FREE_COHERENT(p_hwfn->p_dev,
			       qp->shared_queue,
			       qp->shared_queue_phys_addr,
			       IWARP_SHARED_QUEUE_PAGE_SIZE);

	return rc;
}