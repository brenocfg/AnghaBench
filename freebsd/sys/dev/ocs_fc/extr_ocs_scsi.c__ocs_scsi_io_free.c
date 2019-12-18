#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ocs_t ;
struct TYPE_9__ {int /*<<< orphan*/  active_ios_lock; int /*<<< orphan*/  active_ios; int /*<<< orphan*/  io_alloc_enabled; } ;
typedef  TYPE_1__ ocs_node_t ;
struct TYPE_10__ {TYPE_1__* node; int /*<<< orphan*/  display_name; int /*<<< orphan*/ * ocs; } ;
typedef  TYPE_2__ ocs_io_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_EVT_NODE_ACTIVE_IO_LIST_EMPTY ; 
 int /*<<< orphan*/  ocs_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_io_busy (TYPE_2__*) ; 
 int /*<<< orphan*/  ocs_io_free (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ ocs_list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_list_remove (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ocs_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_node_post_event (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_io_trace (TYPE_2__*,char*,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_ocs_scsi_io_free(void *arg)
{
	ocs_io_t *io = (ocs_io_t *)arg;
	ocs_t *ocs = io->ocs;
	ocs_node_t *node = io->node;
	int send_empty_event;

	ocs_assert(io != NULL);

	scsi_io_trace(io, "freeing io 0x%p %s\n", io, io->display_name);

	ocs_assert(ocs_io_busy(io));

	ocs_lock(&node->active_ios_lock);
		ocs_list_remove(&node->active_ios, io);
		send_empty_event = (!node->io_alloc_enabled) && ocs_list_empty(&node->active_ios);
	ocs_unlock(&node->active_ios_lock);

	if (send_empty_event) {
		ocs_node_post_event(node, OCS_EVT_NODE_ACTIVE_IO_LIST_EMPTY, NULL);
	}

	io->node = NULL;
	ocs_io_free(ocs, io);

}