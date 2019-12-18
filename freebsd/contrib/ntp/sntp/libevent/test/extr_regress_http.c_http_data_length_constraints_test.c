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
typedef  struct evhttp_request evhttp_connection ;
struct basic_test_data {int /*<<< orphan*/  base; } ;
typedef  int /*<<< orphan*/  ev_uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVHTTP_REQ_GET ; 
 int /*<<< orphan*/  EVHTTP_REQ_POST ; 
 int /*<<< orphan*/  evbuffer_add_printf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  event_base_dispatch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_add_header (int /*<<< orphan*/ ,char*,char*) ; 
 struct evhttp_request* evhttp_connection_base_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_connection_free (struct evhttp_request*) ; 
 int /*<<< orphan*/  evhttp_connection_set_local_address (struct evhttp_request*,char*) ; 
 int /*<<< orphan*/  evhttp_free (scalar_t__) ; 
 int evhttp_make_request (struct evhttp_request*,struct evhttp_request*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  evhttp_request_get_output_buffer (struct evhttp_request*) ; 
 int /*<<< orphan*/  evhttp_request_get_output_headers (struct evhttp_request*) ; 
 struct evhttp_request* evhttp_request_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_set_max_body_size (scalar_t__,int) ; 
 int /*<<< orphan*/  evhttp_set_max_headers_size (scalar_t__,int) ; 
 scalar_t__ http ; 
 int /*<<< orphan*/  http_data_length_constraints_test_done ; 
 int /*<<< orphan*/  http_large_entity_test_done ; 
 scalar_t__ http_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int test_ok ; 
 int /*<<< orphan*/  tt_abort_msg (char*) ; 
 int /*<<< orphan*/  tt_assert (struct evhttp_request*) ; 

__attribute__((used)) static void
http_data_length_constraints_test(void *arg)
{
	struct basic_test_data *data = arg;
	ev_uint16_t port = 0;
	struct evhttp_connection *evcon = NULL;
	struct evhttp_request *req = NULL;
	char long_str[8192];

	test_ok = 0;

	http = http_setup(&port, data->base, 0);

	evcon = evhttp_connection_base_new(data->base, NULL, "127.0.0.1", port);
	tt_assert(evcon);

	/* also bind to local host */
	evhttp_connection_set_local_address(evcon, "127.0.0.1");

	/*
	 * At this point, we want to schedule an HTTP GET request
	 * server using our make request method.
	 */

	req = evhttp_request_new(http_data_length_constraints_test_done, data->base);
	tt_assert(req);

	memset(long_str, 'a', 8192);
	long_str[8191] = '\0';
	/* Add the information that we care about */
	evhttp_set_max_headers_size(http, 8191);
	evhttp_add_header(evhttp_request_get_output_headers(req), "Host", "somehost");
	evhttp_add_header(evhttp_request_get_output_headers(req), "Longheader", long_str);

	if (evhttp_make_request(evcon, req, EVHTTP_REQ_GET, "/?arg=val") == -1) {
		tt_abort_msg("Couldn't make request");
	}
	event_base_dispatch(data->base);

	req = evhttp_request_new(http_data_length_constraints_test_done, data->base);
	tt_assert(req);
	evhttp_add_header(evhttp_request_get_output_headers(req), "Host", "somehost");

	/* GET /?arg=verylongvalue HTTP/1.1 */
	if (evhttp_make_request(evcon, req, EVHTTP_REQ_GET, long_str) == -1) {
		tt_abort_msg("Couldn't make request");
	}
	event_base_dispatch(data->base);

	evhttp_set_max_body_size(http, 8190);
	req = evhttp_request_new(http_data_length_constraints_test_done, data->base);
	evhttp_add_header(evhttp_request_get_output_headers(req), "Host", "somehost");
	evbuffer_add_printf(evhttp_request_get_output_buffer(req), "%s", long_str);
	if (evhttp_make_request(evcon, req, EVHTTP_REQ_POST, "/") == -1) {
		tt_abort_msg("Couldn't make request");
	}
	event_base_dispatch(data->base);

	req = evhttp_request_new(http_large_entity_test_done, data->base);
	evhttp_add_header(evhttp_request_get_output_headers(req), "Host", "somehost");
	evhttp_add_header(evhttp_request_get_output_headers(req), "Expect", "100-continue");
	evbuffer_add_printf(evhttp_request_get_output_buffer(req), "%s", long_str);
	if (evhttp_make_request(evcon, req, EVHTTP_REQ_POST, "/") == -1) {
		tt_abort_msg("Couldn't make request");
	}
	event_base_dispatch(data->base);

	test_ok = 1;
 end:
	if (evcon)
		evhttp_connection_free(evcon);
	if (http)
		evhttp_free(http);
}