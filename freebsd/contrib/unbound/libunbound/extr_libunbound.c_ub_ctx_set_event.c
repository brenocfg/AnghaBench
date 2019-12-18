#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ub_event_base {int dummy; } ;
struct ub_ctx {int dothread; int /*<<< orphan*/  cfglock; scalar_t__ created_bg; struct ub_event_base* event_base; int /*<<< orphan*/ * event_worker; } ;
struct event_base {int dummy; } ;

/* Variables and functions */
 int UB_INITFAIL ; 
 int UB_NOERROR ; 
 int /*<<< orphan*/  libworker_delete_event (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 struct ub_event_base* ub_libevent_event_base (struct event_base*) ; 
 struct event_base* ub_libevent_get_event_base (struct ub_event_base*) ; 

int 
ub_ctx_set_event(struct ub_ctx* ctx, struct event_base* base) {
	struct ub_event_base* new_base;

	if (!ctx || !ctx->event_base || !base) {
		return UB_INITFAIL;
	}
	if (ub_libevent_get_event_base(ctx->event_base) == base) {
		/* already set */
		return UB_NOERROR;
	}
	
	lock_basic_lock(&ctx->cfglock);
	/* destroy the current worker - safe to pass in NULL */
	libworker_delete_event(ctx->event_worker);
	ctx->event_worker = NULL;
	new_base = ub_libevent_event_base(base);
	if (new_base)
		ctx->event_base = new_base;	
	ctx->created_bg = 0;
	ctx->dothread = 1;
	lock_basic_unlock(&ctx->cfglock);
	return new_base ? UB_NOERROR : UB_INITFAIL;
}