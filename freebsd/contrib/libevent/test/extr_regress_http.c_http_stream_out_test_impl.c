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
struct evhttp_request {int dummy; } ;
struct evhttp_connection {int dummy; } ;
struct evhttp {int dummy; } ;
struct bufferevent {int dummy; } ;
struct basic_test_data {int /*<<< orphan*/  base; } ;
typedef  int /*<<< orphan*/  ev_uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVHTTP_REQ_GET ; 
 int /*<<< orphan*/  HTTP_BIND_SSL ; 
 struct bufferevent* create_bev (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  event_base_dispatch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_add_header (int /*<<< orphan*/ ,char*,char*) ; 
 struct evhttp_connection* evhttp_connection_base_bufferevent_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct bufferevent*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_connection_free (struct evhttp_connection*) ; 
 int /*<<< orphan*/  evhttp_free (struct evhttp*) ; 
 int evhttp_make_request (struct evhttp_connection*,struct evhttp_request*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  evhttp_request_get_output_headers (struct evhttp_request*) ; 
 struct evhttp_request* evhttp_request_new (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  exit_base ; 
 int /*<<< orphan*/  http_request_done ; 
 struct evhttp* http_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_ok ; 
 int /*<<< orphan*/  tt_abort_msg (char*) ; 
 int /*<<< orphan*/  tt_assert (struct evhttp_connection*) ; 

__attribute__((used)) static void
http_stream_out_test_impl(void *arg, int ssl)
{
	struct basic_test_data *data = arg;
	ev_uint16_t port = 0;
	struct evhttp_connection *evcon = NULL;
	struct evhttp_request *req = NULL;
	struct bufferevent *bev;
	struct evhttp *http = http_setup(&port, data->base, ssl ? HTTP_BIND_SSL : 0);

	test_ok = 0;
	exit_base = data->base;

	bev = create_bev(data->base, -1, ssl);
	evcon = evhttp_connection_base_bufferevent_new(
		data->base, NULL, bev, "127.0.0.1", port);
	tt_assert(evcon);

	/*
	 * At this point, we want to schedule a request to the HTTP
	 * server using our make request method.
	 */

	req = evhttp_request_new(http_request_done,
	    (void *)"This is funnybut not hilarious.bwv 1052");

	/* Add the information that we care about */
	evhttp_add_header(evhttp_request_get_output_headers(req), "Host", "somehost");

	/* We give ownership of the request to the connection */
	if (evhttp_make_request(evcon, req, EVHTTP_REQ_GET, "/streamed")
	    == -1) {
		tt_abort_msg("Couldn't make request");
	}

	event_base_dispatch(data->base);

 end:
	if (evcon)
		evhttp_connection_free(evcon);
	if (http)
		evhttp_free(http);
}