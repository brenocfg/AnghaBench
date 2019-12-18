#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_6__ {scalar_t__ state; TYPE_2__** hw_eq; } ;
typedef  TYPE_1__ ocs_hw_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_7__ {int /*<<< orphan*/  use_count; } ;
typedef  TYPE_2__ hw_eq_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPUTRACE (char*) ; 
 scalar_t__ OCS_HW_STATE_UNINITIALIZED ; 
 int /*<<< orphan*/  OCS_STAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_hw_eq_process (TYPE_1__*,TYPE_2__*,size_t) ; 

int32_t
ocs_hw_process(ocs_hw_t *hw, uint32_t vector, uint32_t max_isr_time_msec)
{
	hw_eq_t *eq;
	int32_t rc = 0;

	CPUTRACE("");

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
	if (hw->state == OCS_HW_STATE_UNINITIALIZED) {
		return 0;
	}

	/* Get pointer to hw_eq_t */
	eq = hw->hw_eq[vector];

	OCS_STAT(eq->use_count++);

	rc = ocs_hw_eq_process(hw, eq, max_isr_time_msec);

	return rc;
}