#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ocs_t ;
struct TYPE_5__ {scalar_t__ send_ls_acc; TYPE_3__* ls_acc_io; int /*<<< orphan*/  ls_acc_oxid; int /*<<< orphan*/  display_name; int /*<<< orphan*/ * ocs; } ;
typedef  TYPE_1__ ocs_node_t ;
struct TYPE_6__ {int /*<<< orphan*/ * hio; } ;

/* Variables and functions */
 scalar_t__ OCS_NODE_SEND_LS_ACC_NONE ; 
 int /*<<< orphan*/  ocs_assert (TYPE_3__*) ; 
 int /*<<< orphan*/  ocs_els_io_free (TYPE_3__*) ; 
 int /*<<< orphan*/  ocs_log_debug (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ocs_node_send_ls_io_cleanup(ocs_node_t *node)
{
	ocs_t *ocs = node->ocs;

	if (node->send_ls_acc != OCS_NODE_SEND_LS_ACC_NONE) {
		ocs_assert(node->ls_acc_io);
		ocs_log_debug(ocs, "[%s] cleaning up LS_ACC oxid=0x%x\n",
			node->display_name, node->ls_acc_oxid);

		node->ls_acc_io->hio = NULL;
		ocs_els_io_free(node->ls_acc_io);
		node->send_ls_acc = OCS_NODE_SEND_LS_ACC_NONE;
		node->ls_acc_io = NULL;
	}
}