#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ocs_sm_event_t ;
typedef  int /*<<< orphan*/  ocs_sm_ctx_t ;
struct TYPE_7__ {int /*<<< orphan*/  display_name; } ;
struct TYPE_6__ {TYPE_1__* node; } ;
struct TYPE_5__ {int /*<<< orphan*/  ocs; } ;

/* Variables and functions */
#define  OCS_EVT_ENTER 131 
#define  OCS_EVT_EXIT 130 
#define  OCS_EVT_REENTER 129 
#define  OCS_EVT_SRRS_ELS_REQ_FAIL 128 
 TYPE_2__* els ; 
 TYPE_3__* node ; 
 int /*<<< orphan*/  ocs_els_io_cleanup (TYPE_2__*,int const,void*) ; 
 int /*<<< orphan*/  ocs_log_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_sm_event_name (int) ; 
 int /*<<< orphan*/  std_els_state_decl () ; 

void *
__ocs_els_common(const char *funcname, ocs_sm_ctx_t *ctx, ocs_sm_event_t evt, void *arg)
{
	std_els_state_decl();

	switch(evt) {
	case OCS_EVT_ENTER:
	case OCS_EVT_REENTER:
	case OCS_EVT_EXIT:
		break;

	/* If ELS_REQ_FAIL is not handled in state, then we'll terminate this ELS and
	 * pass the event to the node
	 */
	case OCS_EVT_SRRS_ELS_REQ_FAIL:
		ocs_log_warn(els->node->ocs, "[%s] %-20s %-20s not handled - terminating ELS\n", node->display_name, funcname,
			ocs_sm_event_name(evt));
		ocs_els_io_cleanup(els, OCS_EVT_SRRS_ELS_REQ_FAIL, arg);
		break;
	default:
		ocs_log_warn(els->node->ocs, "[%s] %-20s %-20s not handled\n", node->display_name, funcname,
			ocs_sm_event_name(evt));
		break;
	}
	return NULL;
}