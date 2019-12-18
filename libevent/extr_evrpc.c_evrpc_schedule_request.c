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
struct evrpc_status {int /*<<< orphan*/  error; } ;
struct evrpc_request_wrapper {int /*<<< orphan*/  cb_arg; int /*<<< orphan*/  reply; int /*<<< orphan*/  request; int /*<<< orphan*/  (* cb ) (struct evrpc_status*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  hook_meta; struct evhttp_request* req; struct evhttp_connection* evcon; int /*<<< orphan*/  (* request_marshal ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;struct evrpc_pool* pool; } ;
struct evrpc_pool {int /*<<< orphan*/  output_hooks; } ;
struct evhttp_request {int /*<<< orphan*/  output_buffer; } ;
struct evhttp_connection {int dummy; } ;
typedef  int /*<<< orphan*/  status ;

/* Variables and functions */
#define  EVRPC_CONTINUE 130 
#define  EVRPC_PAUSE 129 
 int /*<<< orphan*/  EVRPC_STATUS_ERR_UNSTARTED ; 
#define  EVRPC_TERMINATE 128 
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 int /*<<< orphan*/ * TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct evhttp_request* evhttp_request_new (int /*<<< orphan*/ ,struct evrpc_request_wrapper*) ; 
 int /*<<< orphan*/  evrpc_hook_associate_meta_ (int /*<<< orphan*/ *,struct evhttp_connection*) ; 
 int evrpc_pause_request (struct evrpc_pool*,struct evrpc_request_wrapper*,int /*<<< orphan*/  (*) (struct evrpc_request_wrapper*,int const)) ; 
 int evrpc_process_hooks (int /*<<< orphan*/ *,struct evrpc_request_wrapper*,struct evhttp_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evrpc_reply_done ; 
 int /*<<< orphan*/  evrpc_request_wrapper_free (struct evrpc_request_wrapper*) ; 
 int /*<<< orphan*/  evrpc_schedule_request_closure (struct evrpc_request_wrapper*,int const) ; 
 int /*<<< orphan*/  memset (struct evrpc_status*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct evrpc_status*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
evrpc_schedule_request(struct evhttp_connection *connection,
    struct evrpc_request_wrapper *ctx)
{
	struct evhttp_request *req = NULL;
	struct evrpc_pool *pool = ctx->pool;
	struct evrpc_status status;

	if ((req = evhttp_request_new(evrpc_reply_done, ctx)) == NULL)
		goto error;

	/* serialize the request data into the output buffer */
	ctx->request_marshal(req->output_buffer, ctx->request);

	/* we need to know the connection that we might have to abort */
	ctx->evcon = connection;

	/* if we get paused we also need to know the request */
	ctx->req = req;

	if (TAILQ_FIRST(&pool->output_hooks) != NULL) {
		int hook_res;

		evrpc_hook_associate_meta_(&ctx->hook_meta, connection);

		/* apply hooks to the outgoing request */
		hook_res = evrpc_process_hooks(&pool->output_hooks,
		    ctx, req, req->output_buffer);

		switch (hook_res) {
		case EVRPC_TERMINATE:
			goto error;
		case EVRPC_PAUSE:
			/* we need to be explicitly resumed */
			if (evrpc_pause_request(pool, ctx,
				evrpc_schedule_request_closure) == -1)
				goto error;
			return (0);
		case EVRPC_CONTINUE:
			/* we can just continue */
			break;
		default:
			EVUTIL_ASSERT(hook_res == EVRPC_TERMINATE ||
			    hook_res == EVRPC_CONTINUE ||
			    hook_res == EVRPC_PAUSE);
		}
	}

	evrpc_schedule_request_closure(ctx, EVRPC_CONTINUE);
	return (0);

error:
	memset(&status, 0, sizeof(status));
	status.error = EVRPC_STATUS_ERR_UNSTARTED;
	(*ctx->cb)(&status, ctx->request, ctx->reply, ctx->cb_arg);
	evrpc_request_wrapper_free(ctx);
	return (-1);
}