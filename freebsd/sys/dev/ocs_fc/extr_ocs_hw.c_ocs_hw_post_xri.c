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
typedef  int /*<<< orphan*/  uint32_t ;
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
 int /*<<< orphan*/  ocs_hw_cb_post_xri ; 
 scalar_t__ ocs_hw_command (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * ocs_malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sli_cmd_post_xri (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ocs_hw_rtn_e
ocs_hw_post_xri(ocs_hw_t *hw, uint32_t xri_start, uint32_t num_to_post)
{
	uint8_t	*post_xri;
	ocs_hw_rtn_e rc = OCS_HW_RTN_ERROR;

	/* Since we need to allocate for mailbox queue, just always allocate */
	post_xri = ocs_malloc(hw->os, SLI4_BMBX_SIZE, OCS_M_NOWAIT);
	if (post_xri == NULL) {
		ocs_log_err(hw->os, "no buffer for command\n");
		return OCS_HW_RTN_NO_MEMORY;
	}

	/* Register the XRIs */
	if (sli_cmd_post_xri(&hw->sli, post_xri, SLI4_BMBX_SIZE,
			     xri_start, num_to_post)) {
		rc = ocs_hw_command(hw, post_xri, OCS_CMD_NOWAIT, ocs_hw_cb_post_xri, NULL);
		if (rc != OCS_HW_RTN_SUCCESS) {
			ocs_free(hw->os, post_xri, SLI4_BMBX_SIZE);
			ocs_log_err(hw->os, "post_xri failed\n");
		}
	}
	return rc;
}