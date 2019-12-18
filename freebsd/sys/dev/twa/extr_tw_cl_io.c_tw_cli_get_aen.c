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
struct tw_cli_req_context {scalar_t__ data; int /*<<< orphan*/  tw_cli_callback; int /*<<< orphan*/  flags; } ;
struct tw_cli_ctlr_context {int /*<<< orphan*/  internal_req_busy; int /*<<< orphan*/  ctlr_handle; } ;
typedef  int /*<<< orphan*/  TW_INT32 ;

/* Variables and functions */
 int /*<<< orphan*/  TW_CLI_FREE_Q ; 
 int /*<<< orphan*/  TW_CLI_REQ_FLAGS_9K ; 
 int /*<<< orphan*/  TW_CLI_REQ_FLAGS_INTERNAL ; 
 int /*<<< orphan*/  TW_CL_FALSE ; 
 struct tw_cli_req_context* TW_CL_NULL ; 
 int /*<<< orphan*/  TW_OSL_EBUSY ; 
 int /*<<< orphan*/  tw_cli_aen_callback ; 
 int /*<<< orphan*/  tw_cli_dbg_printf (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 struct tw_cli_req_context* tw_cli_get_request (struct tw_cli_ctlr_context*) ; 
 int /*<<< orphan*/  tw_cli_req_q_insert_tail (struct tw_cli_req_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw_cli_send_scsi_cmd (struct tw_cli_req_context*,int) ; 
 int /*<<< orphan*/  tw_osl_cur_func () ; 

TW_INT32
tw_cli_get_aen(struct tw_cli_ctlr_context *ctlr)
{
	struct tw_cli_req_context	*req;
	TW_INT32			error;

	tw_cli_dbg_printf(4, ctlr->ctlr_handle, tw_osl_cur_func(), "entered");

	if ((req = tw_cli_get_request(ctlr
		)) == TW_CL_NULL)
		return(TW_OSL_EBUSY);

	req->flags |= TW_CLI_REQ_FLAGS_INTERNAL;
	req->flags |= TW_CLI_REQ_FLAGS_9K;
	req->tw_cli_callback = tw_cli_aen_callback;
	if ((error = tw_cli_send_scsi_cmd(req, 0x03 /* REQUEST_SENSE */))) {
		tw_cli_dbg_printf(1, ctlr->ctlr_handle, tw_osl_cur_func(),
			"Could not send SCSI command",
			"request = %p, error = %d", req, error);
		if (req->data)
			ctlr->internal_req_busy = TW_CL_FALSE;
		tw_cli_req_q_insert_tail(req, TW_CLI_FREE_Q);
	}
	return(error);
}