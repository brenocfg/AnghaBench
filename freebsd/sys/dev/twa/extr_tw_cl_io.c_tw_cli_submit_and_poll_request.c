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
struct tw_cli_req_context {int error_code; scalar_t__ state; scalar_t__ data; struct tw_cli_ctlr_context* ctlr; } ;
struct tw_cli_ctlr_context {int /*<<< orphan*/  internal_req_busy; int /*<<< orphan*/  ctlr_handle; int /*<<< orphan*/ * req_q_head; } ;
typedef  scalar_t__ TW_UINT32 ;
typedef  scalar_t__ TW_TIME ;
typedef  int TW_INT32 ;

/* Variables and functions */
 int /*<<< orphan*/  TWA_CONTROL_MASK_COMMAND_INTERRUPT ; 
 int /*<<< orphan*/  TW_CLI_FREE_Q ; 
 size_t TW_CLI_PENDING_Q ; 
 scalar_t__ TW_CLI_REQ_STATE_BUSY ; 
 scalar_t__ TW_CLI_REQ_STATE_COMPLETE ; 
 scalar_t__ TW_CLI_REQ_STATE_PENDING ; 
 int /*<<< orphan*/  TW_CLI_WRITE_CONTROL_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TW_CL_FALSE ; 
 int /*<<< orphan*/  TW_CL_MESSAGE_SOURCE_COMMON_LAYER_ERROR ; 
 scalar_t__ TW_CL_NULL ; 
 scalar_t__ TW_CL_Q_FIRST_ITEM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TW_CL_SEVERITY_ERROR_STRING ; 
 int TW_OSL_ETIMEDOUT ; 
 int /*<<< orphan*/  tw_cl_create_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  tw_cli_dbg_printf (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tw_cli_process_resp_intr (struct tw_cli_ctlr_context*) ; 
 int /*<<< orphan*/  tw_cli_req_q_insert_tail (struct tw_cli_req_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw_cli_req_q_remove_item (struct tw_cli_req_context*,size_t) ; 
 int tw_cli_submit_cmd (struct tw_cli_req_context*) ; 
 int /*<<< orphan*/  tw_osl_cur_func () ; 
 scalar_t__ tw_osl_get_local_time () ; 

TW_INT32
tw_cli_submit_and_poll_request(struct tw_cli_req_context *req,
	TW_UINT32 timeout)
{
	struct tw_cli_ctlr_context	*ctlr = req->ctlr;
	TW_TIME				end_time;
	TW_INT32			error;

	tw_cli_dbg_printf(4, ctlr->ctlr_handle, tw_osl_cur_func(), "entered");

	/*
	 * If the cmd queue is full, tw_cli_submit_cmd will queue this
	 * request in the pending queue, since this is an internal request.
	 */
	if ((error = tw_cli_submit_cmd(req))) {
		tw_cl_create_event(ctlr->ctlr_handle, TW_CL_FALSE,
			TW_CL_MESSAGE_SOURCE_COMMON_LAYER_ERROR,
			0x1103, 0x1, TW_CL_SEVERITY_ERROR_STRING,
			"Failed to start internal request",
			"error = %d", error);
		return(error);
	}

	/*
	 * Poll for the response until the command gets completed, or there's
	 * a timeout.
	 */
	end_time = tw_osl_get_local_time() + timeout;
	do {
		if ((error = req->error_code))
			/*
			 * This will take care of completion due to a reset,
			 * or a failure in tw_cli_submit_pending_queue.
			 * The caller should do the clean-up.
			 */
			return(error);

		/* See if the command completed. */
		tw_cli_process_resp_intr(ctlr);

		if ((req->state != TW_CLI_REQ_STATE_BUSY) &&
			(req->state != TW_CLI_REQ_STATE_PENDING))
			return(req->state != TW_CLI_REQ_STATE_COMPLETE);
	} while (tw_osl_get_local_time() <= end_time);

	/* Time out! */
	tw_cl_create_event(ctlr->ctlr_handle, TW_CL_FALSE,
		TW_CL_MESSAGE_SOURCE_COMMON_LAYER_ERROR,
		0x1104, 0x1, TW_CL_SEVERITY_ERROR_STRING,
		"Internal request timed out",
		"request = %p", req);

	/*
	 * We will reset the controller only if the request has already been
	 * submitted, so as to not lose the request packet.  If a busy request
	 * timed out, the reset will take care of freeing resources.  If a
	 * pending request timed out, we will free resources for that request,
	 * right here, thereby avoiding a reset.  So, the caller is expected
	 * to NOT cleanup when TW_OSL_ETIMEDOUT is returned.
	 */

	/*
	 * We have to make sure that this timed out request, if it were in the
	 * pending queue, doesn't get submitted while we are here, from
	 * tw_cli_submit_pending_queue.  There could be a race in that case.
	 * Need to revisit.
	 */
	if (req->state == TW_CLI_REQ_STATE_PENDING) {
		tw_cli_dbg_printf(3, ctlr->ctlr_handle, tw_osl_cur_func(),
			"Removing request from pending queue");
		/*
		 * Request was never submitted.  Clean up.  Note that we did
		 * not do a reset.  So, we have to remove the request ourselves
		 * from the pending queue (as against tw_cli_drain_pendinq_queue
		 * taking care of it).
		 */
		tw_cli_req_q_remove_item(req, TW_CLI_PENDING_Q);
		if ((TW_CL_Q_FIRST_ITEM(&(ctlr->req_q_head[TW_CLI_PENDING_Q]))) == TW_CL_NULL)
			TW_CLI_WRITE_CONTROL_REGISTER(ctlr->ctlr_handle,
				TWA_CONTROL_MASK_COMMAND_INTERRUPT);
		if (req->data)
			ctlr->internal_req_busy = TW_CL_FALSE;
		tw_cli_req_q_insert_tail(req, TW_CLI_FREE_Q);
	}

	return(TW_OSL_ETIMEDOUT);
}