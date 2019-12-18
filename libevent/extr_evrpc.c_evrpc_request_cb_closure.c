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
struct evrpc_req_generic {int /*<<< orphan*/ * reply; int /*<<< orphan*/ * request; struct evhttp_request* http_req; struct evrpc* rpc; } ;
struct evrpc {int (* request_unmarshal ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  cb_arg; int /*<<< orphan*/  (* cb ) (struct evrpc_req_generic*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  reply_new_arg; int /*<<< orphan*/ * (* reply_new ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  request_new_arg; int /*<<< orphan*/ * (* request_new ) (int /*<<< orphan*/ ) ;} ;
struct evhttp_request {int /*<<< orphan*/  input_buffer; } ;
typedef  enum EVRPC_HOOK_RESULT { ____Placeholder_EVRPC_HOOK_RESULT } EVRPC_HOOK_RESULT ;

/* Variables and functions */
 int EVRPC_TERMINATE ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (struct evrpc_req_generic*) ; 
 int /*<<< orphan*/  HTTP_SERVUNAVAIL ; 
 int /*<<< orphan*/  evhttp_send_error (struct evhttp_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evrpc_reqstate_free_ (struct evrpc_req_generic*) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct evrpc_req_generic*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
evrpc_request_cb_closure(void *arg, enum EVRPC_HOOK_RESULT hook_res)
{
	struct evrpc_req_generic *rpc_state = arg;
	struct evrpc *rpc;
	struct evhttp_request *req;

	EVUTIL_ASSERT(rpc_state);
	rpc = rpc_state->rpc;
	req = rpc_state->http_req;

	if (hook_res == EVRPC_TERMINATE)
		goto error;

	/* let's check that we can parse the request */
	rpc_state->request = rpc->request_new(rpc->request_new_arg);
	if (rpc_state->request == NULL)
		goto error;

	if (rpc->request_unmarshal(
		    rpc_state->request, req->input_buffer) == -1) {
		/* we failed to parse the request; that's a bummer */
		goto error;
	}

	/* at this point, we have a well formed request, prepare the reply */

	rpc_state->reply = rpc->reply_new(rpc->reply_new_arg);
	if (rpc_state->reply == NULL)
		goto error;

	/* give the rpc to the user; they can deal with it */
	rpc->cb(rpc_state, rpc->cb_arg);

	return;

error:
	evrpc_reqstate_free_(rpc_state);
	evhttp_send_error(req, HTTP_SERVUNAVAIL, NULL);
	return;
}