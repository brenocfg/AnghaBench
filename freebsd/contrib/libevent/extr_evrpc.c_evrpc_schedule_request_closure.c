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
struct timeval {scalar_t__ tv_sec; } ;
struct evrpc_status {int /*<<< orphan*/  error; } ;
struct evrpc_request_wrapper {int /*<<< orphan*/  cb_arg; int /*<<< orphan*/  reply; int /*<<< orphan*/  request; int /*<<< orphan*/  (* cb ) (struct evrpc_status*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  ev_timeout; int /*<<< orphan*/  name; struct evrpc_pool* pool; struct evhttp_request* req; struct evhttp_connection* evcon; } ;
struct evrpc_pool {scalar_t__ timeout; } ;
struct evhttp_request {int dummy; } ;
struct evhttp_connection {int dummy; } ;
typedef  int /*<<< orphan*/  status ;
typedef  enum EVRPC_HOOK_RESULT { ____Placeholder_EVRPC_HOOK_RESULT } EVRPC_HOOK_RESULT ;

/* Variables and functions */
 int /*<<< orphan*/  EVHTTP_REQ_POST ; 
 int /*<<< orphan*/  EVRPC_STATUS_ERR_UNSTARTED ; 
 int EVRPC_TERMINATE ; 
 int evhttp_make_request (struct evhttp_connection*,struct evhttp_request*,int /*<<< orphan*/ ,char*) ; 
 char* evrpc_construct_uri (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evrpc_request_wrapper_free (struct evrpc_request_wrapper*) ; 
 int /*<<< orphan*/  evtimer_add (int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  evutil_timerclear (struct timeval*) ; 
 int /*<<< orphan*/  memset (struct evrpc_status*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mm_free (char*) ; 
 int /*<<< orphan*/  stub1 (struct evrpc_status*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
evrpc_schedule_request_closure(void *arg, enum EVRPC_HOOK_RESULT hook_res)
{
	struct evrpc_request_wrapper *ctx = arg;
	struct evhttp_connection *connection = ctx->evcon;
	struct evhttp_request *req = ctx->req;
	struct evrpc_pool *pool = ctx->pool;
	struct evrpc_status status;
	char *uri = NULL;
	int res = 0;

	if (hook_res == EVRPC_TERMINATE)
		goto error;

	uri = evrpc_construct_uri(ctx->name);
	if (uri == NULL)
		goto error;

	if (pool->timeout > 0) {
		/*
		 * a timeout after which the whole rpc is going to be aborted.
		 */
		struct timeval tv;
		evutil_timerclear(&tv);
		tv.tv_sec = pool->timeout;
		evtimer_add(&ctx->ev_timeout, &tv);
	}

	/* start the request over the connection */
	res = evhttp_make_request(connection, req, EVHTTP_REQ_POST, uri);
	mm_free(uri);

	if (res == -1)
		goto error;

	return;

error:
	memset(&status, 0, sizeof(status));
	status.error = EVRPC_STATUS_ERR_UNSTARTED;
	(*ctx->cb)(&status, ctx->request, ctx->reply, ctx->cb_arg);
	evrpc_request_wrapper_free(ctx);
}