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
struct roce_modify_qp_resp_ramrod_data {int /*<<< orphan*/  dst_gid; int /*<<< orphan*/  src_gid; void* mtu; int /*<<< orphan*/  flow_label; void* p_key; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  max_ird; scalar_t__ fields; scalar_t__ flags; } ;
struct TYPE_4__ {struct roce_modify_qp_resp_ramrod_data roce_modify_qp_resp; } ;
struct ecore_spq_entry {TYPE_2__ ramrod; } ;
struct ecore_sp_init_data {int cid; int /*<<< orphan*/  comp_mode; int /*<<< orphan*/  opaque_fid; } ;
struct ecore_rdma_qp {int icid; int incoming_rdma_read_en; int incoming_rdma_write_en; int incoming_atomic_en; int e2e_flow_control_en; int min_rnr_nak_timer; int /*<<< orphan*/  mtu; int /*<<< orphan*/  flow_label; int /*<<< orphan*/  pkey; int /*<<< orphan*/  hop_limit_ttl; int /*<<< orphan*/  traffic_class_tos; int /*<<< orphan*/  max_rd_atomic_resp; int /*<<< orphan*/  resp_offloaded; int /*<<< orphan*/  has_resp; } ;
struct TYPE_3__ {int /*<<< orphan*/  opaque_fid; } ;
struct ecore_hwfn {TYPE_1__ hw_info; } ;
typedef  int /*<<< orphan*/  init_data ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,int) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ECORE_MSG_RDMA ; 
 int /*<<< orphan*/  ECORE_RDMA_MODIFY_QP_VALID_MAX_RD_ATOMIC_RESP ; 
 int /*<<< orphan*/  ECORE_RDMA_MODIFY_QP_VALID_RDMA_OPS_EN ; 
 int /*<<< orphan*/  ECORE_ROCE_MODIFY_QP_VALID_ADDRESS_VECTOR ; 
 int /*<<< orphan*/  ECORE_ROCE_MODIFY_QP_VALID_MIN_RNR_NAK_TIMER ; 
 int /*<<< orphan*/  ECORE_ROCE_MODIFY_QP_VALID_PKEY ; 
 int /*<<< orphan*/  ECORE_SPQ_MODE_EBLOCK ; 
 int ECORE_SUCCESS ; 
 int GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* OSAL_CPU_TO_LE16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_CPU_TO_LE32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_MEMSET (struct ecore_sp_init_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OSAL_NULL ; 
 int /*<<< orphan*/  PROTOCOLID_ROCE ; 
 int /*<<< orphan*/  ROCE_CREATE_QP_RESP_RAMROD_DATA_E2E_FLOW_CONTROL_EN ; 
 int /*<<< orphan*/  ROCE_EVENT_MODIFY_QP ; 
 int /*<<< orphan*/  ROCE_MODIFY_QP_RESP_RAMROD_DATA_ADDRESS_VECTOR_FLG ; 
 int /*<<< orphan*/  ROCE_MODIFY_QP_RESP_RAMROD_DATA_ATOMIC_EN ; 
 int /*<<< orphan*/  ROCE_MODIFY_QP_RESP_RAMROD_DATA_MAX_IRD_FLG ; 
 int /*<<< orphan*/  ROCE_MODIFY_QP_RESP_RAMROD_DATA_MIN_RNR_NAK_TIMER ; 
 int /*<<< orphan*/  ROCE_MODIFY_QP_RESP_RAMROD_DATA_MIN_RNR_NAK_TIMER_FLG ; 
 int /*<<< orphan*/  ROCE_MODIFY_QP_RESP_RAMROD_DATA_MOVE_TO_ERR_FLG ; 
 int /*<<< orphan*/  ROCE_MODIFY_QP_RESP_RAMROD_DATA_P_KEY_FLG ; 
 int /*<<< orphan*/  ROCE_MODIFY_QP_RESP_RAMROD_DATA_RDMA_OPS_EN_FLG ; 
 int /*<<< orphan*/  ROCE_MODIFY_QP_RESP_RAMROD_DATA_RDMA_RD_EN ; 
 int /*<<< orphan*/  ROCE_MODIFY_QP_RESP_RAMROD_DATA_RDMA_WR_EN ; 
 int /*<<< orphan*/  SET_FIELD (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ecore_rdma_copy_gids (struct ecore_rdma_qp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ecore_sp_init_request (struct ecore_hwfn*,struct ecore_spq_entry**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ecore_sp_init_data*) ; 
 int ecore_spq_post (struct ecore_hwfn*,struct ecore_spq_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum _ecore_status_t ecore_roce_sp_modify_responder(
	struct ecore_hwfn	*p_hwfn,
	struct ecore_rdma_qp	*qp,
	bool			move_to_err,
	u32			modify_flags)
{
	struct roce_modify_qp_resp_ramrod_data	*p_ramrod;
	struct ecore_sp_init_data		init_data;
	struct ecore_spq_entry			*p_ent;
	enum _ecore_status_t			rc;

	if (!qp->has_resp)
		return ECORE_SUCCESS;

	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "icid = %08x\n", qp->icid);

	if (move_to_err && !qp->resp_offloaded)
		return ECORE_SUCCESS;

	/* Get SPQ entry */
	OSAL_MEMSET(&init_data, 0, sizeof(init_data));
	init_data.cid = qp->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = ECORE_SPQ_MODE_EBLOCK;

	rc = ecore_sp_init_request(p_hwfn, &p_ent,
				   ROCE_EVENT_MODIFY_QP,
				   PROTOCOLID_ROCE, &init_data);
	if (rc != ECORE_SUCCESS)
	{
		DP_NOTICE(p_hwfn, false, "rc = %d\n", rc);
		return rc;
	}

	p_ramrod = &p_ent->ramrod.roce_modify_qp_resp;

	p_ramrod->flags = 0;

	SET_FIELD(p_ramrod->flags,
		  ROCE_MODIFY_QP_RESP_RAMROD_DATA_MOVE_TO_ERR_FLG,
		  move_to_err);

	SET_FIELD(p_ramrod->flags,
		  ROCE_MODIFY_QP_RESP_RAMROD_DATA_RDMA_RD_EN,
		  qp->incoming_rdma_read_en);

	SET_FIELD(p_ramrod->flags,
		  ROCE_MODIFY_QP_RESP_RAMROD_DATA_RDMA_WR_EN,
		  qp->incoming_rdma_write_en);

	SET_FIELD(p_ramrod->flags,
		  ROCE_MODIFY_QP_RESP_RAMROD_DATA_ATOMIC_EN,
		  qp->incoming_atomic_en);

	SET_FIELD(p_ramrod->flags,
		  ROCE_CREATE_QP_RESP_RAMROD_DATA_E2E_FLOW_CONTROL_EN,
		  qp->e2e_flow_control_en);

	SET_FIELD(p_ramrod->flags,
		  ROCE_MODIFY_QP_RESP_RAMROD_DATA_RDMA_OPS_EN_FLG,
		  GET_FIELD(modify_flags,
			    ECORE_RDMA_MODIFY_QP_VALID_RDMA_OPS_EN));

	SET_FIELD(p_ramrod->flags,
		  ROCE_MODIFY_QP_RESP_RAMROD_DATA_P_KEY_FLG,
		  GET_FIELD(modify_flags, ECORE_ROCE_MODIFY_QP_VALID_PKEY));

	SET_FIELD(p_ramrod->flags,
		  ROCE_MODIFY_QP_RESP_RAMROD_DATA_ADDRESS_VECTOR_FLG,
		  GET_FIELD(modify_flags,
			    ECORE_ROCE_MODIFY_QP_VALID_ADDRESS_VECTOR));

	SET_FIELD(p_ramrod->flags,
		  ROCE_MODIFY_QP_RESP_RAMROD_DATA_MAX_IRD_FLG,
		  GET_FIELD(modify_flags,
			    ECORE_RDMA_MODIFY_QP_VALID_MAX_RD_ATOMIC_RESP));

	/* TBD: future use only
	 * #define ROCE_MODIFY_QP_RESP_RAMROD_DATA_PRI_FLG_MASK
	 * #define ROCE_MODIFY_QP_RESP_RAMROD_DATA_PRI_FLG_SHIFT
	 */

	SET_FIELD(p_ramrod->flags,
		  ROCE_MODIFY_QP_RESP_RAMROD_DATA_MIN_RNR_NAK_TIMER_FLG,
		  GET_FIELD(modify_flags,
			    ECORE_ROCE_MODIFY_QP_VALID_MIN_RNR_NAK_TIMER));

	p_ramrod->fields = 0;
	SET_FIELD(p_ramrod->fields,
		  ROCE_MODIFY_QP_RESP_RAMROD_DATA_MIN_RNR_NAK_TIMER,
		  qp->min_rnr_nak_timer);

	p_ramrod->max_ird = qp->max_rd_atomic_resp;
	p_ramrod->traffic_class = qp->traffic_class_tos;
	p_ramrod->hop_limit = qp->hop_limit_ttl;
	p_ramrod->p_key = OSAL_CPU_TO_LE16(qp->pkey);
	p_ramrod->flow_label = OSAL_CPU_TO_LE32(qp->flow_label);
	p_ramrod->mtu = OSAL_CPU_TO_LE16(qp->mtu);
	ecore_rdma_copy_gids(qp, p_ramrod->src_gid, p_ramrod->dst_gid);
	rc = ecore_spq_post(p_hwfn, p_ent, OSAL_NULL);

	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "Modify responder, rc = %d\n", rc);
	return rc;
}