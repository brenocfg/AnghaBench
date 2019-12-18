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
struct msg {int dummy; } ;
struct evrpc_base {int dummy; } ;
struct evhttp_request {int /*<<< orphan*/  output_buffer; int /*<<< orphan*/  output_headers; } ;
struct evhttp_connection {int dummy; } ;
struct evhttp {int dummy; } ;
typedef  int /*<<< orphan*/  ev_uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVHTTP_REQ_POST ; 
 int /*<<< orphan*/  EVTAG_ASSIGN (struct msg*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  event_dispatch () ; 
 int /*<<< orphan*/  evhttp_add_header (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  evhttp_connection_free (struct evhttp_connection*) ; 
 struct evhttp_connection* evhttp_connection_new (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_free (struct evhttp*) ; 
 int evhttp_make_request (struct evhttp_connection*,struct evhttp_request*,int /*<<< orphan*/ ,char*) ; 
 struct evhttp_request* evhttp_request_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  from_name ; 
 int /*<<< orphan*/  msg_free (struct msg*) ; 
 int /*<<< orphan*/  msg_marshal (int /*<<< orphan*/ ,struct msg*) ; 
 struct msg* msg_new () ; 
 int /*<<< orphan*/  rpc_postrequest_done ; 
 int /*<<< orphan*/  rpc_setup (struct evhttp**,int /*<<< orphan*/ *,struct evrpc_base**) ; 
 int /*<<< orphan*/  rpc_teardown (struct evrpc_base*) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ test_ok ; 
 int /*<<< orphan*/  to_name ; 
 int /*<<< orphan*/  tt_assert (struct evhttp_connection*) ; 

__attribute__((used)) static void
rpc_basic_message(void)
{
	ev_uint16_t port;
	struct evhttp *http = NULL;
	struct evrpc_base *base = NULL;
	struct evhttp_connection *evcon = NULL;
	struct evhttp_request *req = NULL;
	struct msg *msg;

	rpc_setup(&http, &port, &base);

	evcon = evhttp_connection_new("127.0.0.1", port);
	tt_assert(evcon);

	/*
	 * At this point, we want to schedule an HTTP POST request
	 * server using our make request method.
	 */

	req = evhttp_request_new(rpc_postrequest_done, NULL);
	if (req == NULL) {
		fprintf(stdout, "FAILED\n");
		exit(1);
	}

	/* Add the information that we care about */
	evhttp_add_header(req->output_headers, "Host", "somehost");

	/* set up the basic message */
	msg = msg_new();
	EVTAG_ASSIGN(msg, from_name, "niels");
	EVTAG_ASSIGN(msg, to_name, "tester");
	msg_marshal(req->output_buffer, msg);
	msg_free(msg);

	if (evhttp_make_request(evcon, req,
		EVHTTP_REQ_POST,
		"/.rpc.Message") == -1) {
		fprintf(stdout, "FAILED\n");
		exit(1);
	}

	test_ok = 0;

	event_dispatch();

	evhttp_connection_free(evcon);

	rpc_teardown(base);

end:
	evhttp_free(http);
}