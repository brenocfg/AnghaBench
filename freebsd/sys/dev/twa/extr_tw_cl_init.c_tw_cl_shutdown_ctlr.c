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
struct tw_cli_ctlr_context {int /*<<< orphan*/  io_lock; int /*<<< orphan*/  gen_lock; int /*<<< orphan*/  active; } ;
struct tw_cl_ctlr_handle {scalar_t__ cl_ctlr_ctxt; } ;
typedef  int TW_UINT32 ;
typedef  int /*<<< orphan*/  TW_INT32 ;

/* Variables and functions */
 int /*<<< orphan*/  TWA_SHUTDOWN_MESSAGE_CREDITS ; 
 int /*<<< orphan*/  TW_CL_FALSE ; 
 int /*<<< orphan*/  TW_CL_MESSAGE_SOURCE_COMMON_LAYER_ERROR ; 
 int /*<<< orphan*/  TW_CL_NULL ; 
 int /*<<< orphan*/  TW_CL_SEVERITY_ERROR_STRING ; 
 int TW_CL_STOP_CTLR_ONLY ; 
 int /*<<< orphan*/  tw_cl_create_event (struct tw_cl_ctlr_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw_cli_dbg_printf (int,struct tw_cl_ctlr_handle*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tw_cli_disable_interrupts (struct tw_cli_ctlr_context*) ; 
 int /*<<< orphan*/  tw_cli_init_connection (struct tw_cli_ctlr_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw_osl_cur_func () ; 
 int /*<<< orphan*/  tw_osl_destroy_lock (struct tw_cl_ctlr_handle*,int /*<<< orphan*/ ) ; 

TW_INT32
tw_cl_shutdown_ctlr(struct tw_cl_ctlr_handle *ctlr_handle, TW_UINT32 flags)
{
	struct tw_cli_ctlr_context	*ctlr =
		(struct tw_cli_ctlr_context *)(ctlr_handle->cl_ctlr_ctxt);
	TW_INT32			error;

	tw_cli_dbg_printf(3, ctlr_handle, tw_osl_cur_func(), "entered");
	/*
	 * Mark the controller as inactive, disable any further interrupts,
	 * and notify the controller that we are going down.
	 */
	ctlr->active = TW_CL_FALSE;

	tw_cli_disable_interrupts(ctlr);

	/* Let the controller know that we are going down. */
	if ((error = tw_cli_init_connection(ctlr, TWA_SHUTDOWN_MESSAGE_CREDITS,
			0, 0, 0, 0, 0, TW_CL_NULL, TW_CL_NULL, TW_CL_NULL,
			TW_CL_NULL, TW_CL_NULL)))
		tw_cl_create_event(ctlr_handle, TW_CL_FALSE,
			TW_CL_MESSAGE_SOURCE_COMMON_LAYER_ERROR,
			0x1015, 0x1, TW_CL_SEVERITY_ERROR_STRING,
			"Can't close connection with controller",
			"error = %d", error);

	if (flags & TW_CL_STOP_CTLR_ONLY)
		goto ret;

	/* Destroy all locks used by CL. */
	tw_osl_destroy_lock(ctlr_handle, ctlr->gen_lock);
	tw_osl_destroy_lock(ctlr_handle, ctlr->io_lock);

ret:
	return(error);
}