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
struct ecore_iwarp_ep {scalar_t__ connect_mode; int /*<<< orphan*/  list_entry; int /*<<< orphan*/  cb_context; int /*<<< orphan*/  (* event_cb ) (int /*<<< orphan*/ ,struct ecore_iwarp_cm_event_params*) ;int /*<<< orphan*/  tcp_cid; int /*<<< orphan*/  state; int /*<<< orphan*/  cm_info; } ;
struct ecore_iwarp_cm_event_params {void* status; int /*<<< orphan*/ * cm_info; struct ecore_iwarp_ep* ep_context; int /*<<< orphan*/  event; } ;
struct ecore_hwfn {TYPE_2__* p_rdma_info; } ;
typedef  int /*<<< orphan*/  params ;
struct TYPE_3__ {int /*<<< orphan*/  iw_lock; int /*<<< orphan*/  ep_list; } ;
struct TYPE_4__ {TYPE_1__ iwarp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct ecore_hwfn*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* ECORE_CONN_REFUSED ; 
 void* ECORE_CONN_RESET ; 
 int /*<<< orphan*/  ECORE_IWARP_CONNECT_MODE_STRING (struct ecore_iwarp_ep*) ; 
 int /*<<< orphan*/  ECORE_IWARP_EP_CLOSED ; 
 int /*<<< orphan*/  ECORE_IWARP_EVENT_ACTIVE_COMPLETE ; 
 int /*<<< orphan*/  ECORE_IWARP_INVALID_TCP_CID ; 
 int /*<<< orphan*/  ECORE_MSG_RDMA ; 
 void* ECORE_TIMEOUT ; 
#define  IWARP_CONN_ERROR_MPA_INVALID_PACKET 132 
#define  IWARP_CONN_ERROR_MPA_NOT_SUPPORTED_VER 131 
#define  IWARP_CONN_ERROR_TCP_CONNECTION_RST 130 
#define  IWARP_CONN_ERROR_TCP_CONNECT_INVALID_PACKET 129 
#define  IWARP_CONN_ERROR_TCP_CONNECT_TIMEOUT 128 
 int /*<<< orphan*/  OSAL_LIST_REMOVE_ENTRY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_MEM_ZERO (struct ecore_iwarp_cm_event_params*,int) ; 
 int /*<<< orphan*/  OSAL_SPIN_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_SPIN_UNLOCK (int /*<<< orphan*/ *) ; 
 scalar_t__ TCP_CONNECT_PASSIVE ; 
 int /*<<< orphan*/  ecore_iwarp_return_ep (struct ecore_hwfn*,struct ecore_iwarp_ep*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct ecore_iwarp_cm_event_params*) ; 

__attribute__((used)) static void
ecore_iwarp_tcp_connect_unsuccessful(struct ecore_hwfn *p_hwfn,
				     struct ecore_iwarp_ep *ep,
				     u8 fw_return_code)
{
	struct ecore_iwarp_cm_event_params params;

	OSAL_MEM_ZERO(&params, sizeof(params));
	params.event = ECORE_IWARP_EVENT_ACTIVE_COMPLETE;
	params.ep_context = ep;
	params.cm_info = &ep->cm_info;
	ep->state = ECORE_IWARP_EP_CLOSED;

	switch (fw_return_code) {
	case IWARP_CONN_ERROR_TCP_CONNECT_INVALID_PACKET:
		DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA,
			   "%s(0x%x) TCP connect got invalid packet\n",
			   ECORE_IWARP_CONNECT_MODE_STRING(ep),
			   ep->tcp_cid);
		params.status = ECORE_CONN_RESET;
		break;
	case IWARP_CONN_ERROR_TCP_CONNECTION_RST:
		DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA,
			   "%s(0x%x) TCP Connection Reset\n",
			   ECORE_IWARP_CONNECT_MODE_STRING(ep),
			   ep->tcp_cid);
		params.status = ECORE_CONN_RESET;
		break;
	case IWARP_CONN_ERROR_TCP_CONNECT_TIMEOUT:
		DP_NOTICE(p_hwfn, false, "%s(0x%x) TCP timeout\n",
			  ECORE_IWARP_CONNECT_MODE_STRING(ep),
			  ep->tcp_cid);
		params.status = ECORE_TIMEOUT;
		break;
	case IWARP_CONN_ERROR_MPA_NOT_SUPPORTED_VER:
		DP_NOTICE(p_hwfn, false, "%s(0x%x) MPA not supported VER\n",
			  ECORE_IWARP_CONNECT_MODE_STRING(ep),
			  ep->tcp_cid);
		params.status = ECORE_CONN_REFUSED;
		break;
	case IWARP_CONN_ERROR_MPA_INVALID_PACKET:
		DP_NOTICE(p_hwfn, false, "%s(0x%x) MPA Invalid Packet\n",
			  ECORE_IWARP_CONNECT_MODE_STRING(ep), ep->tcp_cid);
		params.status = ECORE_CONN_RESET;
		break;
	default:
		DP_ERR(p_hwfn, "%s(0x%x) Unexpected return code tcp connect: %d\n",
		       ECORE_IWARP_CONNECT_MODE_STRING(ep), ep->tcp_cid,
		       fw_return_code);
		params.status = ECORE_CONN_RESET;
		break;
	}

	if (ep->connect_mode == TCP_CONNECT_PASSIVE) {
		ep->tcp_cid = ECORE_IWARP_INVALID_TCP_CID;
		ecore_iwarp_return_ep(p_hwfn, ep);
	} else {
		ep->event_cb(ep->cb_context, &params);
		OSAL_SPIN_LOCK(&p_hwfn->p_rdma_info->iwarp.iw_lock);
		OSAL_LIST_REMOVE_ENTRY(&ep->list_entry,
				       &p_hwfn->p_rdma_info->iwarp.ep_list);
		OSAL_SPIN_UNLOCK(&p_hwfn->p_rdma_info->iwarp.iw_lock);
	}
}