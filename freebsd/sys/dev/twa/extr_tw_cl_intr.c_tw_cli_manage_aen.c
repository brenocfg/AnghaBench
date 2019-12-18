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
struct tw_cli_req_context {scalar_t__ data; } ;
struct tw_cli_ctlr_context {int /*<<< orphan*/  ctlr_handle; int /*<<< orphan*/  interrupts_enabled; int /*<<< orphan*/  get_more_aens; int /*<<< orphan*/  internal_req_busy; } ;
struct TYPE_2__ {int error; } ;
struct tw_cl_command_header {TYPE_1__ status_block; } ;
typedef  int /*<<< orphan*/  TW_UINT32 ;
typedef  int TW_UINT16 ;
typedef  int TW_TIME ;

/* Variables and functions */
#define  TWA_AEN_QUEUE_EMPTY 129 
#define  TWA_AEN_SYNC_TIME_WITH_HOST 128 
 int /*<<< orphan*/  TWA_PARAM_TIME_SCHED_TIME ; 
 int /*<<< orphan*/  TWA_PARAM_TIME_TABLE ; 
 int /*<<< orphan*/  TW_CLI_FREE_Q ; 
 int /*<<< orphan*/  TW_CL_FALSE ; 
 int /*<<< orphan*/  TW_CL_MESSAGE_SOURCE_COMMON_LAYER_ERROR ; 
 int /*<<< orphan*/  TW_CL_MESSAGE_SOURCE_CONTROLLER_EVENT ; 
 int /*<<< orphan*/  TW_CL_NULL ; 
 int /*<<< orphan*/  TW_CL_SEVERITY_ERROR_STRING ; 
 int /*<<< orphan*/  TW_CL_TRUE ; 
 int /*<<< orphan*/  tw_cl_create_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw_cli_create_ctlr_event (struct tw_cli_ctlr_context*,int /*<<< orphan*/ ,struct tw_cl_command_header*) ; 
 int /*<<< orphan*/  tw_cli_dbg_printf (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tw_cli_param_callback ; 
 int /*<<< orphan*/  tw_cli_req_q_insert_tail (struct tw_cli_req_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw_cli_set_param (struct tw_cli_ctlr_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw_osl_cur_func () ; 
 int tw_osl_get_local_time () ; 

TW_UINT16
tw_cli_manage_aen(struct tw_cli_ctlr_context *ctlr,
	struct tw_cli_req_context *req)
{
	struct tw_cl_command_header	*cmd_hdr;
	TW_UINT16			aen_code;
	TW_TIME				local_time;
	TW_TIME				sync_time;
	TW_UINT32			error;

	tw_cli_dbg_printf(4, ctlr->ctlr_handle, tw_osl_cur_func(), "entered");

	cmd_hdr = (struct tw_cl_command_header *)(req->data);
	aen_code = cmd_hdr->status_block.error;

	switch (aen_code) {
	case TWA_AEN_SYNC_TIME_WITH_HOST:
		tw_cli_dbg_printf(4, ctlr->ctlr_handle, tw_osl_cur_func(),
			"Received AEN_SYNC_TIME");
		/*
		 * Free the internal req pkt right here, since
		 * tw_cli_set_param will need it.
		 */
		ctlr->internal_req_busy = TW_CL_FALSE;
		tw_cli_req_q_insert_tail(req, TW_CLI_FREE_Q);

		/*
		 * We will use a callback in tw_cli_set_param only when
		 * interrupts are enabled and we can expect our callback
		 * to get called.  Setting the get_more_aens
		 * flag will make the callback continue to try to retrieve
		 * more AEN's.
		 */
		if (ctlr->interrupts_enabled)
			ctlr->get_more_aens = TW_CL_TRUE;
		/* Calculate time (in seconds) since last Sunday 12.00 AM. */
		local_time = tw_osl_get_local_time();
		sync_time = (local_time - (3 * 86400)) % 604800;
		if ((error = tw_cli_set_param(ctlr, TWA_PARAM_TIME_TABLE,
				TWA_PARAM_TIME_SCHED_TIME, 4,
				&sync_time,
				(ctlr->interrupts_enabled)
				? tw_cli_param_callback : TW_CL_NULL)))
			tw_cl_create_event(ctlr->ctlr_handle, TW_CL_FALSE,
				TW_CL_MESSAGE_SOURCE_COMMON_LAYER_ERROR,
				0x1208, 0x1, TW_CL_SEVERITY_ERROR_STRING,
				"Unable to sync time with ctlr",
				"error = %d", error);

		break;


	case TWA_AEN_QUEUE_EMPTY:
		tw_cli_dbg_printf(4, ctlr->ctlr_handle, tw_osl_cur_func(),
			"AEN queue empty");
		break;


	default:
		/* Queue the event. */

		tw_cli_dbg_printf(4, ctlr->ctlr_handle, tw_osl_cur_func(),
			"Queueing AEN");
		tw_cli_create_ctlr_event(ctlr,
			TW_CL_MESSAGE_SOURCE_CONTROLLER_EVENT,
			cmd_hdr);
		break;
	} /* switch */
	return(aen_code);
}