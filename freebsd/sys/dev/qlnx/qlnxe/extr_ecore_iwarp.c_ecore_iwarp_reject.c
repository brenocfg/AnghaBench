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
typedef  int u8 ;
struct ecore_iwarp_reject_in {int private_data_len; int /*<<< orphan*/  private_data; int /*<<< orphan*/  cb_context; scalar_t__ ep_context; } ;
struct TYPE_3__ {int private_data_len; scalar_t__ private_data; } ;
struct ecore_iwarp_ep {scalar_t__ state; int /*<<< orphan*/  tcp_cid; TYPE_2__* ep_buffer_virt; TYPE_1__ cm_info; int /*<<< orphan*/  qp; int /*<<< orphan*/  cb_context; } ;
struct ecore_hwfn {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_4__ {scalar_t__ out_pdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct ecore_hwfn*,char*) ; 
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int ECORE_CONN_RESET ; 
 int ECORE_INVAL ; 
 scalar_t__ ECORE_IWARP_EP_CLOSED ; 
 int /*<<< orphan*/  ECORE_IWARP_INVALID_TCP_CID ; 
 int /*<<< orphan*/  ECORE_MSG_RDMA ; 
 int /*<<< orphan*/  OSAL_MEMCPY (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OSAL_NULL ; 
 int ecore_iwarp_mpa_offload (struct ecore_hwfn*,struct ecore_iwarp_ep*) ; 
 int /*<<< orphan*/  ecore_iwarp_mpa_v2_set_private (struct ecore_hwfn*,struct ecore_iwarp_ep*,int*) ; 
 int /*<<< orphan*/  ecore_iwarp_return_ep (struct ecore_hwfn*,struct ecore_iwarp_ep*) ; 

enum _ecore_status_t
ecore_iwarp_reject(void *rdma_cxt,
		   struct ecore_iwarp_reject_in *iparams)
{
	struct ecore_hwfn *p_hwfn = (struct ecore_hwfn *)rdma_cxt;
	struct ecore_iwarp_ep *ep;
	u8 mpa_data_size = 0;
	enum _ecore_status_t rc;

	ep = (struct ecore_iwarp_ep *)iparams->ep_context;
	if (!ep) {
		DP_ERR(p_hwfn, "Ep Context receive in reject is NULL\n");
		return ECORE_INVAL;
	}

	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "EP(0x%x)\n", ep->tcp_cid);

	ep->cb_context = iparams->cb_context;
	ep->qp = OSAL_NULL;

	ecore_iwarp_mpa_v2_set_private(p_hwfn, ep, &mpa_data_size);

	ep->cm_info.private_data = ep->ep_buffer_virt->out_pdata;
	ep->cm_info.private_data_len =
		iparams->private_data_len + mpa_data_size;

	OSAL_MEMCPY((u8 *)ep->ep_buffer_virt->out_pdata + mpa_data_size,
		    iparams->private_data,
		    iparams->private_data_len);

	if (ep->state == ECORE_IWARP_EP_CLOSED) {
		DP_NOTICE(p_hwfn, false,
			  "(0x%x) Reject called on EP in CLOSED state\n",
			  ep->tcp_cid);
		ep->tcp_cid = ECORE_IWARP_INVALID_TCP_CID;
		ecore_iwarp_return_ep(p_hwfn, ep);
		return ECORE_CONN_RESET;
	}

	rc = ecore_iwarp_mpa_offload(p_hwfn, ep);
	return rc;
}