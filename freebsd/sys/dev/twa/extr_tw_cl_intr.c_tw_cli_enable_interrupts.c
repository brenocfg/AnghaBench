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
struct tw_cli_ctlr_context {int /*<<< orphan*/  ctlr_handle; int /*<<< orphan*/  interrupts_enabled; } ;
typedef  int /*<<< orphan*/  TW_VOID ;

/* Variables and functions */
 int TWA_CONTROL_CLEAR_ATTENTION_INTERRUPT ; 
 int TWA_CONTROL_ENABLE_INTERRUPTS ; 
 int TWA_CONTROL_UNMASK_RESPONSE_INTERRUPT ; 
 int /*<<< orphan*/  TW_CLI_WRITE_CONTROL_REGISTER (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TW_CL_TRUE ; 
 int /*<<< orphan*/  tw_cli_dbg_printf (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tw_osl_cur_func () ; 

TW_VOID
tw_cli_enable_interrupts(struct tw_cli_ctlr_context *ctlr)
{
	tw_cli_dbg_printf(3, ctlr->ctlr_handle, tw_osl_cur_func(), "entered");

	ctlr->interrupts_enabled = TW_CL_TRUE;
	TW_CLI_WRITE_CONTROL_REGISTER(ctlr->ctlr_handle,
		TWA_CONTROL_CLEAR_ATTENTION_INTERRUPT |
		TWA_CONTROL_UNMASK_RESPONSE_INTERRUPT |
		TWA_CONTROL_ENABLE_INTERRUPTS);
}