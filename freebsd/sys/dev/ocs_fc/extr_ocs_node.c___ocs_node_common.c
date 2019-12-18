#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_19__ {int refound; int /*<<< orphan*/  display_name; struct TYPE_19__* ocs; struct TYPE_19__* els_req_cnt; struct TYPE_19__* els_cmpl_cnt; int /*<<< orphan*/  attached; struct TYPE_19__* app; } ;
typedef  TYPE_5__ ocs_t ;
typedef  int ocs_sm_event_t ;
typedef  TYPE_5__ ocs_sm_ctx_t ;
typedef  TYPE_5__ ocs_node_t ;
struct TYPE_20__ {int /*<<< orphan*/  io; TYPE_4__* header; TYPE_2__* payload; } ;
typedef  TYPE_8__ ocs_node_cb_t ;
struct TYPE_21__ {int /*<<< orphan*/  ox_id; } ;
typedef  TYPE_9__ fc_header_t ;
struct TYPE_17__ {TYPE_9__* virt; } ;
struct TYPE_18__ {TYPE_3__ dma; } ;
struct TYPE_15__ {scalar_t__ virt; } ;
struct TYPE_16__ {TYPE_1__ dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FCCT_COMMAND_NOT_SUPPORTED ; 
 int /*<<< orphan*/  FCCT_HDR_CMDRSP_REJECT ; 
 int /*<<< orphan*/  FC_EXPL_NO_ADDITIONAL ; 
 int /*<<< orphan*/  FC_REASON_COMMAND_NOT_SUPPORTED ; 
 int /*<<< orphan*/  FC_REASON_UNABLE_TO_PERFORM ; 
#define  OCS_EVT_ABTS_RCVD 158 
#define  OCS_EVT_ADISC_RCVD 157 
#define  OCS_EVT_ELS_RCVD 156 
#define  OCS_EVT_ELS_REQ_ABORTED 155 
#define  OCS_EVT_ENTER 154 
#define  OCS_EVT_EXIT 153 
#define  OCS_EVT_FCP_CMD_RCVD 152 
#define  OCS_EVT_FDISC_RCVD 151 
#define  OCS_EVT_FLOGI_RCVD 150 
#define  OCS_EVT_GID_PT_RCVD 149 
#define  OCS_EVT_LOGO_RCVD 148 
#define  OCS_EVT_NODE_ATTACH_FAIL 147 
#define  OCS_EVT_NODE_ATTACH_OK 146 
#define  OCS_EVT_NODE_FREE_OK 145 
#define  OCS_EVT_NODE_MISSING 144 
#define  OCS_EVT_NODE_REFOUND 143 
#define  OCS_EVT_PDISC_RCVD 142 
#define  OCS_EVT_PLOGI_RCVD 141 
#define  OCS_EVT_PRLI_RCVD 140 
#define  OCS_EVT_PRLO_RCVD 139 
#define  OCS_EVT_REENTER 138 
#define  OCS_EVT_RFF_ID_RCVD 137 
#define  OCS_EVT_RFT_ID_RCVD 136 
#define  OCS_EVT_RSCN_RCVD 135 
#define  OCS_EVT_SCR_RCVD 134 
#define  OCS_EVT_SPORT_TOPOLOGY_NOTIFY 133 
#define  OCS_EVT_SRRS_ELS_CMPL_FAIL 132 
#define  OCS_EVT_SRRS_ELS_CMPL_OK 131 
#define  OCS_EVT_SRRS_ELS_REQ_FAIL 130 
#define  OCS_EVT_SRRS_ELS_REQ_OK 129 
#define  OCS_EVT_SRRS_ELS_REQ_RJT 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ocs_assert (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_be16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_bls_send_acc_hdr (int /*<<< orphan*/ ,TYPE_9__*) ; 
 int /*<<< orphan*/  ocs_log_debug (TYPE_5__*,char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_log_test (TYPE_5__*,char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_send_ct_rsp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_send_ls_rjt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_sm_event_name (int) ; 

void *
__ocs_node_common(const char *funcname, ocs_sm_ctx_t *ctx, ocs_sm_event_t evt, void *arg)
{
	ocs_node_t *node = NULL;
	ocs_t *ocs = NULL;
	ocs_node_cb_t *cbdata = arg;
	ocs_assert(ctx, NULL);
	ocs_assert(ctx->app, NULL);
	node = ctx->app;
	ocs_assert(node->ocs, NULL);
	ocs = node->ocs;

	switch(evt) {
	case OCS_EVT_ENTER:
	case OCS_EVT_REENTER:
	case OCS_EVT_EXIT:
	case OCS_EVT_SPORT_TOPOLOGY_NOTIFY:
	case OCS_EVT_NODE_MISSING:
	case OCS_EVT_FCP_CMD_RCVD:
		break;

	case OCS_EVT_NODE_REFOUND:
		node->refound = 1;
		break;

	/* node->attached must be set appropriately for all node attach/detach events */
	case OCS_EVT_NODE_ATTACH_OK:
		node->attached = TRUE;
		break;

	case OCS_EVT_NODE_FREE_OK:
	case OCS_EVT_NODE_ATTACH_FAIL:
		node->attached = FALSE;
		break;

	/* handle any ELS completions that other states either didn't care about
	 * or forgot about
	 */
	case OCS_EVT_SRRS_ELS_CMPL_OK:
	case OCS_EVT_SRRS_ELS_CMPL_FAIL:
		ocs_assert(node->els_cmpl_cnt, NULL);
		node->els_cmpl_cnt--;
		break;

	/* handle any ELS request completions that other states either didn't care about
	 * or forgot about
	 */
	case OCS_EVT_SRRS_ELS_REQ_OK:
	case OCS_EVT_SRRS_ELS_REQ_FAIL:
	case OCS_EVT_SRRS_ELS_REQ_RJT:
	case OCS_EVT_ELS_REQ_ABORTED:
		ocs_assert(node->els_req_cnt, NULL);
		node->els_req_cnt--;
		break;

	case OCS_EVT_ELS_RCVD: {
		fc_header_t *hdr = cbdata->header->dma.virt;

		/* Unsupported ELS was received, send LS_RJT, command not supported */
		ocs_log_debug(ocs, "[%s] (%s) ELS x%02x, LS_RJT not supported\n",
			      node->display_name, funcname, ((uint8_t*)cbdata->payload->dma.virt)[0]);
		ocs_send_ls_rjt(cbdata->io, ocs_be16toh(hdr->ox_id),
			FC_REASON_COMMAND_NOT_SUPPORTED, FC_EXPL_NO_ADDITIONAL, 0,
			NULL, NULL);
		break;
	}

	case OCS_EVT_PLOGI_RCVD:
	case OCS_EVT_FLOGI_RCVD:
	case OCS_EVT_LOGO_RCVD:
	case OCS_EVT_PRLI_RCVD:
	case OCS_EVT_PRLO_RCVD:
	case OCS_EVT_PDISC_RCVD:
	case OCS_EVT_FDISC_RCVD:
	case OCS_EVT_ADISC_RCVD:
	case OCS_EVT_RSCN_RCVD:
	case OCS_EVT_SCR_RCVD: {
		fc_header_t *hdr = cbdata->header->dma.virt;
		/* sm: / send ELS_RJT */
		ocs_log_debug(ocs, "[%s] (%s) %s sending ELS_RJT\n",
			      node->display_name, funcname, ocs_sm_event_name(evt));
		/* if we didn't catch this in a state, send generic LS_RJT */
		ocs_send_ls_rjt(cbdata->io, ocs_be16toh(hdr->ox_id),
			FC_REASON_UNABLE_TO_PERFORM, FC_EXPL_NO_ADDITIONAL, 0,
			NULL, NULL);

		break;
	}
	case OCS_EVT_GID_PT_RCVD:
	case OCS_EVT_RFT_ID_RCVD:
	case OCS_EVT_RFF_ID_RCVD: {
		fc_header_t *hdr = cbdata->header->dma.virt;
		ocs_log_debug(ocs, "[%s] (%s) %s sending CT_REJECT\n",
			      node->display_name, funcname, ocs_sm_event_name(evt));
		ocs_send_ct_rsp(cbdata->io, hdr->ox_id, cbdata->payload->dma.virt, FCCT_HDR_CMDRSP_REJECT, FCCT_COMMAND_NOT_SUPPORTED, 0);
		break;
	}

	case OCS_EVT_ABTS_RCVD: {
		fc_header_t *hdr = cbdata->header->dma.virt;
		ocs_log_debug(ocs, "[%s] (%s) %s sending BA_ACC\n",
			      node->display_name, funcname, ocs_sm_event_name(evt));

		/* sm: send BA_ACC */
		ocs_bls_send_acc_hdr(cbdata->io, hdr);
		break;
	}

	default:
		ocs_log_test(node->ocs, "[%s] %-20s %-20s not handled\n", node->display_name, funcname,
			ocs_sm_event_name(evt));
		break;
	}
	return NULL;
}