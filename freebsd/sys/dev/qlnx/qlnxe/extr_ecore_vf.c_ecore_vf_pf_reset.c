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
struct vfpf_first_tlv {int dummy; } ;
struct TYPE_4__ {scalar_t__ status; } ;
struct pfvf_def_resp_tlv {TYPE_2__ hdr; } ;
struct ecore_vf_iov {TYPE_1__* pf2vf_reply; int /*<<< orphan*/  offset; } ;
struct ecore_hwfn {scalar_t__ b_int_enabled; struct ecore_vf_iov* vf_iov_info; } ;
struct channel_list_end_tlv {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_3__ {struct pfvf_def_resp_tlv default_resp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNEL_TLV_CLOSE ; 
 int /*<<< orphan*/  CHANNEL_TLV_LIST_END ; 
 int ECORE_AGAIN ; 
 scalar_t__ PFVF_STATUS_SUCCESS ; 
 int /*<<< orphan*/  ecore_add_tlv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int ecore_send_msg2pf (struct ecore_hwfn*,scalar_t__*,int) ; 
 struct vfpf_first_tlv* ecore_vf_pf_prep (struct ecore_hwfn*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ecore_vf_pf_req_end (struct ecore_hwfn*,int) ; 

enum _ecore_status_t ecore_vf_pf_reset(struct ecore_hwfn *p_hwfn)
{
	struct ecore_vf_iov *p_iov = p_hwfn->vf_iov_info;
	struct pfvf_def_resp_tlv *resp;
	struct vfpf_first_tlv *req;
	enum _ecore_status_t rc;

	/* clear mailbox and prep first tlv */
	req = ecore_vf_pf_prep(p_hwfn, CHANNEL_TLV_CLOSE, sizeof(*req));

	/* add list termination tlv */
	ecore_add_tlv(&p_iov->offset,
		      CHANNEL_TLV_LIST_END,
		      sizeof(struct channel_list_end_tlv));

	resp = &p_iov->pf2vf_reply->default_resp;
	rc = ecore_send_msg2pf(p_hwfn, &resp->hdr.status, sizeof(*resp));
	if (rc)
		goto exit;

	if (resp->hdr.status != PFVF_STATUS_SUCCESS) {
		rc = ECORE_AGAIN;
		goto exit;
	}

	p_hwfn->b_int_enabled = 0;

exit:
	ecore_vf_pf_req_end(p_hwfn, rc);

	return rc;
}