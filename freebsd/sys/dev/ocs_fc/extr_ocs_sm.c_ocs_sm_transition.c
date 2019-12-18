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
typedef  scalar_t__ ocs_sm_function_t ;
struct TYPE_4__ {scalar_t__ current_state; } ;
typedef  TYPE_1__ ocs_sm_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_EVT_ENTER ; 
 int /*<<< orphan*/  OCS_EVT_EXIT ; 
 int /*<<< orphan*/  OCS_EVT_REENTER ; 
 int /*<<< orphan*/  ocs_sm_post_event (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 

void
ocs_sm_transition(ocs_sm_ctx_t *ctx, ocs_sm_function_t state, void *data)
{
	if (ctx->current_state == state) {
		ocs_sm_post_event(ctx, OCS_EVT_REENTER, data);
	} else {
		ocs_sm_post_event(ctx, OCS_EVT_EXIT, data);
		ctx->current_state = state;
		ocs_sm_post_event(ctx, OCS_EVT_ENTER, data);
	}
}