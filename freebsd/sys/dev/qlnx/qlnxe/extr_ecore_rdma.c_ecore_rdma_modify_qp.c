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
typedef  int /*<<< orphan*/  u8 ;
struct ecore_rdma_qp {int cur_state; scalar_t__ qp_type; int has_req; int has_resp; int /*<<< orphan*/  sqd_async; int /*<<< orphan*/  min_rnr_nak_timer; int /*<<< orphan*/  rnr_retry_cnt; int /*<<< orphan*/  retry_cnt; int /*<<< orphan*/  ack_timeout; int /*<<< orphan*/  max_rd_atomic_resp; int /*<<< orphan*/  max_rd_atomic_req; int /*<<< orphan*/  sq_psn; int /*<<< orphan*/  rq_psn; int /*<<< orphan*/ * local_mac_addr; int /*<<< orphan*/ * remote_mac_addr; int /*<<< orphan*/  mtu; int /*<<< orphan*/  traffic_class_tos; int /*<<< orphan*/  vlan_id; int /*<<< orphan*/  udp_src_port; int /*<<< orphan*/  dgid; int /*<<< orphan*/  sgid; int /*<<< orphan*/  hop_limit_ttl; int /*<<< orphan*/  flow_label; int /*<<< orphan*/  dest_qp; int /*<<< orphan*/  e2e_flow_control_en; int /*<<< orphan*/  pkey; int /*<<< orphan*/  roce_mode; int /*<<< orphan*/  incoming_atomic_en; int /*<<< orphan*/  incoming_rdma_write_en; int /*<<< orphan*/  incoming_rdma_read_en; } ;
struct ecore_rdma_modify_qp_in_params {int new_state; int /*<<< orphan*/  modify_flags; int /*<<< orphan*/  sqd_async; int /*<<< orphan*/  min_rnr_nak_timer; int /*<<< orphan*/  rnr_retry_cnt; int /*<<< orphan*/  retry_cnt; int /*<<< orphan*/  ack_timeout; int /*<<< orphan*/  max_rd_atomic_resp; int /*<<< orphan*/  max_rd_atomic_req; int /*<<< orphan*/  sq_psn; int /*<<< orphan*/  rq_psn; int /*<<< orphan*/ * local_mac_addr; scalar_t__ use_local_mac; int /*<<< orphan*/ * remote_mac_addr; int /*<<< orphan*/  mtu; int /*<<< orphan*/  traffic_class_tos; int /*<<< orphan*/  vlan_id; int /*<<< orphan*/  udp_src_port; int /*<<< orphan*/  dgid; int /*<<< orphan*/  sgid; int /*<<< orphan*/  hop_limit_ttl; int /*<<< orphan*/  flow_label; int /*<<< orphan*/  dest_qp; int /*<<< orphan*/  e2e_flow_control_en; int /*<<< orphan*/  pkey; int /*<<< orphan*/  roce_mode; int /*<<< orphan*/  incoming_atomic_en; int /*<<< orphan*/  incoming_rdma_write_en; int /*<<< orphan*/  incoming_rdma_read_en; } ;
struct TYPE_6__ {int /*<<< orphan*/  hw_mac_addr; } ;
struct ecore_hwfn {TYPE_3__ hw_info; TYPE_2__* p_rdma_info; } ;
typedef  enum ecore_roce_qp_state { ____Placeholder_ecore_roce_qp_state } ecore_roce_qp_state ;
typedef  enum ecore_iwarp_qp_state { ____Placeholder_ecore_iwarp_qp_state } ecore_iwarp_qp_state ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_4__ {int /*<<< orphan*/  dscp; scalar_t__ dscp_en; int /*<<< orphan*/  ecn; scalar_t__ ecn_en; int /*<<< orphan*/  vlan_pri; scalar_t__ vlan_pri_en; } ;
struct TYPE_5__ {TYPE_1__ glob_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ECORE_MSG_RDMA ; 
 int /*<<< orphan*/  ECORE_RDMA_DSCP ; 
 int /*<<< orphan*/  ECORE_RDMA_ECN ; 
 int /*<<< orphan*/  ECORE_RDMA_MODIFY_QP_VALID_MAX_RD_ATOMIC_REQ ; 
 int /*<<< orphan*/  ECORE_RDMA_MODIFY_QP_VALID_MAX_RD_ATOMIC_RESP ; 
 int /*<<< orphan*/  ECORE_RDMA_MODIFY_QP_VALID_NEW_STATE ; 
 int /*<<< orphan*/  ECORE_RDMA_MODIFY_QP_VALID_RDMA_OPS_EN ; 
 scalar_t__ ECORE_RDMA_QP_TYPE_XRC_INI ; 
 scalar_t__ ECORE_RDMA_QP_TYPE_XRC_TGT ; 
 int /*<<< orphan*/  ECORE_RDMA_VLAN_PRIO ; 
 int /*<<< orphan*/  ECORE_ROCE_MODIFY_QP_VALID_ACK_TIMEOUT ; 
 int /*<<< orphan*/  ECORE_ROCE_MODIFY_QP_VALID_ADDRESS_VECTOR ; 
 int /*<<< orphan*/  ECORE_ROCE_MODIFY_QP_VALID_DEST_QP ; 
 int /*<<< orphan*/  ECORE_ROCE_MODIFY_QP_VALID_E2E_FLOW_CONTROL_EN ; 
 int /*<<< orphan*/  ECORE_ROCE_MODIFY_QP_VALID_MIN_RNR_NAK_TIMER ; 
 int /*<<< orphan*/  ECORE_ROCE_MODIFY_QP_VALID_PKEY ; 
 int /*<<< orphan*/  ECORE_ROCE_MODIFY_QP_VALID_RETRY_CNT ; 
 int /*<<< orphan*/  ECORE_ROCE_MODIFY_QP_VALID_RNR_RETRY_CNT ; 
 int /*<<< orphan*/  ECORE_ROCE_MODIFY_QP_VALID_ROCE_MODE ; 
 int /*<<< orphan*/  ECORE_ROCE_MODIFY_QP_VALID_RQ_PSN ; 
 int /*<<< orphan*/  ECORE_ROCE_MODIFY_QP_VALID_SQ_PSN ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_IWARP (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  OSAL_MEMCPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ecore_iwarp_modify_qp (struct ecore_hwfn*,struct ecore_rdma_qp*,int,int /*<<< orphan*/ ) ; 
 int ecore_roce2iwarp_state (int) ; 
 int ecore_roce_modify_qp (struct ecore_hwfn*,struct ecore_rdma_qp*,int,struct ecore_rdma_modify_qp_in_params*) ; 

enum _ecore_status_t ecore_rdma_modify_qp(
	void *rdma_cxt,
	struct ecore_rdma_qp *qp,
	struct ecore_rdma_modify_qp_in_params *params)
{
	struct ecore_hwfn *p_hwfn = (struct ecore_hwfn *)rdma_cxt;
	enum ecore_roce_qp_state prev_state;
	enum _ecore_status_t     rc = ECORE_SUCCESS;

	if (GET_FIELD(params->modify_flags,
		      ECORE_RDMA_MODIFY_QP_VALID_RDMA_OPS_EN))
	{
		qp->incoming_rdma_read_en = params->incoming_rdma_read_en;
		qp->incoming_rdma_write_en = params->incoming_rdma_write_en;
		qp->incoming_atomic_en = params->incoming_atomic_en;
	}

	/* Update QP structure with the updated values */
	if (GET_FIELD(params->modify_flags,
		      ECORE_ROCE_MODIFY_QP_VALID_ROCE_MODE))
	{
		qp->roce_mode = params->roce_mode;
	}
	if (GET_FIELD(params->modify_flags, ECORE_ROCE_MODIFY_QP_VALID_PKEY))
	{
		qp->pkey = params->pkey;
	}
	if (GET_FIELD(params->modify_flags,
		      ECORE_ROCE_MODIFY_QP_VALID_E2E_FLOW_CONTROL_EN))
	{
		qp->e2e_flow_control_en = params->e2e_flow_control_en;
	}
	if (GET_FIELD(params->modify_flags,
		      ECORE_ROCE_MODIFY_QP_VALID_DEST_QP))
	{
		qp->dest_qp = params->dest_qp;
	}
	if (GET_FIELD(params->modify_flags,
		      ECORE_ROCE_MODIFY_QP_VALID_ADDRESS_VECTOR))
	{
		/* Indicates that the following parameters have changed:
		 * Traffic class, flow label, hop limit, source GID,
		 * destination GID, loopback indicator
		 */
		qp->flow_label = params->flow_label;
		qp->hop_limit_ttl = params->hop_limit_ttl;

		qp->sgid = params->sgid;
		qp->dgid = params->dgid;
		qp->udp_src_port = params->udp_src_port;
		qp->vlan_id = params->vlan_id;
		qp->traffic_class_tos = params->traffic_class_tos;

		/* apply global override values */
		if (p_hwfn->p_rdma_info->glob_cfg.vlan_pri_en)
			SET_FIELD(qp->vlan_id, ECORE_RDMA_VLAN_PRIO,
				  p_hwfn->p_rdma_info->glob_cfg.vlan_pri);

		if (p_hwfn->p_rdma_info->glob_cfg.ecn_en)
			SET_FIELD(qp->traffic_class_tos, ECORE_RDMA_ECN,
				  p_hwfn->p_rdma_info->glob_cfg.ecn);

		if (p_hwfn->p_rdma_info->glob_cfg.dscp_en)
			SET_FIELD(qp->traffic_class_tos, ECORE_RDMA_DSCP,
				  p_hwfn->p_rdma_info->glob_cfg.dscp);

		qp->mtu = params->mtu;

		OSAL_MEMCPY((u8 *)&qp->remote_mac_addr[0],
			    (u8 *)&params->remote_mac_addr[0], ETH_ALEN);
		if (params->use_local_mac) {
			OSAL_MEMCPY((u8 *)&qp->local_mac_addr[0],
				    (u8 *)&params->local_mac_addr[0],
				    ETH_ALEN);
		} else {
			OSAL_MEMCPY((u8 *)&qp->local_mac_addr[0],
				    (u8 *)&p_hwfn->hw_info.hw_mac_addr,
				    ETH_ALEN);
		}
	}
	if (GET_FIELD(params->modify_flags, ECORE_ROCE_MODIFY_QP_VALID_RQ_PSN))
	{
		qp->rq_psn = params->rq_psn;
	}
	if (GET_FIELD(params->modify_flags, ECORE_ROCE_MODIFY_QP_VALID_SQ_PSN))
	{
		qp->sq_psn = params->sq_psn;
	}
	if (GET_FIELD(params->modify_flags,
		      ECORE_RDMA_MODIFY_QP_VALID_MAX_RD_ATOMIC_REQ))
	{
		qp->max_rd_atomic_req = params->max_rd_atomic_req;
	}
	if (GET_FIELD(params->modify_flags,
		      ECORE_RDMA_MODIFY_QP_VALID_MAX_RD_ATOMIC_RESP))
	{
		qp->max_rd_atomic_resp = params->max_rd_atomic_resp;
	}
	if (GET_FIELD(params->modify_flags,
		      ECORE_ROCE_MODIFY_QP_VALID_ACK_TIMEOUT))
	{
		qp->ack_timeout = params->ack_timeout;
	}
	if (GET_FIELD(params->modify_flags,
		      ECORE_ROCE_MODIFY_QP_VALID_RETRY_CNT))
	{
		qp->retry_cnt = params->retry_cnt;
	}
	if (GET_FIELD(params->modify_flags,
		      ECORE_ROCE_MODIFY_QP_VALID_RNR_RETRY_CNT))
	{
		qp->rnr_retry_cnt = params->rnr_retry_cnt;
	}
	if (GET_FIELD(params->modify_flags,
		      ECORE_ROCE_MODIFY_QP_VALID_MIN_RNR_NAK_TIMER))
	{
		qp->min_rnr_nak_timer = params->min_rnr_nak_timer;
	}

	qp->sqd_async = params->sqd_async;

	prev_state = qp->cur_state;
	if (GET_FIELD(params->modify_flags,
		      ECORE_RDMA_MODIFY_QP_VALID_NEW_STATE))
	{
		qp->cur_state = params->new_state;
		DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "qp->cur_state=%d\n",
			   qp->cur_state);
	}

	if (qp->qp_type == ECORE_RDMA_QP_TYPE_XRC_INI) {
		qp->has_req = 1;
	} else if (qp->qp_type == ECORE_RDMA_QP_TYPE_XRC_TGT)
	{
		qp->has_resp = 1;
	} else {
		qp->has_req = 1;
		qp->has_resp = 1;
	}

	if (IS_IWARP(p_hwfn)) {
		enum ecore_iwarp_qp_state new_state =
			ecore_roce2iwarp_state(qp->cur_state);

		rc = ecore_iwarp_modify_qp(p_hwfn, qp, new_state, 0);
	} else {
		rc = ecore_roce_modify_qp(p_hwfn, qp, prev_state, params);
	}

	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "Modify QP, rc = %d\n", rc);
	return rc;
}