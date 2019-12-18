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
typedef  int /*<<< orphan*/  vf_params ;
typedef  size_t u8 ;
struct vfpf_start_rxq_tlv {size_t rx_qid; int /*<<< orphan*/  cqe_pbl_size; int /*<<< orphan*/  cqe_pbl_addr; int /*<<< orphan*/  rxq_addr; int /*<<< orphan*/  bd_max_bytes; int /*<<< orphan*/  sb_index; int /*<<< orphan*/  hw_sb; } ;
struct ecore_vf_queue {TYPE_2__* cids; scalar_t__ fw_rx_qid; } ;
struct ecore_iov_vf_mbx {TYPE_1__* req_virt; } ;
struct ecore_vf_info {int /*<<< orphan*/  num_active_rxqs; scalar_t__ abs_vf_id; int /*<<< orphan*/  opaque_fid; int /*<<< orphan*/  relative_vf_id; int /*<<< orphan*/  vport_id; struct ecore_vf_queue* vf_queues; struct ecore_iov_vf_mbx vf_mbx; } ;
struct ecore_sb_info {size_t vf_qid; size_t vf_legacy; size_t qid_usage_idx; int /*<<< orphan*/  vfid; int /*<<< orphan*/  igu_sb_id; } ;
struct ecore_queue_start_common_params {size_t queue_id; int /*<<< orphan*/  sb_idx; struct ecore_sb_info* p_sb; scalar_t__ stats_id; int /*<<< orphan*/  vport_id; } ;
struct ecore_queue_cid_vf_params {size_t vf_qid; size_t vf_legacy; size_t qid_usage_idx; int /*<<< orphan*/  vfid; int /*<<< orphan*/  igu_sb_id; } ;
struct ecore_queue_cid {int dummy; } ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
typedef  int /*<<< orphan*/  sb_dummy ;
typedef  int /*<<< orphan*/  params ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_4__ {int b_is_tx; struct ecore_queue_cid* p_cid; } ;
struct TYPE_3__ {struct vfpf_start_rxq_tlv start_rxq; } ;

/* Variables and functions */
 size_t ECORE_IOV_QID_INVALID ; 
 int /*<<< orphan*/  ECORE_IOV_VALIDATE_Q_DISABLE ; 
 size_t ECORE_QCID_LEGACY_VF_RX_PROD ; 
 int ECORE_SUCCESS ; 
 scalar_t__ GTT_BAR0_MAP_REG_MSDM_RAM ; 
 scalar_t__ MSTORM_ETH_VF_PRODS_OFFSET (scalar_t__,size_t) ; 
 int /*<<< orphan*/  OSAL_MEMSET (struct ecore_queue_start_common_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OSAL_MEM_ZERO (struct ecore_sb_info*,int) ; 
 struct ecore_queue_cid* OSAL_NULL ; 
 size_t PFVF_STATUS_FAILURE ; 
 size_t PFVF_STATUS_NO_RESOURCE ; 
 size_t PFVF_STATUS_SUCCESS ; 
 int /*<<< orphan*/  REG_WR (struct ecore_hwfn*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_eth_queue_cid_release (struct ecore_hwfn*,struct ecore_queue_cid*) ; 
 struct ecore_queue_cid* ecore_eth_queue_to_cid (struct ecore_hwfn*,int /*<<< orphan*/ ,struct ecore_queue_start_common_params*,int,struct ecore_sb_info*) ; 
 int ecore_eth_rxq_start_ramrod (struct ecore_hwfn*,struct ecore_queue_cid*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_iov_validate_rxq (struct ecore_hwfn*,struct ecore_vf_info*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_iov_validate_sb (struct ecore_hwfn*,struct ecore_vf_info*,int /*<<< orphan*/ ) ; 
 size_t ecore_iov_vf_mbx_qid (struct ecore_hwfn*,struct ecore_vf_info*,int) ; 
 int /*<<< orphan*/  ecore_iov_vf_mbx_start_rxq_resp (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_vf_info*,size_t,int) ; 
 size_t ecore_vf_calculate_legacy (struct ecore_vf_info*) ; 

__attribute__((used)) static void ecore_iov_vf_mbx_start_rxq(struct ecore_hwfn *p_hwfn,
				       struct ecore_ptt *p_ptt,
				       struct ecore_vf_info *vf)
{
	struct ecore_queue_start_common_params params;
	struct ecore_queue_cid_vf_params vf_params;
	struct ecore_iov_vf_mbx *mbx = &vf->vf_mbx;
	u8 status = PFVF_STATUS_NO_RESOURCE;
	u8 qid_usage_idx, vf_legacy = 0;
	struct ecore_vf_queue *p_queue;
	struct vfpf_start_rxq_tlv *req;
	struct ecore_queue_cid *p_cid;
	struct ecore_sb_info sb_dummy;
	enum _ecore_status_t rc;

	req = &mbx->req_virt->start_rxq;

	if (!ecore_iov_validate_rxq(p_hwfn, vf, req->rx_qid,
				    ECORE_IOV_VALIDATE_Q_DISABLE) ||
	    !ecore_iov_validate_sb(p_hwfn, vf, req->hw_sb))
		goto out;

	qid_usage_idx = ecore_iov_vf_mbx_qid(p_hwfn, vf, false);
	if (qid_usage_idx == ECORE_IOV_QID_INVALID)
		goto out;

	p_queue = &vf->vf_queues[req->rx_qid];
	if (p_queue->cids[qid_usage_idx].p_cid)
		goto out;

	vf_legacy = ecore_vf_calculate_legacy(vf);

	/* Acquire a new queue-cid */
	OSAL_MEMSET(&params, 0, sizeof(params));
	params.queue_id = (u8)p_queue->fw_rx_qid;
	params.vport_id = vf->vport_id;
	params.stats_id = vf->abs_vf_id + 0x10;

	/* Since IGU index is passed via sb_info, construct a dummy one */
	OSAL_MEM_ZERO(&sb_dummy, sizeof(sb_dummy));
	sb_dummy.igu_sb_id = req->hw_sb;
	params.p_sb = &sb_dummy;
	params.sb_idx = req->sb_index;

	OSAL_MEM_ZERO(&vf_params, sizeof(vf_params));
	vf_params.vfid = vf->relative_vf_id;
	vf_params.vf_qid = (u8)req->rx_qid;
	vf_params.vf_legacy = vf_legacy;
	vf_params.qid_usage_idx = qid_usage_idx;

	p_cid = ecore_eth_queue_to_cid(p_hwfn, vf->opaque_fid,
				       &params, true, &vf_params);
	if (p_cid == OSAL_NULL)
		goto out;

	/* Legacy VFs have their Producers in a different location, which they
	 * calculate on their own and clean the producer prior to this.
	 */
	if (!(vf_legacy & ECORE_QCID_LEGACY_VF_RX_PROD))
		REG_WR(p_hwfn,
		       GTT_BAR0_MAP_REG_MSDM_RAM +
		       MSTORM_ETH_VF_PRODS_OFFSET(vf->abs_vf_id, req->rx_qid),
		       0);

	rc = ecore_eth_rxq_start_ramrod(p_hwfn, p_cid,
					req->bd_max_bytes,
					req->rxq_addr,
					req->cqe_pbl_addr,
					req->cqe_pbl_size);
	if (rc != ECORE_SUCCESS) {
		status = PFVF_STATUS_FAILURE;
		ecore_eth_queue_cid_release(p_hwfn, p_cid);
	} else {
		p_queue->cids[qid_usage_idx].p_cid = p_cid;
		p_queue->cids[qid_usage_idx].b_is_tx = false;
		status = PFVF_STATUS_SUCCESS;
		vf->num_active_rxqs++;
	}

out:
	ecore_iov_vf_mbx_start_rxq_resp(p_hwfn, p_ptt, vf, status,
					!!(vf_legacy &
					   ECORE_QCID_LEGACY_VF_RX_PROD));
}