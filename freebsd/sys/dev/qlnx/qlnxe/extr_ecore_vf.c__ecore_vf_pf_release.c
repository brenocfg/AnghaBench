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
typedef  union vfpf_tlvs {int dummy; } vfpf_tlvs ;
typedef  union pfvf_tlvs {int dummy; } pfvf_tlvs ;
typedef  int u32 ;
struct vfpf_first_tlv {int dummy; } ;
struct TYPE_4__ {scalar_t__ status; } ;
struct pfvf_def_resp_tlv {TYPE_1__ hdr; } ;
struct TYPE_5__ {int /*<<< orphan*/  phys; TYPE_3__* p_virt; } ;
struct ecore_vf_iov {int /*<<< orphan*/  mutex; TYPE_2__ bulletin; int /*<<< orphan*/  pf2vf_reply_phys; TYPE_3__* pf2vf_reply; int /*<<< orphan*/  vf2pf_request_phys; TYPE_3__* vf2pf_request; int /*<<< orphan*/  offset; } ;
struct ecore_hwfn {struct ecore_vf_iov* vf_iov_info; int /*<<< orphan*/  p_dev; scalar_t__ b_int_enabled; } ;
struct ecore_bulletin_content {int dummy; } ;
struct channel_list_end_tlv {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_6__ {struct pfvf_def_resp_tlv default_resp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNEL_TLV_LIST_END ; 
 int /*<<< orphan*/  CHANNEL_TLV_RELEASE ; 
 int ECORE_AGAIN ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  OSAL_DMA_FREE_COHERENT (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OSAL_FREE (int /*<<< orphan*/ ,struct ecore_vf_iov*) ; 
 int /*<<< orphan*/  OSAL_MUTEX_DEALLOC (int /*<<< orphan*/ *) ; 
 struct ecore_vf_iov* OSAL_NULL ; 
 scalar_t__ PFVF_STATUS_SUCCESS ; 
 int /*<<< orphan*/  ecore_add_tlv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int ecore_send_msg2pf (struct ecore_hwfn*,scalar_t__*,int) ; 
 struct vfpf_first_tlv* ecore_vf_pf_prep (struct ecore_hwfn*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ecore_vf_pf_req_end (struct ecore_hwfn*,int) ; 

__attribute__((used)) static enum _ecore_status_t _ecore_vf_pf_release(struct ecore_hwfn *p_hwfn,
					  bool b_final)
{
	struct ecore_vf_iov *p_iov = p_hwfn->vf_iov_info;
	struct pfvf_def_resp_tlv *resp;
	struct vfpf_first_tlv *req;
	u32 size;
	enum _ecore_status_t rc;

	/* clear mailbox and prep first tlv */
	req = ecore_vf_pf_prep(p_hwfn, CHANNEL_TLV_RELEASE, sizeof(*req));

	/* add list termination tlv */
	ecore_add_tlv(&p_iov->offset,
		      CHANNEL_TLV_LIST_END,
		      sizeof(struct channel_list_end_tlv));

	resp = &p_iov->pf2vf_reply->default_resp;
	rc = ecore_send_msg2pf(p_hwfn, &resp->hdr.status, sizeof(*resp));

	if (rc == ECORE_SUCCESS && resp->hdr.status != PFVF_STATUS_SUCCESS)
		rc = ECORE_AGAIN;

	ecore_vf_pf_req_end(p_hwfn, rc);
	if (!b_final)
		return rc;

	p_hwfn->b_int_enabled = 0;

	if (p_iov->vf2pf_request)
		OSAL_DMA_FREE_COHERENT(p_hwfn->p_dev,
				       p_iov->vf2pf_request,
				       p_iov->vf2pf_request_phys,
				       sizeof(union vfpf_tlvs));
	if (p_iov->pf2vf_reply)
		OSAL_DMA_FREE_COHERENT(p_hwfn->p_dev,
				       p_iov->pf2vf_reply,
				       p_iov->pf2vf_reply_phys,
				       sizeof(union pfvf_tlvs));

	if (p_iov->bulletin.p_virt) {
		size = sizeof(struct ecore_bulletin_content);
		OSAL_DMA_FREE_COHERENT(p_hwfn->p_dev,
				       p_iov->bulletin.p_virt,
				       p_iov->bulletin.phys,
				       size);
	}

#ifdef CONFIG_ECORE_LOCK_ALLOC
	OSAL_MUTEX_DEALLOC(&p_iov->mutex);
#endif

	OSAL_FREE(p_hwfn->p_dev, p_hwfn->vf_iov_info);
	p_hwfn->vf_iov_info = OSAL_NULL;

	return rc;
}