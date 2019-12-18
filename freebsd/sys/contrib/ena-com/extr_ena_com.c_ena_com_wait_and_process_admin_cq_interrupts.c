#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ena_comp_ctx {scalar_t__ status; int /*<<< orphan*/  comp_status; int /*<<< orphan*/  cmd_opcode; int /*<<< orphan*/  wait_event; } ;
struct TYPE_2__ {int /*<<< orphan*/  no_completion; } ;
struct ena_com_admin_queue {int running_state; int /*<<< orphan*/  q_lock; TYPE_1__ stats; int /*<<< orphan*/  completion_timeout; } ;

/* Variables and functions */
 scalar_t__ ENA_CMD_COMPLETED ; 
 scalar_t__ ENA_CMD_SUBMITTED ; 
 int ENA_COM_TIMER_EXPIRED ; 
 int /*<<< orphan*/  ENA_SPINLOCK_LOCK (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  ENA_SPINLOCK_UNLOCK (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  ENA_WAIT_EVENT_WAIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comp_ctxt_release (struct ena_com_admin_queue*,struct ena_comp_ctx*) ; 
 int ena_com_comp_status_to_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ena_com_handle_admin_completion (struct ena_com_admin_queue*) ; 
 int /*<<< orphan*/  ena_trc_err (char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ena_com_wait_and_process_admin_cq_interrupts(struct ena_comp_ctx *comp_ctx,
							struct ena_com_admin_queue *admin_queue)
{
	unsigned long flags = 0;
	int ret;

	ENA_WAIT_EVENT_WAIT(comp_ctx->wait_event,
			    admin_queue->completion_timeout);

	/* In case the command wasn't completed find out the root cause.
	 * There might be 2 kinds of errors
	 * 1) No completion (timeout reached)
	 * 2) There is completion but the device didn't get any msi-x interrupt.
	 */
	if (unlikely(comp_ctx->status == ENA_CMD_SUBMITTED)) {
		ENA_SPINLOCK_LOCK(admin_queue->q_lock, flags);
		ena_com_handle_admin_completion(admin_queue);
		admin_queue->stats.no_completion++;
		ENA_SPINLOCK_UNLOCK(admin_queue->q_lock, flags);

		if (comp_ctx->status == ENA_CMD_COMPLETED)
			ena_trc_err("The ena device have completion but the driver didn't receive any MSI-X interrupt (cmd %d)\n",
				    comp_ctx->cmd_opcode);
		else
			ena_trc_err("The ena device doesn't send any completion for the admin cmd %d status %d\n",
				    comp_ctx->cmd_opcode, comp_ctx->status);

		admin_queue->running_state = false;
		ret = ENA_COM_TIMER_EXPIRED;
		goto err;
	}

	ret = ena_com_comp_status_to_errno(comp_ctx->comp_status);
err:
	comp_ctxt_release(admin_queue, comp_ctx);
	return ret;
}