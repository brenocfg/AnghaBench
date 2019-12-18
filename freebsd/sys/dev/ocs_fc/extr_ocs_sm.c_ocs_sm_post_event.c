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
struct TYPE_4__ {int /*<<< orphan*/  (* current_state ) (TYPE_1__*,int /*<<< orphan*/ ,void*) ;} ;
typedef  TYPE_1__ ocs_sm_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 

int
ocs_sm_post_event(ocs_sm_ctx_t *ctx, ocs_sm_event_t evt, void *data)
{
	if (ctx->current_state) {
		ctx->current_state(ctx, evt, data);
		return 0;
	} else {
		return -1;
	}
}