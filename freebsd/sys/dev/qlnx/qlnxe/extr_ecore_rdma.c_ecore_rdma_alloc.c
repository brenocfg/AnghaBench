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
typedef  int u32 ;
typedef  void* u16 ;
struct ecore_rdma_info {int num_qps; int num_mrs; int srq_id_offset; int num_srqs; int /*<<< orphan*/  srq_map; int /*<<< orphan*/  xrc_srq_map; int /*<<< orphan*/  cid_map; int /*<<< orphan*/  qp_map; int /*<<< orphan*/  tid_map; int /*<<< orphan*/  toggle_bits; int /*<<< orphan*/  cq_map; int /*<<< orphan*/  dpi_map; int /*<<< orphan*/  xrcd_map; int /*<<< orphan*/  pd_map; void* port; void* dev; void* max_queue_zones; void* queue_zone_base; int /*<<< orphan*/  proto; } ;
struct TYPE_2__ {scalar_t__ personality; } ;
struct ecore_hwfn {int dpi_count; int /*<<< orphan*/  p_dev; TYPE_1__ hw_info; struct ecore_rdma_info* p_rdma_info; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,...) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,...) ; 
 int ECORE_INVAL ; 
 int /*<<< orphan*/  ECORE_L2_QUEUE ; 
 int /*<<< orphan*/  ECORE_MSG_RDMA ; 
 int ECORE_NOMEM ; 
 scalar_t__ ECORE_PCI_ETH_IWARP ; 
 int ECORE_RDMA_MAX_XRCDS ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_IWARP (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  OSAL_NULL ; 
 void* OSAL_ZALLOC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PROTOCOLID_IWARP ; 
 int /*<<< orphan*/  PROTOCOLID_ROCE ; 
 int RDMA_MAX_PDS ; 
 scalar_t__ RESC_NUM (struct ecore_hwfn*,int /*<<< orphan*/ ) ; 
 scalar_t__ RESC_START (struct ecore_hwfn*,int /*<<< orphan*/ ) ; 
 int ecore_cxt_get_proto_cid_count (struct ecore_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ecore_cxt_get_proto_tid_count (struct ecore_hwfn*,int /*<<< orphan*/ ) ; 
 int ecore_cxt_get_srq_count (struct ecore_hwfn*) ; 
 scalar_t__ ecore_cxt_get_xrc_srq_count (struct ecore_hwfn*) ; 
 int ecore_iwarp_alloc (struct ecore_hwfn*) ; 
 int ecore_rdma_bmap_alloc (struct ecore_hwfn*,int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static enum _ecore_status_t ecore_rdma_alloc(struct ecore_hwfn *p_hwfn)
{
	struct ecore_rdma_info *p_rdma_info = p_hwfn->p_rdma_info;
	u32 num_cons, num_tasks;
	enum _ecore_status_t rc;

	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "Allocating RDMA\n");

	if (!p_rdma_info)
		return ECORE_INVAL;

	if (p_hwfn->hw_info.personality == ECORE_PCI_ETH_IWARP)
		p_rdma_info->proto = PROTOCOLID_IWARP;
	else
		p_rdma_info->proto = PROTOCOLID_ROCE;

	num_cons = ecore_cxt_get_proto_cid_count(p_hwfn, p_rdma_info->proto,
						 OSAL_NULL);

	if (IS_IWARP(p_hwfn))
		p_rdma_info->num_qps = num_cons;
	else
		p_rdma_info->num_qps = num_cons / 2;

	/* INTERNAL: RoCE & iWARP use the same taskid */
	num_tasks = ecore_cxt_get_proto_tid_count(p_hwfn, PROTOCOLID_ROCE);

	/* Each MR uses a single task */
	p_rdma_info->num_mrs = num_tasks;

	/* Queue zone lines are shared between RoCE and L2 in such a way that
	 * they can be used by each without obstructing the other.
	 */
	p_rdma_info->queue_zone_base = (u16) RESC_START(p_hwfn, ECORE_L2_QUEUE);
	p_rdma_info->max_queue_zones = (u16) RESC_NUM(p_hwfn, ECORE_L2_QUEUE);

	/* Allocate a struct with device params and fill it */
	p_rdma_info->dev = OSAL_ZALLOC(p_hwfn->p_dev, GFP_KERNEL, sizeof(*p_rdma_info->dev));
	if (!p_rdma_info->dev)
	{
		rc = ECORE_NOMEM;
		DP_NOTICE(p_hwfn, false,
			  "ecore rdma alloc failed: cannot allocate memory (rdma info dev). rc = %d\n",
			  rc);
		return rc;
	}

	/* Allocate a struct with port params and fill it */
	p_rdma_info->port = OSAL_ZALLOC(p_hwfn->p_dev, GFP_KERNEL, sizeof(*p_rdma_info->port));
	if (!p_rdma_info->port)
	{
		DP_NOTICE(p_hwfn, false,
			  "ecore rdma alloc failed: cannot allocate memory (rdma info port)\n");
		return ECORE_NOMEM;
	}

	/* Allocate bit map for pd's */
	rc = ecore_rdma_bmap_alloc(p_hwfn, &p_rdma_info->pd_map, RDMA_MAX_PDS,
				   "PD");
	if (rc != ECORE_SUCCESS)
	{
		DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA,
			   "Failed to allocate pd_map,rc = %d\n",
			   rc);
		return rc;
	}

	/* Allocate bit map for XRC Domains */
	rc = ecore_rdma_bmap_alloc(p_hwfn, &p_rdma_info->xrcd_map,
				   ECORE_RDMA_MAX_XRCDS, "XRCD");
	if (rc != ECORE_SUCCESS)
	{
		DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA,
			   "Failed to allocate xrcd_map,rc = %d\n",
			   rc);
		return rc;
	}

	/* Allocate DPI bitmap */
	rc = ecore_rdma_bmap_alloc(p_hwfn, &p_rdma_info->dpi_map,
				   p_hwfn->dpi_count, "DPI");
	if (rc != ECORE_SUCCESS)
	{
		DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA,
			   "Failed to allocate DPI bitmap, rc = %d\n", rc);
		return rc;
	}

	/* Allocate bitmap for cq's. The maximum number of CQs is bounded to
	 * twice the number of QPs.
	 */
	rc = ecore_rdma_bmap_alloc(p_hwfn, &p_rdma_info->cq_map,
				   num_cons, "CQ");
	if (rc != ECORE_SUCCESS)
	{
		DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA,
			   "Failed to allocate cq bitmap, rc = %d\n", rc);
		return rc;
	}

	/* Allocate bitmap for toggle bit for cq icids
	 * We toggle the bit every time we create or resize cq for a given icid.
	 * The maximum number of CQs is bounded to the number of connections we
	 * support. (num_qps in iWARP or num_qps/2 in RoCE).
	 */
	rc = ecore_rdma_bmap_alloc(p_hwfn, &p_rdma_info->toggle_bits,
				   num_cons, "Toggle");
	if (rc != ECORE_SUCCESS)
	{
		DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA,
			   "Failed to allocate toogle bits, rc = %d\n", rc);
		return rc;
	}

	/* Allocate bitmap for itids */
	rc = ecore_rdma_bmap_alloc(p_hwfn, &p_rdma_info->tid_map,
				   p_rdma_info->num_mrs, "MR");
	if (rc != ECORE_SUCCESS)
	{
		DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA,
			   "Failed to allocate itids bitmaps, rc = %d\n", rc);
		return rc;
	}

	/* Allocate bitmap for qps. */
	rc = ecore_rdma_bmap_alloc(p_hwfn, &p_rdma_info->qp_map,
				   p_rdma_info->num_qps, "QP");
	if (rc != ECORE_SUCCESS)
	{
		DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA,
			   "Failed to allocate qp bitmap, rc = %d\n", rc);
		return rc;
	}

	/* Allocate bitmap for cids used for responders/requesters. */
	rc = ecore_rdma_bmap_alloc(p_hwfn, &p_rdma_info->cid_map, num_cons,
				   "REAL CID");
	if (rc != ECORE_SUCCESS)
	{
		DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA,
			   "Failed to allocate cid bitmap, rc = %d\n", rc);
		return rc;
	}

	/* The first SRQ follows the last XRC SRQ. This means that the
	 * SRQ IDs start from an offset equals to max_xrc_srqs.
	 */
	p_rdma_info->srq_id_offset = (u16)ecore_cxt_get_xrc_srq_count(p_hwfn);
	rc = ecore_rdma_bmap_alloc(p_hwfn, &p_rdma_info->xrc_srq_map,
				   p_rdma_info->srq_id_offset, "XRC SRQ");
	if (rc != ECORE_SUCCESS) {
		DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA,
			   "Failed to allocate xrc srq bitmap, rc = %d\n", rc);
		return rc;
	}

	/* Allocate bitmap for srqs */
	p_rdma_info->num_srqs = ecore_cxt_get_srq_count(p_hwfn);
	rc = ecore_rdma_bmap_alloc(p_hwfn, &p_rdma_info->srq_map,
				   p_rdma_info->num_srqs,
				   "SRQ");
	if (rc != ECORE_SUCCESS) {
		DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA,
			   "Failed to allocate srq bitmap, rc = %d\n", rc);

		return rc;
	}

	if (IS_IWARP(p_hwfn))
		rc = ecore_iwarp_alloc(p_hwfn);

	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "rc = %d\n", rc);

	return rc;
}