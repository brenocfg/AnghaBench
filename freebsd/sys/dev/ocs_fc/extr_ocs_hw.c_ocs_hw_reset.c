#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_13__ {scalar_t__ state; size_t wq_count; size_t rq_count; size_t hw_rq_count; size_t mq_count; size_t cq_count; size_t eq_count; int /*<<< orphan*/ * eq; int /*<<< orphan*/  sli; int /*<<< orphan*/ * cq; int /*<<< orphan*/ * mq; TYPE_2__** hw_rq; int /*<<< orphan*/ * rq; int /*<<< orphan*/ * wq; int /*<<< orphan*/  io_lock; int /*<<< orphan*/  io_wait_free; int /*<<< orphan*/  io_free; int /*<<< orphan*/  io_timed_wqe; int /*<<< orphan*/  fcf_index_fcfi; int /*<<< orphan*/  domains; int /*<<< orphan*/  os; int /*<<< orphan*/  cmd_head; } ;
typedef  TYPE_1__ ocs_hw_t ;
typedef  scalar_t__ ocs_hw_state_e ;
typedef  int /*<<< orphan*/  ocs_hw_rtn_e ;
typedef  int ocs_hw_reset_e ;
struct TYPE_14__ {size_t entry_count; int /*<<< orphan*/ ** rq_tracker; } ;
typedef  TYPE_2__ hw_rq_t ;

/* Variables and functions */
#define  OCS_HW_RESET_FIRMWARE 129 
#define  OCS_HW_RESET_FUNCTION 128 
 int /*<<< orphan*/  OCS_HW_RTN_ERROR ; 
 int /*<<< orphan*/  OCS_HW_RTN_SUCCESS ; 
 scalar_t__ OCS_HW_STATE_ACTIVE ; 
 scalar_t__ OCS_HW_STATE_QUEUES_ALLOCATED ; 
 scalar_t__ OCS_HW_STATE_RESET_IN_PROGRESS ; 
 scalar_t__ OCS_HW_STATE_UNINITIALIZED ; 
 int /*<<< orphan*/  hw_queue_teardown (TYPE_1__*) ; 
 int /*<<< orphan*/  ocs_hw_command_cancel (TYPE_1__*) ; 
 int /*<<< orphan*/  ocs_hw_flush (TYPE_1__*) ; 
 int /*<<< orphan*/  ocs_hw_io_cancel (TYPE_1__*) ; 
 int /*<<< orphan*/  ocs_hw_link_event_init (TYPE_1__*) ; 
 int /*<<< orphan*/  ocs_hw_reqtag_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  ocs_hw_rx_free (TYPE_1__*) ; 
 int /*<<< orphan*/  ocs_hw_workaround_setup (TYPE_1__*) ; 
 scalar_t__ ocs_list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_list_remove_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_log_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ocs_memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocs_udelay (int) ; 
 int /*<<< orphan*/  ocs_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shutdown_target_wqe_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  sli_fw_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sli_queue_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sli_reset (int /*<<< orphan*/ *) ; 

ocs_hw_rtn_e
ocs_hw_reset(ocs_hw_t *hw, ocs_hw_reset_e reset)
{
	uint32_t	i;
	ocs_hw_rtn_e rc = OCS_HW_RTN_SUCCESS;
	uint32_t	iters;
	ocs_hw_state_e prev_state = hw->state;

	if (hw->state != OCS_HW_STATE_ACTIVE) {
		ocs_log_test(hw->os, "HW state %d is not active\n", hw->state);
	}

	hw->state = OCS_HW_STATE_RESET_IN_PROGRESS;

	/* shutdown target wqe timer */
	shutdown_target_wqe_timer(hw);

	ocs_hw_flush(hw);

	/*
	 * If an mailbox command requiring a DMA is outstanding (i.e. SFP/DDM),
	 * then the FW will UE when the reset is issued. So attempt to complete
	 * all mailbox commands.
	 */
	iters = 10;
	while (!ocs_list_empty(&hw->cmd_head) && iters) {
		ocs_udelay(10000);
		ocs_hw_flush(hw);
		iters--;
	}

	if (ocs_list_empty(&hw->cmd_head)) {
		ocs_log_debug(hw->os, "All commands completed on MQ queue\n");
	} else {
		ocs_log_debug(hw->os, "Some commands still pending on MQ queue\n");
	}

	/* Reset the chip */
	switch(reset) {
	case OCS_HW_RESET_FUNCTION:
		ocs_log_debug(hw->os, "issuing function level reset\n");
		if (sli_reset(&hw->sli)) {
			ocs_log_err(hw->os, "sli_reset failed\n");
			rc = OCS_HW_RTN_ERROR;
		}
		break;
	case OCS_HW_RESET_FIRMWARE:
		ocs_log_debug(hw->os, "issuing firmware reset\n");
		if (sli_fw_reset(&hw->sli)) {
			ocs_log_err(hw->os, "sli_soft_reset failed\n");
			rc = OCS_HW_RTN_ERROR;
		}
		/*
		 * Because the FW reset leaves the FW in a non-running state,
		 * follow that with a regular reset.
		 */
		ocs_log_debug(hw->os, "issuing function level reset\n");
		if (sli_reset(&hw->sli)) {
			ocs_log_err(hw->os, "sli_reset failed\n");
			rc = OCS_HW_RTN_ERROR;
		}
		break;
	default:
		ocs_log_test(hw->os, "unknown reset type - no reset performed\n");
		hw->state = prev_state;
		return OCS_HW_RTN_ERROR;
	}

	/* Not safe to walk command/io lists unless they've been initialized */
	if (prev_state != OCS_HW_STATE_UNINITIALIZED) {
		ocs_hw_command_cancel(hw);

		/* Clean up the inuse list, the free list and the wait free list */
		ocs_hw_io_cancel(hw);

		ocs_memset(hw->domains, 0, sizeof(hw->domains));
		ocs_memset(hw->fcf_index_fcfi, 0, sizeof(hw->fcf_index_fcfi));

		ocs_hw_link_event_init(hw);

		ocs_lock(&hw->io_lock);
			/* The io lists should be empty, but remove any that didn't get cleaned up. */
			while (!ocs_list_empty(&hw->io_timed_wqe)) {
				ocs_list_remove_head(&hw->io_timed_wqe);
			}
			/* Don't clean up the io_inuse list, the backend will do that when it finishes the IO */

			while (!ocs_list_empty(&hw->io_free)) {
				ocs_list_remove_head(&hw->io_free);
			}
			while (!ocs_list_empty(&hw->io_wait_free)) {
				ocs_list_remove_head(&hw->io_wait_free);
			}

			/* Reset the request tag pool, the HW IO request tags are reassigned in ocs_hw_setup_io() */
			ocs_hw_reqtag_reset(hw);

		ocs_unlock(&hw->io_lock);
	}

	if (prev_state != OCS_HW_STATE_UNINITIALIZED) {
		for (i = 0; i < hw->wq_count; i++) {
			sli_queue_reset(&hw->sli, &hw->wq[i]);
		}

		for (i = 0; i < hw->rq_count; i++) {
			sli_queue_reset(&hw->sli, &hw->rq[i]);
		}

		for (i = 0; i < hw->hw_rq_count; i++) {
			hw_rq_t *rq = hw->hw_rq[i];
			if (rq->rq_tracker != NULL) {
				uint32_t j;

				for (j = 0; j < rq->entry_count; j++) {
					rq->rq_tracker[j] = NULL;
				}
			}
		}

		for (i = 0; i < hw->mq_count; i++) {
			sli_queue_reset(&hw->sli, &hw->mq[i]);
		}

		for (i = 0; i < hw->cq_count; i++) {
			sli_queue_reset(&hw->sli, &hw->cq[i]);
		}

		for (i = 0; i < hw->eq_count; i++) {
			sli_queue_reset(&hw->sli, &hw->eq[i]);
		}

		/* Free rq buffers */
		ocs_hw_rx_free(hw);

		/* Teardown the HW queue topology */
		hw_queue_teardown(hw);
	} else {

		/* Free rq buffers */
		ocs_hw_rx_free(hw);
	}

	/*
	 * Re-apply the run-time workarounds after clearing the SLI config
	 * fields in sli_reset.
	 */
	ocs_hw_workaround_setup(hw);
	hw->state = OCS_HW_STATE_QUEUES_ALLOCATED;

	return rc;
}