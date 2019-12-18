#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ecore_iwarp_ep {int /*<<< orphan*/  cb_context; int /*<<< orphan*/  (* event_cb ) (int /*<<< orphan*/ ,struct ecore_iwarp_cm_event_params*) ;int /*<<< orphan*/  cm_info; int /*<<< orphan*/  cid; } ;
struct ecore_iwarp_cm_event_params {int /*<<< orphan*/ * cm_info; struct ecore_iwarp_ep* ep_context; void* event; int /*<<< orphan*/  status; } ;
struct ecore_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ECORE_CONN_RESET ; 
 void* ECORE_IWARP_EVENT_CQ_OVERFLOW ; 
 void* ECORE_IWARP_EVENT_DISCONNECT ; 
 void* ECORE_IWARP_EVENT_IRQ_FULL ; 
 void* ECORE_IWARP_EVENT_LLP_TIMEOUT ; 
 void* ECORE_IWARP_EVENT_LOCAL_ACCESS_ERROR ; 
 void* ECORE_IWARP_EVENT_QP_CATASTROPHIC ; 
 void* ECORE_IWARP_EVENT_REMOTE_OPERATION_ERROR ; 
 void* ECORE_IWARP_EVENT_REMOTE_PROTECTION_ERROR ; 
 void* ECORE_IWARP_EVENT_RQ_EMPTY ; 
 void* ECORE_IWARP_EVENT_TERMINATE_RECEIVED ; 
 int /*<<< orphan*/  ECORE_MSG_RDMA ; 
 int /*<<< orphan*/  ECORE_SUCCESS ; 
#define  IWARP_EXCEPTION_DETECTED_CQ_OVERFLOW 138 
#define  IWARP_EXCEPTION_DETECTED_IRQ_FULL 137 
#define  IWARP_EXCEPTION_DETECTED_LLP_CLOSED 136 
#define  IWARP_EXCEPTION_DETECTED_LLP_RESET 135 
#define  IWARP_EXCEPTION_DETECTED_LLP_TIMEOUT 134 
#define  IWARP_EXCEPTION_DETECTED_LOCAL_ACCESS_ERROR 133 
#define  IWARP_EXCEPTION_DETECTED_LOCAL_CATASTROPHIC 132 
#define  IWARP_EXCEPTION_DETECTED_REMOTE_OPERATION_ERROR 131 
#define  IWARP_EXCEPTION_DETECTED_REMOTE_PROTECTION_ERROR 130 
#define  IWARP_EXCEPTION_DETECTED_RQ_EMPTY 129 
#define  IWARP_EXCEPTION_DETECTED_TERMINATE_RECEIVED 128 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct ecore_iwarp_cm_event_params*) ; 

__attribute__((used)) static void
ecore_iwarp_exception_received(struct ecore_hwfn *p_hwfn,
			       struct ecore_iwarp_ep *ep,
			       int fw_ret_code)
{
	struct ecore_iwarp_cm_event_params params;
	bool event_cb = false;

	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "EP(0x%x) fw_ret_code=%d\n",
		   ep->cid, fw_ret_code);

	switch (fw_ret_code) {
	case IWARP_EXCEPTION_DETECTED_LLP_CLOSED:
		params.status = ECORE_SUCCESS;
		params.event = ECORE_IWARP_EVENT_DISCONNECT;
		event_cb = true;
		break;
	case IWARP_EXCEPTION_DETECTED_LLP_RESET:
		params.status = ECORE_CONN_RESET;
		params.event = ECORE_IWARP_EVENT_DISCONNECT;
		event_cb = true;
		break;
	case IWARP_EXCEPTION_DETECTED_RQ_EMPTY:
		params.event = ECORE_IWARP_EVENT_RQ_EMPTY;
		event_cb = true;
		break;
	case IWARP_EXCEPTION_DETECTED_IRQ_FULL:
		params.event = ECORE_IWARP_EVENT_IRQ_FULL;
		event_cb = true;
		break;
	case IWARP_EXCEPTION_DETECTED_LLP_TIMEOUT:
		params.event = ECORE_IWARP_EVENT_LLP_TIMEOUT;
		event_cb = true;
		break;
	case IWARP_EXCEPTION_DETECTED_REMOTE_PROTECTION_ERROR:
		params.event = ECORE_IWARP_EVENT_REMOTE_PROTECTION_ERROR;
		event_cb = true;
		break;
	case IWARP_EXCEPTION_DETECTED_CQ_OVERFLOW:
		params.event = ECORE_IWARP_EVENT_CQ_OVERFLOW;
		event_cb = true;
		break;
	case IWARP_EXCEPTION_DETECTED_LOCAL_CATASTROPHIC:
		params.event = ECORE_IWARP_EVENT_QP_CATASTROPHIC;
		event_cb = true;
		break;
	case IWARP_EXCEPTION_DETECTED_LOCAL_ACCESS_ERROR:
		params.event = ECORE_IWARP_EVENT_LOCAL_ACCESS_ERROR;
		event_cb = true;
		break;
	case IWARP_EXCEPTION_DETECTED_REMOTE_OPERATION_ERROR:
		params.event = ECORE_IWARP_EVENT_REMOTE_OPERATION_ERROR;
		event_cb = true;
		break;
	case IWARP_EXCEPTION_DETECTED_TERMINATE_RECEIVED:
		params.event = ECORE_IWARP_EVENT_TERMINATE_RECEIVED;
		event_cb = true;
		break;
	default:
		DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA,
			   "Unhandled exception received...\n");
		break;
	}

	if (event_cb) {
		params.ep_context = ep;
		params.cm_info = &ep->cm_info;
		ep->event_cb(ep->cb_context, &params);
	}
}