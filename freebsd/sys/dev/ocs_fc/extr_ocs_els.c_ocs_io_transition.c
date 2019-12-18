#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ocs_sm_function_t ;
typedef  int /*<<< orphan*/  ocs_node_t ;
struct TYPE_3__ {int /*<<< orphan*/  els_sm; int /*<<< orphan*/ * node; } ;
typedef  TYPE_1__ ocs_io_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_node_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_node_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_sm_transition (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void
ocs_io_transition(ocs_io_t *els, ocs_sm_function_t state, void *data)
{
	/* protect ELS events with node lock */
	ocs_node_t *node = els->node;
	ocs_node_lock(node);
		ocs_sm_transition(&els->els_sm, state, data);
	ocs_node_unlock(node);
}