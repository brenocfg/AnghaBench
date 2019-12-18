#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  hw; } ;
typedef  TYPE_1__ ocs_t ;
struct TYPE_10__ {scalar_t__ free_group; } ;
struct TYPE_9__ {TYPE_5__ rnode; int /*<<< orphan*/ * node_group; scalar_t__ attached; TYPE_1__* ocs; } ;
typedef  TYPE_2__ ocs_node_t ;
typedef  scalar_t__ ocs_hw_rtn_e ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ OCS_HW_RTN_SUCCESS ; 
 scalar_t__ OCS_HW_RTN_SUCCESS_SYNC ; 
 int /*<<< orphan*/  node_printf (TYPE_2__*,char*,scalar_t__) ; 
 scalar_t__ ocs_hw_node_detach (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  ocs_node_initiate_cleanup (TYPE_2__*) ; 
 int /*<<< orphan*/  ocs_remote_node_group_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_scsi_io_alloc_disable (TYPE_2__*) ; 

__attribute__((used)) static void
ocs_fabric_initiate_shutdown(ocs_node_t *node)
{
	ocs_hw_rtn_e rc;
	ocs_t *ocs = node->ocs;
	ocs_scsi_io_alloc_disable(node);

	if (node->attached) {
		/* issue hw node free; don't care if succeeds right away
		 * or sometime later, will check node->attached later in
		 * shutdown process
		 */
		rc = ocs_hw_node_detach(&ocs->hw, &node->rnode);
		if (node->rnode.free_group) {
			ocs_remote_node_group_free(node->node_group);
			node->node_group = NULL;
			node->rnode.free_group = FALSE;
		}
		if (rc != OCS_HW_RTN_SUCCESS && rc != OCS_HW_RTN_SUCCESS_SYNC) {
			node_printf(node, "Failed freeing HW node, rc=%d\n", rc);
		}
	}
	/*
	 * node has either been detached or is in the process of being detached,
	 * call common node's initiate cleanup function
	 */
	ocs_node_initiate_cleanup(node);
}