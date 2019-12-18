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
struct basic_test_data {int /*<<< orphan*/  base; } ;
typedef  int /*<<< orphan*/  ev_uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVHTTP_REQ_GET ; 
 int /*<<< orphan*/  event_base_dispatch (int /*<<< orphan*/ ) ; 
 struct evhttp_connection* evhttp_connection_base_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_connection_free (struct evhttp_connection*) ; 
 int /*<<< orphan*/  evhttp_free (int /*<<< orphan*/ ) ; 
 int evhttp_make_request (struct evhttp_connection*,struct evhttp_request*,int /*<<< orphan*/ ,char*) ; 
 struct evhttp_request* evhttp_request_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_request_set_chunked_cb (struct evhttp_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  http ; 
 int /*<<< orphan*/  http_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  http_stream_in_cancel_chunk ; 
 int /*<<< orphan*/  http_stream_in_cancel_done ; 
 int test_ok ; 
 int /*<<< orphan*/  tt_abort_msg (char*) ; 
 int /*<<< orphan*/  tt_assert (struct evhttp_connection*) ; 

__attribute__((used)) static void
http_stream_in_cancel_test(void *arg)
{
	struct basic_test_data *data = arg;
	struct evhttp_connection *evcon;
	struct evhttp_request *req = NULL;
	ev_uint16_t port = 0;

	http = http_setup(&port, data->base, 0);

	evcon = evhttp_connection_base_new(data->base, NULL, "127.0.0.1", port);
	tt_assert(evcon);

	req = evhttp_request_new(http_stream_in_cancel_done, data->base);
	evhttp_request_set_chunked_cb(req, http_stream_in_cancel_chunk);

	/* We give ownership of the request to the connection */
	if (evhttp_make_request(evcon, req, EVHTTP_REQ_GET, "/chunked") == -1) {
		tt_abort_msg("Couldn't make request");
	}

	event_base_dispatch(data->base);

	test_ok = 1;
 end:
	evhttp_connection_free(evcon);
	evhttp_free(http);

}