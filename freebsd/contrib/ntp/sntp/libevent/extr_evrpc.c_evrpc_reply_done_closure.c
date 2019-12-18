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
struct evrpc_status {int /*<<< orphan*/  error; struct evhttp_request* http_req; } ;
struct evrpc_request_wrapper {int (* reply_unmarshal ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  cb_arg; int /*<<< orphan*/  reply; int /*<<< orphan*/  request; int /*<<< orphan*/  (* cb ) (struct evrpc_status*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* reply_clear ) (int /*<<< orphan*/ ) ;struct evrpc_pool* pool; struct evhttp_request* req; } ;
struct evrpc_pool {int dummy; } ;
struct evhttp_request {int /*<<< orphan*/  input_buffer; } ;
typedef  int /*<<< orphan*/  status ;
typedef  enum EVRPC_HOOK_RESULT { ____Placeholder_EVRPC_HOOK_RESULT } EVRPC_HOOK_RESULT ;

/* Variables and functions */
 int /*<<< orphan*/  EVRPC_STATUS_ERR_BADPAYLOAD ; 
 int /*<<< orphan*/  EVRPC_STATUS_ERR_HOOKABORTED ; 
 int /*<<< orphan*/  EVRPC_STATUS_ERR_TIMEOUT ; 
 int EVRPC_TERMINATE ; 
 int /*<<< orphan*/  evhttp_request_free (struct evhttp_request*) ; 
 scalar_t__ evhttp_request_is_owned (struct evhttp_request*) ; 
 int /*<<< orphan*/  evrpc_pool_schedule (struct evrpc_pool*) ; 
 int /*<<< orphan*/  evrpc_request_wrapper_free (struct evrpc_request_wrapper*) ; 
 int /*<<< orphan*/  memset (struct evrpc_status*,int /*<<< orphan*/ ,int) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct evrpc_status*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
evrpc_reply_done_closure(void *arg, enum EVRPC_HOOK_RESULT hook_res)
{
	struct evrpc_request_wrapper *ctx = arg;
	struct evhttp_request *req = ctx->req;
	struct evrpc_pool *pool = ctx->pool;
	struct evrpc_status status;
	int res = -1;

	memset(&status, 0, sizeof(status));
	status.http_req = req;

	/* we need to get the reply now */
	if (req == NULL) {
		status.error = EVRPC_STATUS_ERR_TIMEOUT;
	} else if (hook_res == EVRPC_TERMINATE) {
		status.error = EVRPC_STATUS_ERR_HOOKABORTED;
	} else {
		res = ctx->reply_unmarshal(ctx->reply, req->input_buffer);
		if (res == -1)
			status.error = EVRPC_STATUS_ERR_BADPAYLOAD;
	}

	if (res == -1) {
		/* clear everything that we might have written previously */
		ctx->reply_clear(ctx->reply);
	}

	(*ctx->cb)(&status, ctx->request, ctx->reply, ctx->cb_arg);

	evrpc_request_wrapper_free(ctx);

	/* the http layer owned the original request structure, but if we
	 * got paused, we asked for ownership and need to free it here. */
	if (req != NULL && evhttp_request_is_owned(req))
		evhttp_request_free(req);

	/* see if we can schedule another request */
	evrpc_pool_schedule(pool);
}