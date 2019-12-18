#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  active_ios_lock; int /*<<< orphan*/  ocs; int /*<<< orphan*/  els_io_active_list; int /*<<< orphan*/  els_io_pend_list; } ;
typedef  TYPE_1__ ocs_node_t ;
struct TYPE_7__ {int els_active; scalar_t__ els_pend; TYPE_1__* node; } ;
typedef  TYPE_2__ ocs_io_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_list_add_tail (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ocs_list_remove (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ocs_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ocs_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ocs_els_make_active(ocs_io_t *els)
{
	ocs_node_t *node = els->node;

	/* move ELS from pending list to active list */
	ocs_lock(&node->active_ios_lock);
		if (els->els_pend) {
			if (els->els_active) {
				ocs_log_err(node->ocs, "assertion failed: both els->els_pend and els->active set\n");
				ocs_unlock(&node->active_ios_lock);
				return;
			} else {

				/* remove from pending list */
				ocs_list_remove(&node->els_io_pend_list, els);
				els->els_pend = 0;

				/* add els structure to ELS IO list */
				ocs_list_add_tail(&node->els_io_active_list, els);
				els->els_active = 1;
			}
		} else {
			/* must be retrying; make sure it's already active */
			if (!els->els_active) {
				ocs_log_err(node->ocs, "assertion failed: niether els->els_pend nor els->active set\n");
			}
		}
	ocs_unlock(&node->active_ios_lock);
}