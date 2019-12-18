#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_3__ {size_t eq_count; scalar_t__ state; int /*<<< orphan*/ * eq; int /*<<< orphan*/  sli; int /*<<< orphan*/  os; } ;
typedef  TYPE_1__ ocs_hw_t ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ OCS_HW_STATE_UNINITIALIZED ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  sli_queue_arm (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sli_queue_is_empty (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int32_t
ocs_hw_event_check(ocs_hw_t *hw, uint32_t vector)
{
	int32_t rc = 0;

	if (!hw) {
		ocs_log_err(NULL, "HW context NULL?!?\n");
		return -1;
	}

	if (vector > hw->eq_count) {
		ocs_log_err(hw->os, "vector %d. max %d\n",
				vector, hw->eq_count);
		return -1;
	}

	/*
	 * The caller should disable interrupts if they wish to prevent us
	 * from processing during a shutdown. The following states are defined:
	 *   OCS_HW_STATE_UNINITIALIZED - No queues allocated
	 *   OCS_HW_STATE_QUEUES_ALLOCATED - The state after a chip reset,
	 *                                    queues are cleared.
	 *   OCS_HW_STATE_ACTIVE - Chip and queues are operational
	 *   OCS_HW_STATE_RESET_IN_PROGRESS - reset, we still want completions
	 *   OCS_HW_STATE_TEARDOWN_IN_PROGRESS - We still want mailbox
	 *                                        completions.
	 */
	if (hw->state != OCS_HW_STATE_UNINITIALIZED) {
		rc = sli_queue_is_empty(&hw->sli, &hw->eq[vector]);

		/* Re-arm queue if there are no entries */
		if (rc != 0) {
			sli_queue_arm(&hw->sli, &hw->eq[vector], TRUE);
		}
	}
	return rc;
}