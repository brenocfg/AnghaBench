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
struct evrpc_req_generic {int /*<<< orphan*/  hook_meta; int /*<<< orphan*/ * rpc_data; struct evhttp_request* http_req; struct evrpc* rpc; } ;
struct evrpc {TYPE_1__* base; } ;
struct evhttp_request {scalar_t__ type; int /*<<< orphan*/  input_buffer; int /*<<< orphan*/  evcon; } ;
struct TYPE_2__ {int /*<<< orphan*/  input_hooks; } ;

/* Variables and functions */
 scalar_t__ EVHTTP_REQ_POST ; 
#define  EVRPC_CONTINUE 130 
#define  EVRPC_PAUSE 129 
#define  EVRPC_TERMINATE 128 
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 int /*<<< orphan*/  HTTP_SERVUNAVAIL ; 
 int /*<<< orphan*/ * TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 scalar_t__ evbuffer_get_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_send_error (struct evhttp_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evrpc_hook_associate_meta_ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evrpc_pause_request (TYPE_1__*,struct evrpc_req_generic*,int /*<<< orphan*/  (*) (struct evrpc_req_generic*,int const)) ; 
 int evrpc_process_hooks (int /*<<< orphan*/ *,struct evrpc_req_generic*,struct evhttp_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evrpc_reqstate_free_ (struct evrpc_req_generic*) ; 
 int /*<<< orphan*/  evrpc_request_cb_closure (struct evrpc_req_generic*,int const) ; 
 struct evrpc_req_generic* mm_calloc (int,int) ; 

__attribute__((used)) static void
evrpc_request_cb(struct evhttp_request *req, void *arg)
{
	struct evrpc *rpc = arg;
	struct evrpc_req_generic *rpc_state = NULL;

	/* let's verify the outside parameters */
	if (req->type != EVHTTP_REQ_POST ||
	    evbuffer_get_length(req->input_buffer) <= 0)
		goto error;

	rpc_state = mm_calloc(1, sizeof(struct evrpc_req_generic));
	if (rpc_state == NULL)
		goto error;
	rpc_state->rpc = rpc;
	rpc_state->http_req = req;
	rpc_state->rpc_data = NULL;

	if (TAILQ_FIRST(&rpc->base->input_hooks) != NULL) {
		int hook_res;

		evrpc_hook_associate_meta_(&rpc_state->hook_meta, req->evcon);

		/*
		 * allow hooks to modify the outgoing request
		 */
		hook_res = evrpc_process_hooks(&rpc->base->input_hooks,
		    rpc_state, req, req->input_buffer);
		switch (hook_res) {
		case EVRPC_TERMINATE:
			goto error;
		case EVRPC_PAUSE:
			evrpc_pause_request(rpc->base, rpc_state,
			    evrpc_request_cb_closure);
			return;
		case EVRPC_CONTINUE:
			break;
		default:
			EVUTIL_ASSERT(hook_res == EVRPC_TERMINATE ||
			    hook_res == EVRPC_CONTINUE ||
			    hook_res == EVRPC_PAUSE);
		}
	}

	evrpc_request_cb_closure(rpc_state, EVRPC_CONTINUE);
	return;

error:
	if (rpc_state)
		evrpc_reqstate_free_(rpc_state);
	evhttp_send_error(req, HTTP_SERVUNAVAIL, NULL);
	return;
}