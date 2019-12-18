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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct vfpf_stop_rxqs_tlv {int num_rxqs; int /*<<< orphan*/  cqe_completion; int /*<<< orphan*/  rx_qid; } ;
struct pfvf_def_resp_tlv {int dummy; } ;
struct ecore_iov_vf_mbx {TYPE_1__* req_virt; } ;
struct ecore_vf_info {int /*<<< orphan*/  relative_vf_id; struct ecore_iov_vf_mbx vf_mbx; } ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_2__ {struct vfpf_stop_rxqs_tlv stop_rxqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNEL_TLV_STOP_RXQS ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ECORE_IOV_QID_INVALID ; 
 int /*<<< orphan*/  ECORE_MSG_IOV ; 
 int ECORE_SUCCESS ; 
 scalar_t__ PFVF_STATUS_FAILURE ; 
 scalar_t__ PFVF_STATUS_NOT_SUPPORTED ; 
 scalar_t__ PFVF_STATUS_SUCCESS ; 
 int /*<<< orphan*/  ecore_iov_prepare_resp (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_vf_info*,int /*<<< orphan*/ ,int,scalar_t__) ; 
 scalar_t__ ecore_iov_vf_mbx_qid (struct ecore_hwfn*,struct ecore_vf_info*,int) ; 
 int ecore_iov_vf_stop_rxqs (struct ecore_hwfn*,struct ecore_vf_info*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ecore_iov_vf_mbx_stop_rxqs(struct ecore_hwfn *p_hwfn,
				       struct ecore_ptt *p_ptt,
				       struct ecore_vf_info *vf)
{
	u16 length = sizeof(struct pfvf_def_resp_tlv);
	struct ecore_iov_vf_mbx *mbx = &vf->vf_mbx;
	u8 status = PFVF_STATUS_FAILURE;
	struct vfpf_stop_rxqs_tlv *req;
	u8 qid_usage_idx;
	enum _ecore_status_t rc;

	/* Starting with CHANNEL_TLV_QID, it's assumed the 'num_rxqs'
	 * would be one. Since no older ecore passed multiple queues
	 * using this API, sanitize on the value.
	 */
	req = &mbx->req_virt->stop_rxqs;
	if (req->num_rxqs != 1) {
		DP_VERBOSE(p_hwfn, ECORE_MSG_IOV,
			   "Odd; VF[%d] tried stopping multiple Rx queues\n",
			   vf->relative_vf_id);
		status = PFVF_STATUS_NOT_SUPPORTED;
		goto out;
	}

	/* Find which qid-index is associated with the queue */
	qid_usage_idx = ecore_iov_vf_mbx_qid(p_hwfn, vf, false);
	if (qid_usage_idx == ECORE_IOV_QID_INVALID)
		goto out;

	rc = ecore_iov_vf_stop_rxqs(p_hwfn, vf, req->rx_qid,
				    qid_usage_idx, req->cqe_completion);
	if (rc == ECORE_SUCCESS)
		status = PFVF_STATUS_SUCCESS;
out:
	ecore_iov_prepare_resp(p_hwfn, p_ptt, vf, CHANNEL_TLV_STOP_RXQS,
			       length, status);
}