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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {scalar_t__ state; int /*<<< orphan*/  sli; } ;
typedef  TYPE_1__ ocs_hw_t ;
typedef  int /*<<< orphan*/  ocs_hw_rtn_e ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_HW_RTN_ERROR ; 
 int /*<<< orphan*/  OCS_HW_RTN_SUCCESS ; 
 scalar_t__ OCS_HW_STATE_QUEUES_ALLOCATED ; 
 scalar_t__ OCS_HW_STATE_UNINITIALIZED ; 
 scalar_t__ sli_raise_ue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

ocs_hw_rtn_e
ocs_hw_raise_ue(ocs_hw_t *hw, uint8_t dump)
{
	ocs_hw_rtn_e rc = OCS_HW_RTN_SUCCESS;

	if (sli_raise_ue(&hw->sli, dump) != 0) {
		rc = OCS_HW_RTN_ERROR;
	} else {
		if (hw->state != OCS_HW_STATE_UNINITIALIZED) {
			hw->state = OCS_HW_STATE_QUEUES_ALLOCATED;
		}
	}

	return rc;
}