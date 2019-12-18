#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  os; int /*<<< orphan*/  sli; } ;
typedef  TYPE_1__ ocs_hw_t ;
typedef  scalar_t__ ocs_hw_rtn_e ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_CMD_NOWAIT ; 
 scalar_t__ OCS_HW_RTN_ERROR ; 
 scalar_t__ OCS_HW_RTN_NO_MEMORY ; 
 scalar_t__ OCS_HW_RTN_SUCCESS ; 
 int /*<<< orphan*/  OCS_M_NOWAIT ; 
 int /*<<< orphan*/  SLI4_BMBX_SIZE ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_hw_cb_release_xri ; 
 scalar_t__ ocs_hw_command (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * ocs_malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sli_cmd_release_xri (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ocs_hw_rtn_e
ocs_hw_xri_move_to_host_owned(ocs_hw_t *hw, uint8_t num_xri)
{
	uint8_t	*release_xri;
	ocs_hw_rtn_e rc = OCS_HW_RTN_ERROR;

	/* non-local buffer required for mailbox queue */
	release_xri = ocs_malloc(hw->os, SLI4_BMBX_SIZE, OCS_M_NOWAIT);
	if (release_xri == NULL) {
		ocs_log_err(hw->os, "no buffer for command\n");
		return OCS_HW_RTN_NO_MEMORY;
	}

	/* release the XRIs */
	if (sli_cmd_release_xri(&hw->sli, release_xri, SLI4_BMBX_SIZE, num_xri)) {
		rc = ocs_hw_command(hw, release_xri, OCS_CMD_NOWAIT, ocs_hw_cb_release_xri, NULL);
		if (rc != OCS_HW_RTN_SUCCESS) {
			ocs_log_err(hw->os, "release_xri failed\n");
		}
	}
	/* If we are polling or an error occurred, then free the mailbox buffer */
	if (release_xri != NULL && rc != OCS_HW_RTN_SUCCESS) {
		ocs_free(hw->os, release_xri, SLI4_BMBX_SIZE);
	}
	return rc;
}