#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  size_t u16 ;
struct vfpf_update_rxq_tlv {int flags; int num_rxqs; size_t rx_qid; } ;
struct pfvf_def_resp_tlv {int dummy; } ;
struct TYPE_7__ {int capabilities; } ;
struct TYPE_8__ {TYPE_2__ vfdev_info; } ;
struct ecore_iov_vf_mbx {TYPE_1__* req_virt; } ;
struct ecore_vf_info {TYPE_5__* vf_queues; int /*<<< orphan*/  relative_vf_id; TYPE_3__ acquire; struct ecore_iov_vf_mbx vf_mbx; } ;
struct ecore_queue_cid {int dummy; } ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_10__ {TYPE_4__* cids; } ;
struct TYPE_9__ {struct ecore_queue_cid* p_cid; scalar_t__ b_is_tx; } ;
struct TYPE_6__ {struct vfpf_update_rxq_tlv update_rxq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNEL_TLV_UPDATE_RXQ ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 size_t ECORE_IOV_QID_INVALID ; 
 int /*<<< orphan*/  ECORE_IOV_VALIDATE_Q_NA ; 
 int ECORE_MAX_VF_CHAINS_PER_PF ; 
 int /*<<< orphan*/  ECORE_MSG_IOV ; 
 int /*<<< orphan*/  ECORE_SPQ_MODE_EBLOCK ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  OSAL_NULL ; 
 size_t PFVF_STATUS_FAILURE ; 
 size_t PFVF_STATUS_SUCCESS ; 
 int VFPF_ACQUIRE_CAP_QUEUE_QIDS ; 
 int VFPF_RXQ_UPD_COMPLETE_CQE_FLAG ; 
 int VFPF_RXQ_UPD_COMPLETE_EVENT_FLAG ; 
 int /*<<< orphan*/  ecore_iov_prepare_resp (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_vf_info*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  ecore_iov_validate_rxq (struct ecore_hwfn*,struct ecore_vf_info*,size_t,int /*<<< orphan*/ ) ; 
 size_t ecore_iov_vf_mbx_qid (struct ecore_hwfn*,struct ecore_vf_info*,int) ; 
 int ecore_sp_eth_rx_queues_update (struct ecore_hwfn*,void**,size_t,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ecore_iov_vf_mbx_update_rxqs(struct ecore_hwfn *p_hwfn,
					 struct ecore_ptt *p_ptt,
					 struct ecore_vf_info *vf)
{
	struct ecore_queue_cid *handlers[ECORE_MAX_VF_CHAINS_PER_PF];
	u16 length = sizeof(struct pfvf_def_resp_tlv);
	struct ecore_iov_vf_mbx *mbx = &vf->vf_mbx;
	struct vfpf_update_rxq_tlv *req;
	u8 status = PFVF_STATUS_FAILURE;
	u8 complete_event_flg;
	u8 complete_cqe_flg;
	u8 qid_usage_idx;
	enum _ecore_status_t rc;
	u16 i;

	req = &mbx->req_virt->update_rxq;
	complete_cqe_flg = !!(req->flags & VFPF_RXQ_UPD_COMPLETE_CQE_FLAG);
	complete_event_flg = !!(req->flags & VFPF_RXQ_UPD_COMPLETE_EVENT_FLAG);

	qid_usage_idx = ecore_iov_vf_mbx_qid(p_hwfn, vf, false);
	if (qid_usage_idx == ECORE_IOV_QID_INVALID)
		goto out;

	/* Starting with the addition of CHANNEL_TLV_QID, this API started
	 * expecting a single queue at a time. Validate this.
	 */
	if ((vf->acquire.vfdev_info.capabilities &
	     VFPF_ACQUIRE_CAP_QUEUE_QIDS) &&
	     req->num_rxqs != 1) {
		DP_VERBOSE(p_hwfn, ECORE_MSG_IOV,
			   "VF[%d] supports QIDs but sends multiple queues\n",
			   vf->relative_vf_id);
		goto out;
	}

	/* Validate inputs - for the legacy case this is still true since
	 * qid_usage_idx for each Rx queue would be LEGACY_QID_RX.
	 */
	for (i = req->rx_qid; i < req->rx_qid + req->num_rxqs; i++) {
		if (!ecore_iov_validate_rxq(p_hwfn, vf, i,
					    ECORE_IOV_VALIDATE_Q_NA) ||
		    !vf->vf_queues[i].cids[qid_usage_idx].p_cid ||
		    vf->vf_queues[i].cids[qid_usage_idx].b_is_tx) {
			DP_VERBOSE(p_hwfn, ECORE_MSG_IOV,
				   "VF[%d]: Incorrect Rxqs [%04x, %02x]\n",
				   vf->relative_vf_id, req->rx_qid,
				   req->num_rxqs);
			goto out;
		}
	}

	for (i = 0; i < req->num_rxqs; i++) {
		u16 qid = req->rx_qid + i;

		handlers[i] = vf->vf_queues[qid].cids[qid_usage_idx].p_cid;
	}

	rc = ecore_sp_eth_rx_queues_update(p_hwfn, (void **)&handlers,
					   req->num_rxqs,
					   complete_cqe_flg,
					   complete_event_flg,
					   ECORE_SPQ_MODE_EBLOCK,
					   OSAL_NULL);
	if (rc != ECORE_SUCCESS)
		goto out;

	status = PFVF_STATUS_SUCCESS;
out:
	ecore_iov_prepare_resp(p_hwfn, p_ptt, vf, CHANNEL_TLV_UPDATE_RXQ,
			       length, status);
}