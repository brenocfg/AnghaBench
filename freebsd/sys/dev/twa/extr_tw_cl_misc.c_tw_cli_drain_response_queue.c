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
struct tw_cli_ctlr_context {int /*<<< orphan*/  ctlr_handle; } ;
typedef  int TW_UINT32 ;
typedef  int /*<<< orphan*/  TW_INT32 ;

/* Variables and functions */
 int TWA_STATUS_RESPONSE_QUEUE_EMPTY ; 
 int TW_CLI_READ_RESPONSE_QUEUE (int /*<<< orphan*/ ) ; 
 int TW_CLI_READ_STATUS_REGISTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TW_OSL_ESUCCESS ; 
 int /*<<< orphan*/  tw_cli_dbg_printf (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tw_osl_cur_func () ; 

TW_INT32
tw_cli_drain_response_queue(struct tw_cli_ctlr_context *ctlr)
{
	TW_UINT32	resp;
	TW_UINT32	status_reg;

	tw_cli_dbg_printf(4, ctlr->ctlr_handle, tw_osl_cur_func(), "entered");

	for (;;) {
		status_reg = TW_CLI_READ_STATUS_REGISTER(ctlr->ctlr_handle);

		if (status_reg & TWA_STATUS_RESPONSE_QUEUE_EMPTY)
			return(TW_OSL_ESUCCESS); /* no more response queue entries */

		resp = TW_CLI_READ_RESPONSE_QUEUE(ctlr->ctlr_handle);
	}
}