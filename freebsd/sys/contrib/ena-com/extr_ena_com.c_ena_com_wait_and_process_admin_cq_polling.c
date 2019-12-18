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
struct ena_comp_ctx {scalar_t__ status; int /*<<< orphan*/  comp_status; } ;
struct TYPE_2__ {int /*<<< orphan*/  aborted_cmd; int /*<<< orphan*/  no_completion; } ;
struct ena_com_admin_queue {int running_state; int /*<<< orphan*/  q_lock; TYPE_1__ stats; int /*<<< orphan*/  completion_timeout; } ;

/* Variables and functions */
 scalar_t__ ENA_CMD_ABORTED ; 
 scalar_t__ ENA_CMD_COMPLETED ; 
 scalar_t__ ENA_CMD_SUBMITTED ; 
 int ENA_COM_NO_DEVICE ; 
 int ENA_COM_TIMER_EXPIRED ; 
 unsigned long ENA_GET_SYSTEM_TIMEOUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENA_MSLEEP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENA_POLL_MS ; 
 int /*<<< orphan*/  ENA_SPINLOCK_LOCK (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  ENA_SPINLOCK_UNLOCK (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ ENA_TIME_EXPIRE (unsigned long) ; 
 int /*<<< orphan*/  ENA_WARN (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  comp_ctxt_release (struct ena_com_admin_queue*,struct ena_comp_ctx*) ; 
 int ena_com_comp_status_to_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ena_com_handle_admin_completion (struct ena_com_admin_queue*) ; 
 int /*<<< orphan*/  ena_trc_err (char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ena_com_wait_and_process_admin_cq_polling(struct ena_comp_ctx *comp_ctx,
						     struct ena_com_admin_queue *admin_queue)
{
	unsigned long flags = 0;
	unsigned long timeout;
	int ret;

	timeout = ENA_GET_SYSTEM_TIMEOUT(admin_queue->completion_timeout);

	while (1) {
                ENA_SPINLOCK_LOCK(admin_queue->q_lock, flags);
                ena_com_handle_admin_completion(admin_queue);
                ENA_SPINLOCK_UNLOCK(admin_queue->q_lock, flags);

                if (comp_ctx->status != ENA_CMD_SUBMITTED)
			break;

		if (ENA_TIME_EXPIRE(timeout)) {
			ena_trc_err("Wait for completion (polling) timeout\n");
			/* ENA didn't have any completion */
			ENA_SPINLOCK_LOCK(admin_queue->q_lock, flags);
			admin_queue->stats.no_completion++;
			admin_queue->running_state = false;
			ENA_SPINLOCK_UNLOCK(admin_queue->q_lock, flags);

			ret = ENA_COM_TIMER_EXPIRED;
			goto err;
		}

		ENA_MSLEEP(ENA_POLL_MS);
	}

	if (unlikely(comp_ctx->status == ENA_CMD_ABORTED)) {
		ena_trc_err("Command was aborted\n");
		ENA_SPINLOCK_LOCK(admin_queue->q_lock, flags);
		admin_queue->stats.aborted_cmd++;
		ENA_SPINLOCK_UNLOCK(admin_queue->q_lock, flags);
		ret = ENA_COM_NO_DEVICE;
		goto err;
	}

	ENA_WARN(comp_ctx->status != ENA_CMD_COMPLETED,
		 "Invalid comp status %d\n", comp_ctx->status);

	ret = ena_com_comp_status_to_errno(comp_ctx->comp_status);
err:
	comp_ctxt_release(admin_queue, comp_ctx);
	return ret;
}