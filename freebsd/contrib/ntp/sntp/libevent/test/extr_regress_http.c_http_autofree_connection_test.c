#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct evhttp_request {int dummy; } ;
struct evhttp_connection {int dummy; } ;
struct basic_test_data {int /*<<< orphan*/  base; } ;
typedef  int /*<<< orphan*/  ev_uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  connections; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVHTTP_REQ_GET ; 
 int /*<<< orphan*/ * TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_base_dispatch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_add_header (int /*<<< orphan*/ ,char*,char*) ; 
 struct evhttp_connection* evhttp_connection_base_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_connection_free (struct evhttp_connection*) ; 
 int /*<<< orphan*/  evhttp_connection_free_on_completion (struct evhttp_connection*) ; 
 int /*<<< orphan*/  evhttp_free (TYPE_1__*) ; 
 int evhttp_make_request (struct evhttp_connection*,struct evhttp_request*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  evhttp_request_get_output_headers (struct evhttp_request*) ; 
 struct evhttp_request* evhttp_request_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* http ; 
 int /*<<< orphan*/  http_request_empty_done ; 
 TYPE_1__* http_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_ok ; 
 int /*<<< orphan*/  tt_abort_msg (char*) ; 
 int /*<<< orphan*/  tt_assert (struct evhttp_connection*) ; 

__attribute__((used)) static void
http_autofree_connection_test(void *arg)
{
	struct basic_test_data *data = arg;
	ev_uint16_t port = 0;
	struct evhttp_connection *evcon = NULL;
	struct evhttp_request *req[2] = { NULL };

	test_ok = 0;
	http = http_setup(&port, data->base, 0);

	evcon = evhttp_connection_base_new(data->base, NULL, "127.0.0.1", port);
	tt_assert(evcon);

	/*
	 * At this point, we want to schedule two request to the HTTP
	 * server using our make request method.
	 */
	req[0] = evhttp_request_new(http_request_empty_done, data->base);
	req[1] = evhttp_request_new(http_request_empty_done, data->base);

	/* Add the information that we care about */
	evhttp_add_header(evhttp_request_get_output_headers(req[0]), "Host", "somehost");
	evhttp_add_header(evhttp_request_get_output_headers(req[0]), "Connection", "close");
	evhttp_add_header(evhttp_request_get_output_headers(req[0]), "Empty", "itis");
	evhttp_add_header(evhttp_request_get_output_headers(req[1]), "Host", "somehost");
	evhttp_add_header(evhttp_request_get_output_headers(req[1]), "Connection", "close");
	evhttp_add_header(evhttp_request_get_output_headers(req[1]), "Empty", "itis");

	/* We give ownership of the request to the connection */
	if (evhttp_make_request(evcon, req[0], EVHTTP_REQ_GET, "/test") == -1) {
		tt_abort_msg("couldn't make request");
	}
	if (evhttp_make_request(evcon, req[1], EVHTTP_REQ_GET, "/test") == -1) {
		tt_abort_msg("couldn't make request");
	}

	/*
	 * Tell libevent to free the connection when the request completes
	 *	We then set the evcon pointer to NULL since we don't want to free it
	 *	when this function ends.
	 */
	evhttp_connection_free_on_completion(evcon);
	evcon = NULL;

	event_base_dispatch(data->base);

	/* at this point, the http server should have no connection */
	tt_assert(TAILQ_FIRST(&http->connections) == NULL);

 end:
	if (evcon)
		evhttp_connection_free(evcon);
	if (http)
		evhttp_free(http);
}