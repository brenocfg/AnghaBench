#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  void* uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  os; int /*<<< orphan*/  sli; int /*<<< orphan*/  domain_dmem; } ;
typedef  TYPE_1__ ocs_hw_t ;
typedef  int /*<<< orphan*/  ocs_hw_rtn_e ;
struct TYPE_8__ {TYPE_2__* app; } ;
struct TYPE_7__ {TYPE_3__ sm; void* indicator; void* vlan_id; void* fcf_indicator; void* fcf; TYPE_1__* hw; int /*<<< orphan*/  dma; int /*<<< orphan*/ * sport; } ;
typedef  TYPE_2__ ocs_domain_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_HW_RTN_ERROR ; 
 int /*<<< orphan*/  OCS_HW_RTN_NO_MEMORY ; 
 int /*<<< orphan*/  OCS_HW_RTN_SUCCESS ; 
 int OCS_M_NOWAIT ; 
 int OCS_M_ZERO ; 
 int /*<<< orphan*/  SLI4_BMBX_SIZE ; 
 int /*<<< orphan*/  SLI_RSRC_FCOE_VFI ; 
 void* UINT32_MAX ; 
 int /*<<< orphan*/  __ocs_hw_domain_init ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_log_crit (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * ocs_malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocs_sm_transition (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ sli_fw_error_status (int /*<<< orphan*/ *) ; 
 scalar_t__ sli_resource_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**,void**) ; 

ocs_hw_rtn_e
ocs_hw_domain_alloc(ocs_hw_t *hw, ocs_domain_t *domain, uint32_t fcf, uint32_t vlan)
{
	uint8_t		*cmd = NULL;
	uint32_t	index;

	if (!hw || !domain || !domain->sport) {
		ocs_log_err(NULL, "bad parameter(s) hw=%p domain=%p sport=%p\n",
				hw, domain, domain ? domain->sport : NULL);
		return OCS_HW_RTN_ERROR;
	}

	/*
	 * Check if the chip is in an error state (UE'd) before proceeding.
	 */
	if (sli_fw_error_status(&hw->sli) > 0) {
		ocs_log_crit(hw->os, "Chip is in an error state - reset needed\n");
		return OCS_HW_RTN_ERROR;
	}

	cmd = ocs_malloc(hw->os, SLI4_BMBX_SIZE, OCS_M_ZERO | OCS_M_NOWAIT);
	if (!cmd) {
		ocs_log_err(hw->os, "command memory allocation failed\n");
		return OCS_HW_RTN_NO_MEMORY;
	}

	domain->dma = hw->domain_dmem;

	domain->hw = hw;
	domain->sm.app = domain;
	domain->fcf = fcf;
	domain->fcf_indicator = UINT32_MAX;
	domain->vlan_id = vlan;
	domain->indicator = UINT32_MAX;

	if (sli_resource_alloc(&hw->sli, SLI_RSRC_FCOE_VFI, &domain->indicator, &index)) {
		ocs_log_err(hw->os, "FCOE_VFI allocation failure\n");

		ocs_free(hw->os, cmd, SLI4_BMBX_SIZE);

		return OCS_HW_RTN_ERROR;
	}

	ocs_sm_transition(&domain->sm, __ocs_hw_domain_init, cmd);
	return OCS_HW_RTN_SUCCESS;
}