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
typedef  int /*<<< orphan*/  ocs_sm_function_t ;
struct TYPE_4__ {int /*<<< orphan*/  nodedb_state; } ;
typedef  TYPE_1__ ocs_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  __ocs_node_paused ; 
 int /*<<< orphan*/  ocs_node_transition (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
ocs_node_pause(ocs_node_t *node, ocs_sm_function_t state)
{
	node->nodedb_state = state;
	ocs_node_transition(node, __ocs_node_paused, NULL);
}