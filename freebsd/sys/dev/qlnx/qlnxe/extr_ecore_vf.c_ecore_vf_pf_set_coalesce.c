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
typedef  void* u16 ;
struct vfpf_update_coalesce {int /*<<< orphan*/  qid; void* tx_coal; void* rx_coal; } ;
struct TYPE_7__ {scalar_t__ status; } ;
struct pfvf_def_resp_tlv {TYPE_3__ hdr; } ;
struct ecore_vf_iov {TYPE_2__* pf2vf_reply; int /*<<< orphan*/  offset; } ;
struct TYPE_5__ {int /*<<< orphan*/  queue_id; } ;
struct ecore_queue_cid {TYPE_1__ rel; } ;
struct ecore_hwfn {TYPE_4__* p_dev; struct ecore_vf_iov* vf_iov_info; } ;
struct channel_list_end_tlv {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_8__ {void* tx_coalesce_usecs; void* rx_coalesce_usecs; } ;
struct TYPE_6__ {struct pfvf_def_resp_tlv default_resp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNEL_TLV_COALESCE_UPDATE ; 
 int /*<<< orphan*/  CHANNEL_TLV_LIST_END ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECORE_MSG_IOV ; 
 int ECORE_SUCCESS ; 
 scalar_t__ PFVF_STATUS_SUCCESS ; 
 int /*<<< orphan*/  ecore_add_tlv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int ecore_send_msg2pf (struct ecore_hwfn*,scalar_t__*,int) ; 
 struct vfpf_update_coalesce* ecore_vf_pf_prep (struct ecore_hwfn*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ecore_vf_pf_req_end (struct ecore_hwfn*,int) ; 

enum _ecore_status_t
ecore_vf_pf_set_coalesce(struct ecore_hwfn *p_hwfn, u16 rx_coal, u16 tx_coal,
			 struct ecore_queue_cid     *p_cid)
{
	struct ecore_vf_iov *p_iov = p_hwfn->vf_iov_info;
	struct vfpf_update_coalesce *req;
	struct pfvf_def_resp_tlv *resp;
	enum _ecore_status_t rc;

	/* clear mailbox and prep header tlv */
	req = ecore_vf_pf_prep(p_hwfn, CHANNEL_TLV_COALESCE_UPDATE,
			       sizeof(*req));

	req->rx_coal = rx_coal;
	req->tx_coal = tx_coal;
	req->qid = p_cid->rel.queue_id;

	DP_VERBOSE(p_hwfn, ECORE_MSG_IOV,
		   "Setting coalesce rx_coal = %d, tx_coal = %d at queue = %d\n",
		   rx_coal, tx_coal, req->qid);

	/* add list termination tlv */
	ecore_add_tlv(&p_iov->offset, CHANNEL_TLV_LIST_END,
		      sizeof(struct channel_list_end_tlv));

	resp = &p_iov->pf2vf_reply->default_resp;
	rc = ecore_send_msg2pf(p_hwfn, &resp->hdr.status, sizeof(*resp));

	if (rc != ECORE_SUCCESS)
		goto exit;

	if (resp->hdr.status != PFVF_STATUS_SUCCESS)
		goto exit;

	p_hwfn->p_dev->rx_coalesce_usecs = rx_coal;
	p_hwfn->p_dev->tx_coalesce_usecs = tx_coal;

exit:
	ecore_vf_pf_req_end(p_hwfn, rc);
	return rc;
}