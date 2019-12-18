#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ocs_sm_function_t ;
struct TYPE_7__ {scalar_t__ current_state; } ;
typedef  TYPE_1__ ocs_sm_ctx_t ;
struct TYPE_8__ {TYPE_1__ sm; } ;
typedef  TYPE_2__ ocs_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_EVT_ENTER ; 
 int /*<<< orphan*/  OCS_EVT_EXIT ; 
 int /*<<< orphan*/  OCS_EVT_REENTER ; 
 int /*<<< orphan*/  ocs_node_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  ocs_node_post_event (TYPE_2__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ocs_node_unlock (TYPE_2__*) ; 

void
ocs_node_transition(ocs_node_t *node, ocs_sm_function_t state, void *data)
{
	ocs_sm_ctx_t *ctx = &node->sm;

	ocs_node_lock(node);
		if (ctx->current_state == state) {
			ocs_node_post_event(node, OCS_EVT_REENTER, data);
		} else {
			ocs_node_post_event(node, OCS_EVT_EXIT, data);
			ctx->current_state = state;
			ocs_node_post_event(node, OCS_EVT_ENTER, data);
		}
	ocs_node_unlock(node);
}