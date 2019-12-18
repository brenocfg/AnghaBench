#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  os; int /*<<< orphan*/  sli; } ;
typedef  TYPE_1__ ocs_hw_t ;
typedef  int /*<<< orphan*/  ocs_hw_async_cb_t ;
struct TYPE_9__ {int /*<<< orphan*/  cmd; void* arg; int /*<<< orphan*/  callback; } ;
typedef  TYPE_2__ ocs_hw_async_call_ctx_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_CMD_NOWAIT ; 
 int OCS_HW_RTN_NO_MEMORY ; 
 int OCS_M_NOWAIT ; 
 int OCS_M_ZERO ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  ocs_hw_async_cb ; 
 scalar_t__ ocs_hw_command (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* ocs_malloc (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ sli_cmd_common_nop (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int32_t
ocs_hw_async_call(ocs_hw_t *hw, ocs_hw_async_cb_t callback, void *arg)
{
	int32_t rc = 0;
	ocs_hw_async_call_ctx_t *ctx;

	/*
	 * Allocate a callback context (which includes the mailbox command buffer), we need
	 * this to be persistent as the mailbox command submission may be queued and executed later
	 * execution.
	 */
	ctx = ocs_malloc(hw->os, sizeof(*ctx), OCS_M_ZERO | OCS_M_NOWAIT);
	if (ctx == NULL) {
		ocs_log_err(hw->os, "failed to malloc async call context\n");
		return OCS_HW_RTN_NO_MEMORY;
	}
	ctx->callback = callback;
	ctx->arg = arg;

	/* Build and send a NOP mailbox command */
	if (sli_cmd_common_nop(&hw->sli, ctx->cmd, sizeof(ctx->cmd), 0) == 0) {
		ocs_log_err(hw->os, "COMMON_NOP format failure\n");
		ocs_free(hw->os, ctx, sizeof(*ctx));
		rc = -1;
	}

	if (ocs_hw_command(hw, ctx->cmd, OCS_CMD_NOWAIT, ocs_hw_async_cb, ctx)) {
		ocs_log_err(hw->os, "COMMON_NOP command failure\n");
		ocs_free(hw->os, ctx, sizeof(*ctx));
		rc = -1;
	}
	return rc;
}