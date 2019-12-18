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
struct timeval {int member_1; int /*<<< orphan*/  member_0; } ;
struct evhttp_request {int dummy; } ;
struct evhttp_connection {int dummy; } ;
struct evhttp {int /*<<< orphan*/  connections; } ;
struct basic_test_data {int /*<<< orphan*/  base; } ;
typedef  int /*<<< orphan*/  ev_uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVHTTP_REQ_GET ; 
 int /*<<< orphan*/ * TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close_detect_cb ; 
 struct evhttp_connection* delayed_client ; 
 int /*<<< orphan*/  event_base_dispatch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_add_header (int /*<<< orphan*/ ,char*,char*) ; 
 struct evhttp_connection* evhttp_connection_base_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_connection_free (struct evhttp_connection*) ; 
 int /*<<< orphan*/  evhttp_connection_set_timeout_tv (struct evhttp_connection*,struct timeval const*) ; 
 int /*<<< orphan*/  evhttp_free (struct evhttp*) ; 
 int evhttp_make_request (struct evhttp_connection*,struct evhttp_request*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  evhttp_request_get_output_headers (struct evhttp_request*) ; 
 struct evhttp_request* evhttp_request_new (int /*<<< orphan*/ ,struct evhttp_connection*) ; 
 int /*<<< orphan*/  evhttp_set_timeout_tv (struct evhttp*,struct timeval const*) ; 
 struct evhttp* http_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_ok ; 
 int /*<<< orphan*/  tt_abort_msg (char*) ; 
 int /*<<< orphan*/  tt_assert (struct evhttp_connection*) ; 

__attribute__((used)) static void
http_close_detection_(struct basic_test_data *data, int with_delay)
{
	ev_uint16_t port = 0;
	struct evhttp_connection *evcon = NULL;
	struct evhttp_request *req = NULL;
	const struct timeval sec_tenth = { 0, 100000 };
	struct evhttp *http = http_setup(&port, data->base, 0);

	test_ok = 0;

	/* .1 second timeout */
	evhttp_set_timeout_tv(http, &sec_tenth);

	evcon = evhttp_connection_base_new(data->base, NULL,
	    "127.0.0.1", port);
	tt_assert(evcon);
	evhttp_connection_set_timeout_tv(evcon, &sec_tenth);


	tt_assert(evcon);
	delayed_client = evcon;

	/*
	 * At this point, we want to schedule a request to the HTTP
	 * server using our make request method.
	 */

	req = evhttp_request_new(close_detect_cb, evcon);

	/* Add the information that we care about */
	evhttp_add_header(evhttp_request_get_output_headers(req), "Host", "somehost");

	/* We give ownership of the request to the connection */
	if (evhttp_make_request(evcon,
	    req, EVHTTP_REQ_GET, with_delay ? "/largedelay" : "/test") == -1) {
		tt_abort_msg("couldn't make request");
	}

	event_base_dispatch(data->base);

	/* at this point, the http server should have no connection */
	tt_assert(TAILQ_FIRST(&http->connections) == NULL);

 end:
	if (evcon)
		evhttp_connection_free(evcon);
	if (http)
		evhttp_free(http);
}