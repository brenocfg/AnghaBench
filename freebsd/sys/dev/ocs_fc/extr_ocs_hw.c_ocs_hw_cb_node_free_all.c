#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
struct TYPE_10__ {scalar_t__ status; } ;
typedef  TYPE_4__ sli4_mbox_command_header_t ;
struct TYPE_9__ {int /*<<< orphan*/  rnode; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* rnode ) (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  os; TYPE_3__ args; TYPE_2__ callback; int /*<<< orphan*/  sli; TYPE_1__* rpi_ref; } ;
typedef  TYPE_5__ ocs_hw_t ;
typedef  scalar_t__ ocs_hw_remote_node_event_e ;
typedef  int int32_t ;
struct TYPE_7__ {int /*<<< orphan*/  rpi_count; } ;

/* Variables and functions */
 scalar_t__ OCS_HW_NODE_FREE_ALL_OK ; 
 scalar_t__ OCS_HW_NODE_FREE_FAIL ; 
 int /*<<< orphan*/  SLI4_BMBX_SIZE ; 
 int /*<<< orphan*/  SLI_RSRC_FCOE_RPI ; 
 int /*<<< orphan*/  ocs_atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_log_debug (int /*<<< orphan*/ ,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*) ; 
 size_t sli_get_max_rsrc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sli_resource_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int32_t
ocs_hw_cb_node_free_all(ocs_hw_t *hw, int32_t status, uint8_t *mqe, void *arg)
{
	sli4_mbox_command_header_t	*hdr = (sli4_mbox_command_header_t *)mqe;
	ocs_hw_remote_node_event_e	evt = OCS_HW_NODE_FREE_FAIL;
	int32_t		rc = 0;
	uint32_t	i;

	if (status || hdr->status) {
		ocs_log_debug(hw->os, "bad status cqe=%#x mqe=%#x\n", status,
				hdr->status);
	} else {
		evt = OCS_HW_NODE_FREE_ALL_OK;
	}

	if (evt == OCS_HW_NODE_FREE_ALL_OK) {
		for (i = 0; i < sli_get_max_rsrc(&hw->sli, SLI_RSRC_FCOE_RPI); i++) {
			ocs_atomic_set(&hw->rpi_ref[i].rpi_count, 0);
		}

		if (sli_resource_reset(&hw->sli, SLI_RSRC_FCOE_RPI)) {
			ocs_log_test(hw->os, "FCOE_RPI free all failure\n");
			rc = -1;
		}
	}

	if (hw->callback.rnode != NULL) {
		hw->callback.rnode(hw->args.rnode, evt, NULL);
	}

	ocs_free(hw->os, mqe, SLI4_BMBX_SIZE);

	return rc;
}