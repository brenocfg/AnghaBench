#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int ocs_sm_event_t ;
struct TYPE_8__ {TYPE_2__* app; } ;
typedef  TYPE_1__ ocs_sm_ctx_t ;
struct TYPE_9__ {TYPE_3__* hw; } ;
typedef  TYPE_2__ ocs_sli_port_t ;
struct TYPE_10__ {int /*<<< orphan*/  os; } ;
typedef  TYPE_3__ ocs_hw_t ;

/* Variables and functions */
#define  OCS_EVT_ENTER 130 
#define  OCS_EVT_ERROR 129 
#define  OCS_EVT_RESPONSE 128 
 int /*<<< orphan*/  __ocs_hw_port_free_report_fail ; 
 int /*<<< orphan*/  __ocs_hw_port_freed ; 
 int /*<<< orphan*/  __ocs_hw_port_realloc_cb ; 
 int /*<<< orphan*/  ocs_hw_async_call (TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ocs_sm_transition (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  smtrace (char*) ; 

__attribute__((used)) static void *
__ocs_hw_port_free_nop(ocs_sm_ctx_t *ctx, ocs_sm_event_t evt, void *data)
{
	ocs_sli_port_t	*sport = ctx->app;
	ocs_hw_t	*hw = sport->hw;

	smtrace("port");

	switch (evt) {
	case OCS_EVT_ENTER:
		/* Forward to execute in mailbox completion processing context */
		if (ocs_hw_async_call(hw, __ocs_hw_port_realloc_cb, sport)) {
			ocs_log_err(hw->os, "ocs_hw_async_call failed\n");
		}
		break;
	case OCS_EVT_RESPONSE:
		ocs_sm_transition(ctx, __ocs_hw_port_freed, data);
		break;
	case OCS_EVT_ERROR:
		ocs_sm_transition(ctx, __ocs_hw_port_free_report_fail, data);
		break;
	default:
		break;
	}

	return NULL;
}