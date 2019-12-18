#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {scalar_t__ send_ls_acc; int /*<<< orphan*/  ls_acc_did; TYPE_2__* ls_acc_io; int /*<<< orphan*/  ls_acc_oxid; } ;
typedef  TYPE_1__ ocs_node_t ;
typedef  scalar_t__ ocs_node_send_ls_acc_e ;
struct TYPE_7__ {TYPE_1__* node; } ;
typedef  TYPE_2__ ocs_io_t ;
struct TYPE_8__ {int /*<<< orphan*/  d_id; int /*<<< orphan*/  ox_id; } ;
typedef  TYPE_3__ fc_header_t ;

/* Variables and functions */
 scalar_t__ OCS_NODE_SEND_LS_ACC_NONE ; 
 int /*<<< orphan*/  fc_be24toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_assert (int) ; 
 int /*<<< orphan*/  ocs_be16toh (int /*<<< orphan*/ ) ; 

void
ocs_send_ls_acc_after_attach(ocs_io_t *io, fc_header_t *hdr, ocs_node_send_ls_acc_e ls)
{
	ocs_node_t *node = io->node;
	uint16_t ox_id = ocs_be16toh(hdr->ox_id);

	ocs_assert(node->send_ls_acc == OCS_NODE_SEND_LS_ACC_NONE);

	node->ls_acc_oxid = ox_id;
	node->send_ls_acc = ls;
	node->ls_acc_io = io;
	node->ls_acc_did = fc_be24toh(hdr->d_id);
}