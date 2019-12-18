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
struct tw_cli_ctlr_context {int /*<<< orphan*/  reset_needed; } ;
struct tw_cl_ctlr_handle {scalar_t__ cl_ctlr_ctxt; } ;
typedef  int /*<<< orphan*/  TW_VOID ;

/* Variables and functions */
 int /*<<< orphan*/  TW_CL_TRUE ; 

TW_VOID
tw_cl_set_reset_needed(struct tw_cl_ctlr_handle *ctlr_handle)
{
	struct tw_cli_ctlr_context	*ctlr =
		(struct tw_cli_ctlr_context *)(ctlr_handle->cl_ctlr_ctxt);

	ctlr->reset_needed = TW_CL_TRUE;
}