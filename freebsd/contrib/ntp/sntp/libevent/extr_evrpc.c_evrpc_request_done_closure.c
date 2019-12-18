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
struct evrpc_req_generic {int /*<<< orphan*/  rpc_data; struct evhttp_request* http_req; } ;
struct evhttp_request {int /*<<< orphan*/  output_headers; } ;
typedef  enum EVRPC_HOOK_RESULT { ____Placeholder_EVRPC_HOOK_RESULT } EVRPC_HOOK_RESULT ;

/* Variables and functions */
 int EVRPC_TERMINATE ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (struct evrpc_req_generic*) ; 
 int /*<<< orphan*/  HTTP_OK ; 
 int /*<<< orphan*/  HTTP_SERVUNAVAIL ; 
 int /*<<< orphan*/  evhttp_add_header (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/ * evhttp_find_header (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  evhttp_send_error (struct evhttp_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evhttp_send_reply (struct evhttp_request*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evrpc_reqstate_free_ (struct evrpc_req_generic*) ; 

__attribute__((used)) static void
evrpc_request_done_closure(void *arg, enum EVRPC_HOOK_RESULT hook_res)
{
	struct evrpc_req_generic *rpc_state = arg;
	struct evhttp_request *req;
	EVUTIL_ASSERT(rpc_state);
	req = rpc_state->http_req;

	if (hook_res == EVRPC_TERMINATE)
		goto error;

	/* on success, we are going to transmit marshaled binary data */
	if (evhttp_find_header(req->output_headers, "Content-Type") == NULL) {
		evhttp_add_header(req->output_headers,
		    "Content-Type", "application/octet-stream");
	}
	evhttp_send_reply(req, HTTP_OK, "OK", rpc_state->rpc_data);

	evrpc_reqstate_free_(rpc_state);

	return;

error:
	evrpc_reqstate_free_(rpc_state);
	evhttp_send_error(req, HTTP_SERVUNAVAIL, NULL);
	return;
}