#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ocs_sm_event_t ;
typedef  int /*<<< orphan*/  ocs_node_t ;
struct TYPE_4__ {scalar_t__ els_evtdepth; scalar_t__ els_req_free; int /*<<< orphan*/  els_sm; int /*<<< orphan*/ * node; } ;
typedef  TYPE_1__ ocs_io_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_els_io_free (TYPE_1__*) ; 
 int /*<<< orphan*/  ocs_node_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_node_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_sm_post_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 

void
ocs_els_post_event(ocs_io_t *els, ocs_sm_event_t evt, void *data)
{
	/* protect ELS events with node lock */
	ocs_node_t *node = els->node;
	ocs_node_lock(node);
		els->els_evtdepth ++;
		ocs_sm_post_event(&els->els_sm, evt, data);
		els->els_evtdepth --;
	ocs_node_unlock(node);
	if (els->els_evtdepth == 0 && els->els_req_free) {
		ocs_els_io_free(els);
	}
}