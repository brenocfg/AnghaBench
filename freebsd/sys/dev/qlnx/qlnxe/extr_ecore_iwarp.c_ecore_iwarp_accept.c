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
typedef  int u8 ;
struct TYPE_8__ {scalar_t__ ird; scalar_t__ ord; int private_data_len; scalar_t__ private_data; } ;
struct ecore_iwarp_ep {scalar_t__ mpa_rev; int rtr_type; scalar_t__ state; int /*<<< orphan*/  tcp_cid; TYPE_4__* ep_buffer_virt; TYPE_3__ cm_info; TYPE_5__* qp; int /*<<< orphan*/  cb_context; struct ecore_iwarp_ep* listener; } ;
struct ecore_iwarp_accept_in {scalar_t__ ord; int ird; int private_data_len; TYPE_5__* qp; int /*<<< orphan*/  private_data; int /*<<< orphan*/  cb_context; scalar_t__ ep_context; } ;
struct ecore_hwfn {TYPE_2__* p_rdma_info; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_10__ {struct ecore_iwarp_ep* ep; int /*<<< orphan*/  icid; } ;
struct TYPE_9__ {scalar_t__ out_pdata; } ;
struct TYPE_6__ {int /*<<< orphan*/  ep_list; } ;
struct TYPE_7__ {TYPE_1__ iwarp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct ecore_hwfn*,char*) ; 
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,...) ; 
 int ECORE_CONN_RESET ; 
 int ECORE_INVAL ; 
 scalar_t__ ECORE_IWARP_EP_CLOSED ; 
 int /*<<< orphan*/  ECORE_IWARP_INVALID_TCP_CID ; 
 int ECORE_IWARP_IRD_DEFAULT ; 
 scalar_t__ ECORE_IWARP_ORD_DEFAULT ; 
 int /*<<< orphan*/  ECORE_IWARP_QP_STATE_ERROR ; 
 int /*<<< orphan*/  ECORE_MSG_RDMA ; 
 scalar_t__ MPA_NEGOTIATION_TYPE_ENHANCED ; 
 int MPA_RTR_TYPE_ZERO_READ ; 
 int /*<<< orphan*/  OSAL_MEMCPY (int*,int /*<<< orphan*/ ,int) ; 
 struct ecore_iwarp_ep* OSAL_NULL ; 
 int /*<<< orphan*/  ecore_iwarp_modify_qp (struct ecore_hwfn*,TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ecore_iwarp_move_to_ep_list (struct ecore_hwfn*,int /*<<< orphan*/ *,struct ecore_iwarp_ep*) ; 
 int ecore_iwarp_mpa_offload (struct ecore_hwfn*,struct ecore_iwarp_ep*) ; 
 int /*<<< orphan*/  ecore_iwarp_mpa_v2_set_private (struct ecore_hwfn*,struct ecore_iwarp_ep*,int*) ; 
 int /*<<< orphan*/  ecore_iwarp_prealloc_ep (struct ecore_hwfn*,int) ; 
 int /*<<< orphan*/  ecore_iwarp_return_ep (struct ecore_hwfn*,struct ecore_iwarp_ep*) ; 

enum _ecore_status_t
ecore_iwarp_accept(void *rdma_cxt,
		   struct ecore_iwarp_accept_in *iparams)
{
	struct ecore_hwfn *p_hwfn = (struct ecore_hwfn *)rdma_cxt;
	struct ecore_iwarp_ep *ep;
	u8 mpa_data_size = 0;
	enum _ecore_status_t rc;

	ep = (struct ecore_iwarp_ep *)iparams->ep_context;
	if (!ep) {
		DP_ERR(p_hwfn, "Ep Context receive in accept is NULL\n");
		return ECORE_INVAL;
	}

	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "QP(0x%x) EP(0x%x)\n",
		   iparams->qp->icid, ep->tcp_cid);

	if ((iparams->ord > ECORE_IWARP_ORD_DEFAULT) ||
	    (iparams->ird > ECORE_IWARP_IRD_DEFAULT)) {
		DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA,
			   "QP(0x%x) EP(0x%x) ERROR: Invalid ord(0x%x)/ird(0x%x)\n",
			   iparams->qp->icid, ep->tcp_cid,
			   iparams->ord, iparams->ord);
		return ECORE_INVAL;
	}

	/* We could reach qp->ep != OSAL NULL if we do accept on the same qp */
	if (iparams->qp->ep == OSAL_NULL) {
		/* We need to add a replacement for the ep to the free list */
		ecore_iwarp_prealloc_ep(p_hwfn, false);
	} else {
		DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA,
			   "Note re-use of QP for different connect\n");
		/* Return the old ep to the free_pool */
		ecore_iwarp_return_ep(p_hwfn, iparams->qp->ep);
	}

	ecore_iwarp_move_to_ep_list(p_hwfn,
				    &p_hwfn->p_rdma_info->iwarp.ep_list,
				    ep);
	ep->listener = OSAL_NULL;
	ep->cb_context = iparams->cb_context;
	ep->qp = iparams->qp;
	ep->qp->ep = ep;

	if (ep->mpa_rev == MPA_NEGOTIATION_TYPE_ENHANCED) {
		/* Negotiate ord/ird: if upperlayer requested ord larger than
		 * ird advertised by remote, we need to decrease our ord
		 * to match remote ord
		 */
		if (iparams->ord > ep->cm_info.ird) {
			iparams->ord = ep->cm_info.ird;
		}

		/* For chelsio compatability, if rtr_zero read is requested
		 * we can't set ird to zero
		 */
		if ((ep->rtr_type & MPA_RTR_TYPE_ZERO_READ) &&
		    (iparams->ird == 0))
			iparams->ird = 1;
	}

	/* Update cm_info ord/ird to be negotiated values */
	ep->cm_info.ord = iparams->ord;
	ep->cm_info.ird = iparams->ird;

	ecore_iwarp_mpa_v2_set_private(p_hwfn, ep, &mpa_data_size);

	ep->cm_info.private_data = ep->ep_buffer_virt->out_pdata;
	ep->cm_info.private_data_len =
		iparams->private_data_len + mpa_data_size;

	OSAL_MEMCPY((u8 *)ep->ep_buffer_virt->out_pdata + mpa_data_size,
		    iparams->private_data,
		    iparams->private_data_len);

	if (ep->state == ECORE_IWARP_EP_CLOSED) {
		DP_NOTICE(p_hwfn, false,
			  "(0x%x) Accept called on EP in CLOSED state\n",
			  ep->tcp_cid);
		ep->tcp_cid = ECORE_IWARP_INVALID_TCP_CID;
		ecore_iwarp_return_ep(p_hwfn, ep);
		return ECORE_CONN_RESET;
	}

	rc = ecore_iwarp_mpa_offload(p_hwfn, ep);
	if (rc) {
		ecore_iwarp_modify_qp(p_hwfn,
				      iparams->qp,
				      ECORE_IWARP_QP_STATE_ERROR,
				      1);
	}

	return rc;
}