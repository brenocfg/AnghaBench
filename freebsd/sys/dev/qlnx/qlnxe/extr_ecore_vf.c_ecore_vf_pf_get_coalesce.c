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
typedef  int /*<<< orphan*/  u16 ;
struct vfpf_read_coal_req_tlv {int is_rx; int /*<<< orphan*/  qid; } ;
struct TYPE_6__ {scalar_t__ status; } ;
struct pfvf_read_coal_resp_tlv {int /*<<< orphan*/  coal; TYPE_3__ hdr; } ;
struct ecore_vf_iov {TYPE_2__* pf2vf_reply; int /*<<< orphan*/  offset; } ;
struct TYPE_4__ {int /*<<< orphan*/  queue_id; } ;
struct ecore_queue_cid {scalar_t__ b_is_rx; TYPE_1__ rel; } ;
struct ecore_hwfn {struct ecore_vf_iov* vf_iov_info; } ;
struct channel_list_end_tlv {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_5__ {struct pfvf_read_coal_resp_tlv read_coal_resp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNEL_TLV_COALESCE_READ ; 
 int /*<<< orphan*/  CHANNEL_TLV_LIST_END ; 
 int ECORE_SUCCESS ; 
 scalar_t__ PFVF_STATUS_SUCCESS ; 
 int /*<<< orphan*/  ecore_add_tlv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int ecore_send_msg2pf (struct ecore_hwfn*,scalar_t__*,int) ; 
 struct vfpf_read_coal_req_tlv* ecore_vf_pf_prep (struct ecore_hwfn*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ecore_vf_pf_req_end (struct ecore_hwfn*,int) ; 

enum _ecore_status_t ecore_vf_pf_get_coalesce(struct ecore_hwfn *p_hwfn,
					      u16 *p_coal,
					      struct ecore_queue_cid *p_cid)
{
	struct ecore_vf_iov *p_iov = p_hwfn->vf_iov_info;
	struct pfvf_read_coal_resp_tlv *resp;
	struct vfpf_read_coal_req_tlv *req;
	enum _ecore_status_t rc;

	/* clear mailbox and prep header tlv */
	req = ecore_vf_pf_prep(p_hwfn, CHANNEL_TLV_COALESCE_READ,
			       sizeof(*req));
	req->qid = p_cid->rel.queue_id;
	req->is_rx = p_cid->b_is_rx ? 1 : 0;

	ecore_add_tlv(&p_iov->offset, CHANNEL_TLV_LIST_END,
		      sizeof(struct channel_list_end_tlv));
	resp = &p_iov->pf2vf_reply->read_coal_resp;

	rc = ecore_send_msg2pf(p_hwfn, &resp->hdr.status, sizeof(*resp));
	if (rc != ECORE_SUCCESS)
		goto exit;

	if (resp->hdr.status != PFVF_STATUS_SUCCESS)
		goto exit;

	*p_coal = resp->coal;
exit:
	ecore_vf_pf_req_end(p_hwfn, rc);

	return rc;
}