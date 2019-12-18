#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  shutdown_reason; int /*<<< orphan*/  display_name; struct TYPE_9__* ocs; struct TYPE_9__* app; } ;
typedef  TYPE_1__ ocs_t ;
typedef  int ocs_sm_event_t ;
typedef  TYPE_1__ ocs_sm_ctx_t ;
typedef  TYPE_1__ ocs_node_t ;

/* Variables and functions */
#define  OCS_EVT_SHUTDOWN 130 
#define  OCS_EVT_SHUTDOWN_EXPLICIT_LOGO 129 
#define  OCS_EVT_SHUTDOWN_IMPLICIT_LOGO 128 
 int /*<<< orphan*/  OCS_NODE_SHUTDOWN_DEFAULT ; 
 int /*<<< orphan*/  OCS_NODE_SHUTDOWN_EXPLICIT_LOGO ; 
 int /*<<< orphan*/  OCS_NODE_SHUTDOWN_IMPLICIT_LOGO ; 
 int /*<<< orphan*/  __ocs_d_initiate_shutdown ; 
 int /*<<< orphan*/  __ocs_node_common (char const*,TYPE_1__*,int,void*) ; 
 int /*<<< orphan*/  ocs_assert (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_log_debug (TYPE_1__*,char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_node_transition (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_sm_event_name (int) ; 

__attribute__((used)) static void *
__ocs_d_common(const char *funcname, ocs_sm_ctx_t *ctx, ocs_sm_event_t evt, void *arg)
{
	ocs_node_t *node = NULL;
	ocs_t *ocs = NULL;
	ocs_assert(ctx, NULL);
	node = ctx->app;
	ocs_assert(node, NULL);
	ocs = node->ocs;
	ocs_assert(ocs, NULL);

	switch(evt) {

	/* Handle shutdown events */
	case OCS_EVT_SHUTDOWN:
		ocs_log_debug(ocs, "[%s] %-20s %-20s\n", node->display_name, funcname, ocs_sm_event_name(evt));
		node->shutdown_reason = OCS_NODE_SHUTDOWN_DEFAULT;
		ocs_node_transition(node, __ocs_d_initiate_shutdown, NULL);
		break;
	case OCS_EVT_SHUTDOWN_EXPLICIT_LOGO:
		ocs_log_debug(ocs, "[%s] %-20s %-20s\n", node->display_name, funcname, ocs_sm_event_name(evt));
		node->shutdown_reason = OCS_NODE_SHUTDOWN_EXPLICIT_LOGO;
		ocs_node_transition(node, __ocs_d_initiate_shutdown, NULL);
		break;
	case OCS_EVT_SHUTDOWN_IMPLICIT_LOGO:
		ocs_log_debug(ocs, "[%s] %-20s %-20s\n", node->display_name, funcname, ocs_sm_event_name(evt));
		node->shutdown_reason = OCS_NODE_SHUTDOWN_IMPLICIT_LOGO;
		ocs_node_transition(node, __ocs_d_initiate_shutdown, NULL);
		break;

	default:
		/* call default event handler common to all nodes */
		__ocs_node_common(funcname, ctx, evt, arg);
		break;
	}
	return NULL;
}