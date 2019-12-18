#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ocs_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_EVT_NODE_DEL_INI_COMPLETE ; 
 int /*<<< orphan*/  ocs_node_post_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
ocs_scsi_del_initiator_complete(ocs_node_t *node)
{
	/* Notify the node to resume */
	ocs_node_post_event(node, OCS_EVT_NODE_DEL_INI_COMPLETE, NULL);
}