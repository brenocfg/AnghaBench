#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct TYPE_17__ {void* opaque_fid; void* srq_idx; } ;
struct TYPE_14__ {void* lo; void* hi; } ;
struct TYPE_12__ {void* lo; void* hi; } ;
struct roce_create_qp_resp_ramrod_data {int irq_num_pages; scalar_t__ stats_counter_id; TYPE_6__ srq_id; void* vlan_id; int /*<<< orphan*/  udp_src_port; int /*<<< orphan*/  local_mac_addr; int /*<<< orphan*/  remote_mac_addr; void* dpi; void* low_latency_phy_queue; void* regular_latency_phy_queue; void* xrc_domain; void* cq_cid; TYPE_3__ qp_handle_for_cqe; TYPE_1__ qp_handle_for_async; int /*<<< orphan*/  dst_gid; int /*<<< orphan*/  src_gid; int /*<<< orphan*/  irq_pbl_addr; int /*<<< orphan*/  rq_pbl_addr; void* rq_num_pages; void* pd; void* initial_psn; void* mtu; void* dst_qp_id; void* flow_label; void* p_key; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  max_ird; scalar_t__ flags; } ;
struct TYPE_11__ {struct roce_create_qp_resp_ramrod_data roce_create_qp_resp; } ;
struct ecore_spq_entry {TYPE_10__ ramrod; } ;
struct ecore_sp_init_data {int cid; int opaque_fid; int /*<<< orphan*/  comp_mode; } ;
struct TYPE_18__ {scalar_t__ resp; } ;
struct TYPE_15__ {int hi; int lo; } ;
struct TYPE_13__ {int hi; int lo; } ;
struct ecore_rdma_qp {int irq_num_pages; int icid; int incoming_rdma_read_en; int incoming_rdma_write_en; int incoming_atomic_en; int e2e_flow_control_en; int use_srq; int fmr_and_reserved_lkey; int min_rnr_nak_timer; int pkey; int flow_label; int dest_qp; int mtu; int rq_psn; int pd; int rq_num_pages; int rq_cq_id; int xrcd_id; int dpi; int vlan_id; int resp_offloaded; int /*<<< orphan*/  irq_phys_addr; int /*<<< orphan*/  irq; TYPE_7__ cq_prod; scalar_t__ stats_queue; int /*<<< orphan*/  srq_id; int /*<<< orphan*/  udp_src_port; int /*<<< orphan*/  local_mac_addr; int /*<<< orphan*/  remote_mac_addr; TYPE_4__ qp_handle; TYPE_2__ qp_handle_async; int /*<<< orphan*/  rq_pbl_ptr; int /*<<< orphan*/  hop_limit_ttl; int /*<<< orphan*/  traffic_class_tos; int /*<<< orphan*/  max_rd_atomic_resp; int /*<<< orphan*/  roce_mode; int /*<<< orphan*/  qp_idx; int /*<<< orphan*/  has_resp; } ;
struct TYPE_20__ {int opaque_fid; } ;
struct ecore_hwfn {int /*<<< orphan*/  p_dev; TYPE_8__* p_rdma_info; TYPE_9__ hw_info; } ;
typedef  int /*<<< orphan*/  init_data ;
typedef  enum roce_flavor { ____Placeholder_roce_flavor } roce_flavor ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_16__ {scalar_t__ dcqcn_enabled; } ;
struct TYPE_19__ {int /*<<< orphan*/  proto; TYPE_5__ roce; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_REGPAIR_LE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,int) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  ECORE_MSG_RDMA ; 
 int ECORE_NOMEM ; 
 int /*<<< orphan*/  ECORE_RDMA_STATS_QUEUE ; 
 int /*<<< orphan*/  ECORE_SPQ_MODE_EBLOCK ; 
 int ECORE_SUCCESS ; 
 void* OSAL_CPU_TO_LE16 (int) ; 
 void* OSAL_CPU_TO_LE32 (int) ; 
 int /*<<< orphan*/  OSAL_DMA_ALLOC_COHERENT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  OSAL_DMA_FREE_COHERENT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OSAL_MEMSET (struct ecore_sp_init_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OSAL_NULL ; 
 int /*<<< orphan*/  PQ_FLAGS_LLT ; 
 int /*<<< orphan*/  PQ_FLAGS_OFLD ; 
 int /*<<< orphan*/  PROTOCOLID_ROCE ; 
 int RDMA_RING_PAGE_SIZE ; 
 scalar_t__ RESC_START (struct ecore_hwfn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ROCE_CREATE_QP_RESP_RAMROD_DATA_ATOMIC_EN ; 
 int /*<<< orphan*/  ROCE_CREATE_QP_RESP_RAMROD_DATA_E2E_FLOW_CONTROL_EN ; 
 int /*<<< orphan*/  ROCE_CREATE_QP_RESP_RAMROD_DATA_MIN_RNR_NAK_TIMER ; 
 int /*<<< orphan*/  ROCE_CREATE_QP_RESP_RAMROD_DATA_RDMA_RD_EN ; 
 int /*<<< orphan*/  ROCE_CREATE_QP_RESP_RAMROD_DATA_RDMA_WR_EN ; 
 int /*<<< orphan*/  ROCE_CREATE_QP_RESP_RAMROD_DATA_RESERVED_KEY_EN ; 
 int /*<<< orphan*/  ROCE_CREATE_QP_RESP_RAMROD_DATA_ROCE_FLAVOR ; 
 int /*<<< orphan*/  ROCE_CREATE_QP_RESP_RAMROD_DATA_SRQ_FLG ; 
 int /*<<< orphan*/  ROCE_CREATE_QP_RESP_RAMROD_DATA_XRC_FLAG ; 
 int ROCE_DCQCN_RP_MAX_QPS ; 
 int /*<<< orphan*/  ROCE_RAMROD_CREATE_QP ; 
 int /*<<< orphan*/  SET_FIELD (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ecore_cxt_get_proto_cid_start (struct ecore_hwfn*,int /*<<< orphan*/ ) ; 
 int ecore_get_cm_pq_idx (struct ecore_hwfn*,int /*<<< orphan*/ ) ; 
 int ecore_get_cm_pq_idx_rl (struct ecore_hwfn*,int) ; 
 int /*<<< orphan*/  ecore_rdma_copy_gids (struct ecore_rdma_qp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ecore_rdma_get_fw_srq_id (struct ecore_hwfn*,int /*<<< orphan*/ ,int) ; 
 int ecore_rdma_is_xrc_qp (struct ecore_rdma_qp*) ; 
 int /*<<< orphan*/  ecore_rdma_set_fw_mac (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ecore_roce_mode_to_flavor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_roce_set_cid (struct ecore_hwfn*,scalar_t__) ; 
 int ecore_sp_init_request (struct ecore_hwfn*,struct ecore_spq_entry**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ecore_sp_init_data*) ; 
 int ecore_spq_post (struct ecore_hwfn*,struct ecore_spq_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum _ecore_status_t ecore_roce_sp_create_responder(
	struct ecore_hwfn    *p_hwfn,
	struct ecore_rdma_qp *qp)
{
	struct roce_create_qp_resp_ramrod_data *p_ramrod;
	u16 regular_latency_queue, low_latency_queue;
	struct ecore_sp_init_data init_data;
	enum roce_flavor roce_flavor;
	struct ecore_spq_entry *p_ent;
	enum _ecore_status_t rc;
	u32 cid_start;
	u16 fw_srq_id;
	bool is_xrc;

	if (!qp->has_resp)
		return ECORE_SUCCESS;

	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "qp_idx = %08x\n", qp->qp_idx);

	/* Allocate DMA-able memory for IRQ */
	qp->irq_num_pages = 1;
	qp->irq = OSAL_DMA_ALLOC_COHERENT(p_hwfn->p_dev,
					  &qp->irq_phys_addr,
					  RDMA_RING_PAGE_SIZE);
	if (!qp->irq) {
		rc = ECORE_NOMEM;
		DP_NOTICE(p_hwfn, false,
			  "ecore create responder failed: cannot allocate memory (irq). rc = %d\n",
			  rc);
		return rc;
	}

	/* Get SPQ entry */
	OSAL_MEMSET(&init_data, 0, sizeof(init_data));
	init_data.cid = qp->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = ECORE_SPQ_MODE_EBLOCK;

	rc = ecore_sp_init_request(p_hwfn, &p_ent, ROCE_RAMROD_CREATE_QP,
				   PROTOCOLID_ROCE, &init_data);
	if (rc != ECORE_SUCCESS)
		goto err;

	p_ramrod = &p_ent->ramrod.roce_create_qp_resp;

	p_ramrod->flags = 0;

	roce_flavor = ecore_roce_mode_to_flavor(qp->roce_mode);
	SET_FIELD(p_ramrod->flags,
		  ROCE_CREATE_QP_RESP_RAMROD_DATA_ROCE_FLAVOR,
		  roce_flavor);

	SET_FIELD(p_ramrod->flags,
		  ROCE_CREATE_QP_RESP_RAMROD_DATA_RDMA_RD_EN,
		  qp->incoming_rdma_read_en);

	SET_FIELD(p_ramrod->flags,
		  ROCE_CREATE_QP_RESP_RAMROD_DATA_RDMA_WR_EN,
		  qp->incoming_rdma_write_en);

	SET_FIELD(p_ramrod->flags,
		  ROCE_CREATE_QP_RESP_RAMROD_DATA_ATOMIC_EN,
		  qp->incoming_atomic_en);

	SET_FIELD(p_ramrod->flags,
		  ROCE_CREATE_QP_RESP_RAMROD_DATA_E2E_FLOW_CONTROL_EN,
		  qp->e2e_flow_control_en);

	SET_FIELD(p_ramrod->flags,
		  ROCE_CREATE_QP_RESP_RAMROD_DATA_SRQ_FLG,
		  qp->use_srq);

	SET_FIELD(p_ramrod->flags,
		  ROCE_CREATE_QP_RESP_RAMROD_DATA_RESERVED_KEY_EN,
		  qp->fmr_and_reserved_lkey);

	SET_FIELD(p_ramrod->flags,
		  ROCE_CREATE_QP_RESP_RAMROD_DATA_XRC_FLAG,
		  ecore_rdma_is_xrc_qp(qp));

	/* TBD: future use only
	 * #define ROCE_CREATE_QP_RESP_RAMROD_DATA_PRI_MASK
	 * #define ROCE_CREATE_QP_RESP_RAMROD_DATA_PRI_SHIFT
	 */
	SET_FIELD(p_ramrod->flags,
		  ROCE_CREATE_QP_RESP_RAMROD_DATA_MIN_RNR_NAK_TIMER,
		  qp->min_rnr_nak_timer);

	p_ramrod->max_ird =
		qp->max_rd_atomic_resp;
	p_ramrod->traffic_class = qp->traffic_class_tos;
	p_ramrod->hop_limit = qp->hop_limit_ttl;
	p_ramrod->irq_num_pages = qp->irq_num_pages;
	p_ramrod->p_key = OSAL_CPU_TO_LE16(qp->pkey);
	p_ramrod->flow_label = OSAL_CPU_TO_LE32(qp->flow_label);
	p_ramrod->dst_qp_id = OSAL_CPU_TO_LE32(qp->dest_qp);
	p_ramrod->mtu = OSAL_CPU_TO_LE16(qp->mtu);
	p_ramrod->initial_psn = OSAL_CPU_TO_LE32(qp->rq_psn);
	p_ramrod->pd = OSAL_CPU_TO_LE16(qp->pd);
	p_ramrod->rq_num_pages = OSAL_CPU_TO_LE16(qp->rq_num_pages);
	DMA_REGPAIR_LE(p_ramrod->rq_pbl_addr, qp->rq_pbl_ptr);
	DMA_REGPAIR_LE(p_ramrod->irq_pbl_addr, qp->irq_phys_addr);
	ecore_rdma_copy_gids(qp, p_ramrod->src_gid, p_ramrod->dst_gid);
	p_ramrod->qp_handle_for_async.hi =
			OSAL_CPU_TO_LE32(qp->qp_handle_async.hi);
	p_ramrod->qp_handle_for_async.lo =
			OSAL_CPU_TO_LE32(qp->qp_handle_async.lo);
	p_ramrod->qp_handle_for_cqe.hi = OSAL_CPU_TO_LE32(qp->qp_handle.hi);
	p_ramrod->qp_handle_for_cqe.lo = OSAL_CPU_TO_LE32(qp->qp_handle.lo);
	p_ramrod->cq_cid = OSAL_CPU_TO_LE32((p_hwfn->hw_info.opaque_fid << 16) | qp->rq_cq_id);
	p_ramrod->xrc_domain = OSAL_CPU_TO_LE16(qp->xrcd_id);

#ifdef CONFIG_DCQCN
	/* when dcqcn is enabled physical queues are determined accoridng to qp id */
	if (p_hwfn->p_rdma_info->roce.dcqcn_enabled)
		regular_latency_queue =
			ecore_get_cm_pq_idx_rl(p_hwfn,
					       (qp->icid >> 1) %
							ROCE_DCQCN_RP_MAX_QPS);
	else
#endif
		regular_latency_queue = ecore_get_cm_pq_idx(p_hwfn, PQ_FLAGS_OFLD);
	low_latency_queue = ecore_get_cm_pq_idx(p_hwfn, PQ_FLAGS_LLT);

	p_ramrod->regular_latency_phy_queue = OSAL_CPU_TO_LE16(regular_latency_queue);
	p_ramrod->low_latency_phy_queue = OSAL_CPU_TO_LE16(low_latency_queue);
	p_ramrod->dpi = OSAL_CPU_TO_LE16(qp->dpi);

	ecore_rdma_set_fw_mac(p_ramrod->remote_mac_addr, qp->remote_mac_addr);
	ecore_rdma_set_fw_mac(p_ramrod->local_mac_addr, qp->local_mac_addr);

	p_ramrod->udp_src_port = qp->udp_src_port;
	p_ramrod->vlan_id = OSAL_CPU_TO_LE16(qp->vlan_id);
	is_xrc = ecore_rdma_is_xrc_qp(qp);
	fw_srq_id = ecore_rdma_get_fw_srq_id(p_hwfn, qp->srq_id, is_xrc);
	p_ramrod->srq_id.srq_idx = OSAL_CPU_TO_LE16(fw_srq_id);
	p_ramrod->srq_id.opaque_fid = OSAL_CPU_TO_LE16(p_hwfn->hw_info.opaque_fid);

	p_ramrod->stats_counter_id = RESC_START(p_hwfn, ECORE_RDMA_STATS_QUEUE) +
				     qp->stats_queue;

	rc = ecore_spq_post(p_hwfn, p_ent, OSAL_NULL);

	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "rc = %d regular physical queue = 0x%x, low latency physical queue 0x%x\n",
		   rc, regular_latency_queue, low_latency_queue);

	if (rc != ECORE_SUCCESS)
		goto err;

	qp->resp_offloaded = true;
	qp->cq_prod.resp = 0;

	cid_start = ecore_cxt_get_proto_cid_start(p_hwfn,
						  p_hwfn->p_rdma_info->proto);
	ecore_roce_set_cid(p_hwfn, qp->icid - cid_start);

	return rc;

err:
	DP_NOTICE(p_hwfn, false, "create responder - failed, rc = %d\n", rc);
	OSAL_DMA_FREE_COHERENT(p_hwfn->p_dev,
			       qp->irq,
			       qp->irq_phys_addr,
			       qp->irq_num_pages *
			       RDMA_RING_PAGE_SIZE);

	return rc;
}