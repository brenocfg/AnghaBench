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
struct tw_cli_req_context {scalar_t__ state; } ;
struct tw_cli_ctlr_context {int /*<<< orphan*/  ctlr_handle; struct tw_cli_req_context* req_ctxt_buf; } ;
typedef  int TW_UINT32 ;
typedef  int /*<<< orphan*/  TW_INT32 ;

/* Variables and functions */
 size_t GET_RESP_ID (int) ; 
 int TWA_STATUS_RESPONSE_QUEUE_EMPTY ; 
 int /*<<< orphan*/  TW_CLI_BUSY_Q ; 
 int /*<<< orphan*/  TW_CLI_COMPLETE_Q ; 
 int TW_CLI_READ_RESPONSE_QUEUE (int /*<<< orphan*/ ) ; 
 int TW_CLI_READ_STATUS_REGISTER (int /*<<< orphan*/ ) ; 
 scalar_t__ TW_CLI_REQ_STATE_BUSY ; 
 scalar_t__ TW_CLI_REQ_STATE_COMPLETE ; 
 int /*<<< orphan*/  TW_CL_FALSE ; 
 int /*<<< orphan*/  TW_CL_MESSAGE_SOURCE_COMMON_LAYER_ERROR ; 
 int /*<<< orphan*/  TW_CL_SEVERITY_ERROR_STRING ; 
 int /*<<< orphan*/  tw_cl_create_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,char*,char*,struct tw_cli_req_context*,scalar_t__) ; 
 int /*<<< orphan*/  tw_cl_print_ctlr_stats (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw_cli_check_ctlr_state (struct tw_cli_ctlr_context*,int) ; 
 int /*<<< orphan*/  tw_cli_dbg_printf (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tw_cli_process_complete_queue (struct tw_cli_ctlr_context*) ; 
 int /*<<< orphan*/  tw_cli_req_q_insert_tail (struct tw_cli_req_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw_cli_req_q_remove_item (struct tw_cli_req_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw_osl_cur_func () ; 

TW_INT32
tw_cli_process_resp_intr(struct tw_cli_ctlr_context *ctlr)
{
	TW_UINT32			resp;
	struct tw_cli_req_context	*req;
	TW_INT32			error;
	TW_UINT32			status_reg;
    
	tw_cli_dbg_printf(10, ctlr->ctlr_handle, tw_osl_cur_func(), "entered");

	for (;;) {
		status_reg = TW_CLI_READ_STATUS_REGISTER(ctlr->ctlr_handle);
		if ((error = tw_cli_check_ctlr_state(ctlr, status_reg)))
			break;
		if (status_reg & TWA_STATUS_RESPONSE_QUEUE_EMPTY) {
			tw_cli_dbg_printf(7, ctlr->ctlr_handle,
				tw_osl_cur_func(), "Response queue empty");
			break;
		}

		/* Response queue is not empty. */
		resp = TW_CLI_READ_RESPONSE_QUEUE(ctlr->ctlr_handle);
		{
			req = &(ctlr->req_ctxt_buf[GET_RESP_ID(resp)]);
		}

		if (req->state != TW_CLI_REQ_STATE_BUSY) {
			tw_cl_create_event(ctlr->ctlr_handle, TW_CL_FALSE,
				TW_CL_MESSAGE_SOURCE_COMMON_LAYER_ERROR,
				0x1201, 0x1, TW_CL_SEVERITY_ERROR_STRING,
				"Unposted command completed!!",
				"request = %p, status = %d",
				req, req->state);
#ifdef TW_OSL_DEBUG
			tw_cl_print_ctlr_stats(ctlr->ctlr_handle);
#endif /* TW_OSL_DEBUG */
			continue;
		}

		/*
		 * Remove the request from the busy queue, mark it as complete,
		 * and enqueue it in the complete queue.
		 */
		tw_cli_req_q_remove_item(req, TW_CLI_BUSY_Q);
		req->state = TW_CLI_REQ_STATE_COMPLETE;
		tw_cli_req_q_insert_tail(req, TW_CLI_COMPLETE_Q);

	}

	/* Complete this, and other requests in the complete queue. */
	tw_cli_process_complete_queue(ctlr);
	
	return(error);
}