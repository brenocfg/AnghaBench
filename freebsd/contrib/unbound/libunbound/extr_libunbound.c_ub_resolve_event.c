#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ub_event_callback_type ;
struct ub_ctx {TYPE_1__* event_worker; int /*<<< orphan*/  event_base; int /*<<< orphan*/  cfglock; int /*<<< orphan*/  finalized; } ;
struct ctx_query {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int UB_INITFAIL ; 
 int UB_NOERROR ; 
 int UB_NOMEM ; 
 int context_finalize (struct ub_ctx*) ; 
 struct ctx_query* context_new (struct ub_ctx*,char const*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int libworker_attach_mesh (struct ub_ctx*,struct ctx_query*,int*) ; 
 TYPE_1__* libworker_create_event (struct ub_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ub_comm_base_now (int /*<<< orphan*/ ) ; 

int 
ub_resolve_event(struct ub_ctx* ctx, const char* name, int rrtype, 
	int rrclass, void* mydata, ub_event_callback_type callback,
	int* async_id)
{
	struct ctx_query* q;
	int r;

	if(async_id)
		*async_id = 0;
	lock_basic_lock(&ctx->cfglock);
	if(!ctx->finalized) {
		r = context_finalize(ctx);
		if(r) {
			lock_basic_unlock(&ctx->cfglock);
			return r;
		}
	}
	lock_basic_unlock(&ctx->cfglock);
	if(!ctx->event_worker) {
		ctx->event_worker = libworker_create_event(ctx,
			ctx->event_base);
		if(!ctx->event_worker) {
			return UB_INITFAIL;
		}
	}

	/* set time in case answer comes from cache */
	ub_comm_base_now(ctx->event_worker->base);

	/* create new ctx_query and attempt to add to the list */
	q = context_new(ctx, name, rrtype, rrclass, NULL, callback, mydata);
	if(!q)
		return UB_NOMEM;

	/* attach to mesh */
	if((r=libworker_attach_mesh(ctx, q, async_id)) != 0)
		return r;
	return UB_NOERROR;
}