#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {int if_type; int /*<<< orphan*/  os; } ;
typedef  TYPE_1__ sli4_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_FW_READY_TIMEOUT_MSEC ; 
#define  SLI4_IF_TYPE_BE3_SKH_PF 129 
#define  SLI4_IF_TYPE_LANCER_FC_ETH 128 
 int /*<<< orphan*/  SLI4_PCI_SOFT_RESET_CSR ; 
 scalar_t__ SLI4_PCI_SOFT_RESET_MASK ; 
 scalar_t__ SLI4_PHYDEV_CONTROL_FRST ; 
 int /*<<< orphan*/  SLI4_REG_PHYSDEV_CONTROL ; 
 scalar_t__ ocs_config_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_config_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ocs_log_crit (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sli_reg_write (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ sli_wait_for_fw_ready (TYPE_1__*,int /*<<< orphan*/ ) ; 

int32_t
sli_fw_reset(sli4_t *sli4)
{
	uint32_t val;
	uint32_t ready;

	/*
	 * Firmware must be ready before issuing the reset.
	 */
	ready = sli_wait_for_fw_ready(sli4, SLI4_FW_READY_TIMEOUT_MSEC);
	if (!ready) {
		ocs_log_crit(sli4->os, "FW status is NOT ready\n");
		return -1;
	}
	switch(sli4->if_type) {
	case SLI4_IF_TYPE_BE3_SKH_PF:
		/* BE3 / Skyhawk use PCICFG_SOFT_RESET_CSR */
		val = ocs_config_read32(sli4->os, SLI4_PCI_SOFT_RESET_CSR);
		val |= SLI4_PCI_SOFT_RESET_MASK;
		ocs_config_write32(sli4->os, SLI4_PCI_SOFT_RESET_CSR, val);
		break;
	case SLI4_IF_TYPE_LANCER_FC_ETH:
		/* Lancer uses PHYDEV_CONTROL */

		val = SLI4_PHYDEV_CONTROL_FRST;
		sli_reg_write(sli4, SLI4_REG_PHYSDEV_CONTROL, val);
		break;
	default:
		ocs_log_test(sli4->os, "Unexpected iftype %d\n", sli4->if_type);
		return -1;
		break;
	}

	/* wait for the FW to become ready after the reset */
	ready = sli_wait_for_fw_ready(sli4, SLI4_FW_READY_TIMEOUT_MSEC);
	if (!ready) {
		ocs_log_crit(sli4->os, "Failed to become ready after firmware reset\n");
		return -1;
	}
	return 0;
}