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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  ctx; int /*<<< orphan*/  fc_id; } ;
typedef  TYPE_1__ ocs_sli_port_t ;
struct TYPE_6__ {int /*<<< orphan*/ * os; int /*<<< orphan*/  sli; } ;
typedef  TYPE_2__ ocs_hw_t ;
typedef  int /*<<< orphan*/  ocs_hw_rtn_e ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_EVT_HW_PORT_REQ_ATTACH ; 
 int /*<<< orphan*/  OCS_HW_RTN_ERROR ; 
 int /*<<< orphan*/  OCS_HW_RTN_NO_MEMORY ; 
 int /*<<< orphan*/  OCS_HW_RTN_SUCCESS ; 
 int /*<<< orphan*/  OCS_M_NOWAIT ; 
 int /*<<< orphan*/  SLI4_BMBX_SIZE ; 
 int /*<<< orphan*/  ocs_log_crit (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/ * ocs_malloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_sm_post_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ sli_fw_error_status (int /*<<< orphan*/ *) ; 

ocs_hw_rtn_e
ocs_hw_port_attach(ocs_hw_t *hw, ocs_sli_port_t *sport, uint32_t fc_id)
{
	uint8_t	*buf = NULL;
	ocs_hw_rtn_e rc = OCS_HW_RTN_SUCCESS;

	if (!hw || !sport) {
		ocs_log_err(hw ? hw->os : NULL,
			"bad parameter(s) hw=%p sport=%p\n", hw,
			sport);
		return OCS_HW_RTN_ERROR;
	}

	/*
	 * Check if the chip is in an error state (UE'd) before proceeding.
	 */
	if (sli_fw_error_status(&hw->sli) > 0) {
		ocs_log_crit(hw->os, "Chip is in an error state - reset needed\n");
		return OCS_HW_RTN_ERROR;
	}

	buf = ocs_malloc(hw->os, SLI4_BMBX_SIZE, OCS_M_NOWAIT);
	if (!buf) {
		ocs_log_err(hw->os, "no buffer for command\n");
		return OCS_HW_RTN_NO_MEMORY;
	}

	sport->fc_id = fc_id;
	ocs_sm_post_event(&sport->ctx, OCS_EVT_HW_PORT_REQ_ATTACH, buf);
	return rc;
}