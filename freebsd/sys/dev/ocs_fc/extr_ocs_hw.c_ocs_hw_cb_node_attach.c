#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_12__ {scalar_t__ status; } ;
typedef  TYPE_4__ sli4_mbox_command_header_t ;
struct TYPE_13__ {size_t index; int /*<<< orphan*/  attached; } ;
typedef  TYPE_5__ ocs_remote_node_t ;
struct TYPE_11__ {int /*<<< orphan*/  rnode; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* rnode ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ;} ;
struct TYPE_14__ {int /*<<< orphan*/  os; TYPE_3__ args; TYPE_2__ callback; TYPE_1__* rpi_ref; } ;
typedef  TYPE_6__ ocs_hw_t ;
typedef  int /*<<< orphan*/  ocs_hw_remote_node_event_e ;
typedef  scalar_t__ int32_t ;
struct TYPE_9__ {int /*<<< orphan*/  rpi_attached; int /*<<< orphan*/  rpi_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  OCS_HW_NODE_ATTACH_FAIL ; 
 int /*<<< orphan*/  OCS_HW_NODE_ATTACH_OK ; 
 int /*<<< orphan*/  SLI4_BMBX_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ocs_atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ocs_atomic_sub_return (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_log_debug (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 

__attribute__((used)) static int32_t
ocs_hw_cb_node_attach(ocs_hw_t *hw, int32_t status, uint8_t *mqe, void *arg)
{
	ocs_remote_node_t *rnode = arg;
	sli4_mbox_command_header_t	*hdr = (sli4_mbox_command_header_t *)mqe;
	ocs_hw_remote_node_event_e	evt = 0;

	if (status || hdr->status) {
		ocs_log_debug(hw->os, "bad status cqe=%#x mqe=%#x\n", status,
				hdr->status);
		ocs_atomic_sub_return(&hw->rpi_ref[rnode->index].rpi_count, 1);
		rnode->attached = FALSE;
		ocs_atomic_set(&hw->rpi_ref[rnode->index].rpi_attached, 0);
		evt = OCS_HW_NODE_ATTACH_FAIL;
	} else {
		rnode->attached = TRUE;
		ocs_atomic_set(&hw->rpi_ref[rnode->index].rpi_attached, 1);
		evt = OCS_HW_NODE_ATTACH_OK;
	}

	if (hw->callback.rnode != NULL) {
		hw->callback.rnode(hw->args.rnode, evt, rnode);
	}
	ocs_free(hw->os, mqe, SLI4_BMBX_SIZE);

	return 0;
}