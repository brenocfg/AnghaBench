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
struct evrpc_request_wrapper {int /*<<< orphan*/  evcon; int /*<<< orphan*/  hook_meta; struct evhttp_request* req; int /*<<< orphan*/  ev_timeout; struct evrpc_pool* pool; } ;
struct evrpc_pool {int /*<<< orphan*/  input_hooks; } ;
struct evhttp_request {int /*<<< orphan*/  input_buffer; } ;

/* Variables and functions */
#define  EVRPC_CONTINUE 130 
#define  EVRPC_PAUSE 129 
#define  EVRPC_TERMINATE 128 
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 int /*<<< orphan*/ * TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evhttp_request_own (struct evhttp_request*) ; 
 int /*<<< orphan*/  evrpc_hook_associate_meta_ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evrpc_pause_request (struct evrpc_pool*,struct evrpc_request_wrapper*,int /*<<< orphan*/  (*) (struct evrpc_request_wrapper*,int)) ; 
 int evrpc_process_hooks (int /*<<< orphan*/ *,struct evrpc_request_wrapper*,struct evhttp_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evrpc_reply_done_closure (struct evrpc_request_wrapper*,int) ; 

__attribute__((used)) static void
evrpc_reply_done(struct evhttp_request *req, void *arg)
{
	struct evrpc_request_wrapper *ctx = arg;
	struct evrpc_pool *pool = ctx->pool;
	int hook_res = EVRPC_CONTINUE;

	/* cancel any timeout we might have scheduled */
	event_del(&ctx->ev_timeout);

	ctx->req = req;

	/* we need to get the reply now */
	if (req == NULL) {
		evrpc_reply_done_closure(ctx, EVRPC_CONTINUE);
		return;
	}

	if (TAILQ_FIRST(&pool->input_hooks) != NULL) {
		evrpc_hook_associate_meta_(&ctx->hook_meta, ctx->evcon);

		/* apply hooks to the incoming request */
		hook_res = evrpc_process_hooks(&pool->input_hooks,
		    ctx, req, req->input_buffer);

		switch (hook_res) {
		case EVRPC_TERMINATE:
		case EVRPC_CONTINUE:
			break;
		case EVRPC_PAUSE:
			/*
			 * if we get paused we also need to know the
			 * request.  unfortunately, the underlying
			 * layer is going to free it.  we need to
			 * request ownership explicitly
			 */
			if (req != NULL)
				evhttp_request_own(req);

			evrpc_pause_request(pool, ctx,
			    evrpc_reply_done_closure);
			return;
		default:
			EVUTIL_ASSERT(hook_res == EVRPC_TERMINATE ||
			    hook_res == EVRPC_CONTINUE ||
			    hook_res == EVRPC_PAUSE);
		}
	}

	evrpc_reply_done_closure(ctx, hook_res);

	/* http request is being freed by underlying layer */
}