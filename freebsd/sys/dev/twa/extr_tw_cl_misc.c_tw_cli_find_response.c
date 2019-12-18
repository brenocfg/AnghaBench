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
struct tw_cli_ctlr_context {scalar_t__ device_id; int /*<<< orphan*/  ctlr_handle; } ;
typedef  int TW_UINT32 ;
typedef  scalar_t__ TW_INT32 ;

/* Variables and functions */
 scalar_t__ GET_LARGE_RESP_ID (int) ; 
 scalar_t__ GET_RESP_ID (int) ; 
 int TWA_STATUS_RESPONSE_QUEUE_EMPTY ; 
 int TW_CLI_READ_LARGE_RESPONSE_QUEUE (int /*<<< orphan*/ ) ; 
 int TW_CLI_READ_RESPONSE_QUEUE (int /*<<< orphan*/ ) ; 
 int TW_CLI_READ_STATUS_REGISTER (int /*<<< orphan*/ ) ; 
 scalar_t__ TW_CL_DEVICE_ID_9K ; 
 scalar_t__ TW_OSL_ENOTTY ; 
 scalar_t__ TW_OSL_ESUCCESS ; 
 int /*<<< orphan*/  tw_cli_dbg_printf (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tw_osl_cur_func () ; 

TW_INT32
tw_cli_find_response(struct tw_cli_ctlr_context *ctlr, TW_INT32 req_id)
{
	TW_UINT32	resp;
	TW_INT32	resp_id;
	TW_UINT32	status_reg;

	tw_cli_dbg_printf(4, ctlr->ctlr_handle, tw_osl_cur_func(), "entered");

	for (;;) {
		status_reg = TW_CLI_READ_STATUS_REGISTER(ctlr->ctlr_handle);

		if (status_reg & TWA_STATUS_RESPONSE_QUEUE_EMPTY)
			return(TW_OSL_ENOTTY); /* no more response queue entries */

		if (ctlr->device_id == TW_CL_DEVICE_ID_9K) {
			resp = TW_CLI_READ_RESPONSE_QUEUE(ctlr->ctlr_handle);
			resp_id = GET_RESP_ID(resp);
		} else {
			resp = TW_CLI_READ_LARGE_RESPONSE_QUEUE(
				ctlr->ctlr_handle);
			resp_id = GET_LARGE_RESP_ID(resp);
		}
		if (resp_id == req_id)
			return(TW_OSL_ESUCCESS); /* found the req_id */
	}
}