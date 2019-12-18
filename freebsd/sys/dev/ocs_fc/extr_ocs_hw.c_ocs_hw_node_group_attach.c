#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  index; int /*<<< orphan*/  indicator; int /*<<< orphan*/  fc_id; scalar_t__ attached; } ;
typedef  TYPE_1__ ocs_remote_node_t ;
struct TYPE_9__ {int /*<<< orphan*/  index; int /*<<< orphan*/  indicator; } ;
typedef  TYPE_2__ ocs_remote_node_group_t ;
struct TYPE_10__ {int /*<<< orphan*/  os; int /*<<< orphan*/  sli; } ;
typedef  TYPE_3__ ocs_hw_t ;
typedef  int /*<<< orphan*/  ocs_hw_rtn_e ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_HW_RTN_ERROR ; 
 int /*<<< orphan*/  OCS_HW_RTN_SUCCESS ; 
 int /*<<< orphan*/  SLI_RSRC_FCOE_RPI ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*,TYPE_3__*,...) ; 
 scalar_t__ sli_resource_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ocs_hw_rtn_e
ocs_hw_node_group_attach(ocs_hw_t *hw, ocs_remote_node_group_t *ngroup, ocs_remote_node_t *rnode)
{

	if (!hw || !ngroup || !rnode) {
		ocs_log_err(NULL, "bad parameter hw=%p ngroup=%p rnode=%p\n",
			    hw, ngroup, rnode);
		return OCS_HW_RTN_ERROR;
	}

	if (rnode->attached) {
		ocs_log_err(hw->os, "node already attached RPI=%#x addr=%#x\n",
			    rnode->indicator, rnode->fc_id);
		return OCS_HW_RTN_ERROR;
	}

	if (sli_resource_free(&hw->sli, SLI_RSRC_FCOE_RPI, rnode->indicator)) {
		ocs_log_err(hw->os, "FCOE_RPI free failure RPI=%#x\n",
				rnode->indicator);
		return OCS_HW_RTN_ERROR;
	}

	rnode->indicator = ngroup->indicator;
	rnode->index = ngroup->index;

	return OCS_HW_RTN_SUCCESS;
}