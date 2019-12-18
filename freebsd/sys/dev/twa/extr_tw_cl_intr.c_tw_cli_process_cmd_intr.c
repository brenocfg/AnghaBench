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
typedef  int /*<<< orphan*/  TW_VOID ;

/* Variables and functions */
 int /*<<< orphan*/  tw_cli_dbg_printf (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tw_cli_submit_pending_queue (struct tw_cli_ctlr_context*) ; 
 int /*<<< orphan*/  tw_osl_cur_func () ; 

TW_VOID
tw_cli_process_cmd_intr(struct tw_cli_ctlr_context *ctlr)
{
	tw_cli_dbg_printf(6, ctlr->ctlr_handle, tw_osl_cur_func(), "entered");

	/* Start any requests that might be in the pending queue. */
	tw_cli_submit_pending_queue(ctlr);

	/*
	 * If tw_cli_submit_pending_queue was unsuccessful due to a "cmd queue
	 * full" condition, cmd_intr will already have been unmasked by
	 * tw_cli_submit_cmd.  We don't need to do it again... simply return.
	 */
}