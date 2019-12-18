#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {int n_wq; int n_io; } ;
struct TYPE_6__ {int* num_qentries; TYPE_1__ config; int /*<<< orphan*/  sli; } ;
typedef  TYPE_2__ ocs_hw_t ;

/* Variables and functions */
 int OCS_HW_MAX_NUM_WQ ; 
 scalar_t__ SLI4_IF_TYPE_BE3_SKH_PF ; 
 size_t SLI_QTYPE_CQ ; 
 size_t SLI_QTYPE_WQ ; 
 int ocs_hw_get_num_chutes (TYPE_2__*) ; 
 scalar_t__ sli_get_if_type (int /*<<< orphan*/ *) ; 
 int sli_get_max_queue (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void
ocs_hw_adjust_wqs(ocs_hw_t *hw)
{
	uint32_t max_wq_num = sli_get_max_queue(&hw->sli, SLI_QTYPE_WQ);
	uint32_t max_wq_entries = hw->num_qentries[SLI_QTYPE_WQ];
	uint32_t max_cq_entries = hw->num_qentries[SLI_QTYPE_CQ];

	/*
	 * possibly adjust the the size of the WQs so that the CQ is twice as
	 * big as the WQ to allow for 2 completions per IO. This allows us to
	 * handle multi-phase as well as aborts.
	 */
	if (max_cq_entries < max_wq_entries * 2) {
		max_wq_entries = hw->num_qentries[SLI_QTYPE_WQ] = max_cq_entries / 2;
	}

	/*
	 * Calculate the number of WQs to use base on the number of IOs.
	 *
	 * Note: We need to reserve room for aborts which must be sent down
	 *       the same WQ as the IO. So we allocate enough WQ space to
	 *       handle 2 times the number of IOs. Half of the space will be
	 *       used for normal IOs and the other hwf is reserved for aborts.
	 */
	hw->config.n_wq = ((hw->config.n_io * 2) + (max_wq_entries - 1)) / max_wq_entries;

	/*
	 * For performance reasons, it is best to use use a minimum of 4 WQs
	 * for BE3 and Skyhawk.
	 */
	if (hw->config.n_wq < 4 &&
	    SLI4_IF_TYPE_BE3_SKH_PF == sli_get_if_type(&hw->sli)) {
		hw->config.n_wq = 4;
	}

	/*
	 * For dual-chute support, we need to have at least one WQ per chute.
	 */
	if (hw->config.n_wq < 2 &&
	    ocs_hw_get_num_chutes(hw) > 1) {
		hw->config.n_wq = 2;
	}

	/* make sure we haven't exceeded the max supported in the HW */
	if (hw->config.n_wq > OCS_HW_MAX_NUM_WQ) {
		hw->config.n_wq = OCS_HW_MAX_NUM_WQ;
	}

	/* make sure we haven't exceeded the chip maximum */
	if (hw->config.n_wq > max_wq_num) {
		hw->config.n_wq = max_wq_num;
	}

	/*
	 * Using Queue Topology string, we divide by number of chutes
	 */
	hw->config.n_wq /= ocs_hw_get_num_chutes(hw);
}