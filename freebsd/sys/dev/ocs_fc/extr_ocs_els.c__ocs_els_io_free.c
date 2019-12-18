#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  active_ios_lock; scalar_t__ els_pend; int /*<<< orphan*/  els_io_pend_list; scalar_t__ els_active; int /*<<< orphan*/  els_io_active_list; int /*<<< orphan*/  io_alloc_enabled; struct TYPE_11__* ocs; struct TYPE_11__* node; } ;
typedef  TYPE_1__ ocs_t ;
typedef  TYPE_1__ ocs_node_t ;
typedef  TYPE_1__ ocs_io_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  OCS_EVT_ALL_CHILD_NODES_FREE ; 
 int /*<<< orphan*/  ocs_assert (TYPE_1__*) ; 
 int /*<<< orphan*/  ocs_io_free (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ ocs_list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_list_remove (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ocs_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_log_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  ocs_node_post_event (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_scsi_check_pending (TYPE_1__*) ; 
 int /*<<< orphan*/  ocs_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
_ocs_els_io_free(void *arg)
{
	ocs_io_t *els = (ocs_io_t *)arg;
	ocs_t *ocs;
	ocs_node_t *node;
	int send_empty_event = FALSE;

	ocs_assert(els);
	ocs_assert(els->node);
	ocs_assert(els->node->ocs);
	ocs = els->node->ocs;

	node = els->node;
	ocs = node->ocs;

	ocs_lock(&node->active_ios_lock);
		if (els->els_active) {
			/* if active, remove from active list and check empty */
			ocs_list_remove(&node->els_io_active_list, els);
			/* Send list empty event if the IO allocator is disabled, and the list is empty
			 * If node->io_alloc_enabled was not checked, the event would be posted continually
			 */
			send_empty_event = (!node->io_alloc_enabled) && ocs_list_empty(&node->els_io_active_list);
			els->els_active = 0;
		} else if (els->els_pend) {
			/* if pending, remove from pending list; node shutdown isn't
			 * gated off the pending list (only the active list), so no
			 * need to check if pending list is empty
			 */
			ocs_list_remove(&node->els_io_pend_list, els);
			els->els_pend = 0;
		} else {
			ocs_log_err(ocs, "assertion failed: niether els->els_pend nor els->active set\n");
			ocs_unlock(&node->active_ios_lock);
			return;
		}

	ocs_unlock(&node->active_ios_lock);

	ocs_io_free(ocs, els);

	if (send_empty_event) {
		ocs_node_post_event(node, OCS_EVT_ALL_CHILD_NODES_FREE, NULL);
	}

	ocs_scsi_check_pending(ocs);
}