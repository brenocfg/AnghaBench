#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {int /*<<< orphan*/  os; int /*<<< orphan*/  cmd_lock; int /*<<< orphan*/  cmd_head_count; int /*<<< orphan*/  cmd_head; } ;
typedef  TYPE_1__ ocs_hw_t ;
struct TYPE_10__ {int /*<<< orphan*/  arg; scalar_t__ buf; int /*<<< orphan*/  (* cb ) (TYPE_1__*,int,scalar_t__,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ ocs_command_ctx_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  ocs_hw_cmd_submit_pending (TYPE_1__*) ; 
 TYPE_2__* ocs_list_remove_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ocs_memcpy (scalar_t__,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ocs_memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocs_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t
ocs_hw_command_process(ocs_hw_t *hw, int32_t status, uint8_t *mqe, size_t size)
{
	ocs_command_ctx_t *ctx = NULL;

	ocs_lock(&hw->cmd_lock);
		if (NULL == (ctx = ocs_list_remove_head(&hw->cmd_head))) {
			ocs_log_err(hw->os, "XXX no command context?!?\n");
			ocs_unlock(&hw->cmd_lock);
			return -1;
		}

		hw->cmd_head_count--;

		/* Post any pending requests */
		ocs_hw_cmd_submit_pending(hw);

	ocs_unlock(&hw->cmd_lock);

	if (ctx->cb) {
		if (ctx->buf) {
			ocs_memcpy(ctx->buf, mqe, size);
		}
		ctx->cb(hw, status, ctx->buf, ctx->arg);
	}

	ocs_memset(ctx, 0, sizeof(ocs_command_ctx_t));
	ocs_free(hw->os, ctx, sizeof(ocs_command_ctx_t));

	return 0;
}