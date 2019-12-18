#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ocs_sm_event_t ;
struct TYPE_8__ {int evtdepth; scalar_t__ req_free; int /*<<< orphan*/  hold_frames; int /*<<< orphan*/  sm; } ;
typedef  TYPE_1__ ocs_node_t ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  ocs_assert (TYPE_1__*) ; 
 int /*<<< orphan*/  ocs_node_free (TYPE_1__*) ; 
 int /*<<< orphan*/  ocs_node_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  ocs_node_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  ocs_process_node_pending (TYPE_1__*) ; 
 int /*<<< orphan*/  ocs_sm_post_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 

void
ocs_node_post_event(ocs_node_t *node, ocs_sm_event_t evt, void *arg)
{
	int free_node = FALSE;
	ocs_assert(node);

	ocs_node_lock(node);
		node->evtdepth ++;

		ocs_sm_post_event(&node->sm, evt, arg);

		/* If our event call depth is one and we're not holding frames
		 * then we can dispatch any pending frames.   We don't want to allow
		 * the ocs_process_node_pending() call to recurse.
		 */
		if (!node->hold_frames && (node->evtdepth == 1)) {
			ocs_process_node_pending(node);
		}
		node->evtdepth --;

		/* Free the node object if so requested, and we're at an event
		 * call depth of zero
		 */
		if ((node->evtdepth == 0) && node->req_free) {
			free_node = TRUE;
		}
	ocs_node_unlock(node);

	if (free_node) {
		ocs_node_free(node);
	}

	return;
}