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
struct evdns_base {int dummy; } ;
struct bufferevent {int dummy; } ;
struct basic_test_data {void* base; } ;
typedef  int /*<<< orphan*/  ev_uint16_t ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 scalar_t__ BASIC_REQUEST_BODY ; 
 int /*<<< orphan*/  BEV_OPT_DEFER_CALLBACKS ; 
 int /*<<< orphan*/  BUFFEREVENT_SSL_CONNECTING ; 
 int /*<<< orphan*/  EVHTTP_REQ_GET ; 
 int HTTP_BIND_IPV6 ; 
 int HTTP_BIND_SSL ; 
 int /*<<< orphan*/ * SSL_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_openssl_set_allow_dirty_shutdown (struct bufferevent*,int) ; 
 struct bufferevent* bufferevent_openssl_socket_new (void*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_base_dispatch (void*) ; 
 int /*<<< orphan*/  evhttp_add_header (int /*<<< orphan*/ ,char*,char*) ; 
 struct evhttp_connection* evhttp_connection_base_bufferevent_new (void*,struct evdns_base*,struct bufferevent*,char const*,int /*<<< orphan*/ ) ; 
 struct evhttp_connection* evhttp_connection_base_new (void*,struct evdns_base*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_connection_free (struct evhttp_connection*) ; 
 void* evhttp_connection_get_base (struct evhttp_connection*) ; 
 int /*<<< orphan*/ * evhttp_connection_get_server (struct evhttp_connection*) ; 
 int /*<<< orphan*/  evhttp_connection_set_family (struct evhttp_connection*,int) ; 
 int /*<<< orphan*/  evhttp_free (struct evhttp*) ; 
 int evhttp_make_request (struct evhttp_connection*,struct evhttp_request*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  evhttp_request_get_output_headers (struct evhttp_request*) ; 
 struct evhttp_request* evhttp_request_new (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  exit (int) ; 
 void* exit_base ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_ssl_ctx () ; 
 int /*<<< orphan*/  http_request_done ; 
 int /*<<< orphan*/  http_request_empty_done ; 
 struct evhttp* http_setup (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  stdout ; 
 int test_ok ; 
 int /*<<< orphan*/  tt_abort_msg (char*) ; 
 int /*<<< orphan*/  tt_assert (int) ; 
 int /*<<< orphan*/  tt_skip () ; 

__attribute__((used)) static void
http_connection_test_(struct basic_test_data *data, int persistent,
	const char *address, struct evdns_base *dnsbase, int ipv6, int family,
	int ssl)
{
	ev_uint16_t port = 0;
	struct evhttp_connection *evcon = NULL;
	struct evhttp_request *req = NULL;
	struct evhttp *http;

	int mask = 0;
	if (ipv6)
		mask |= HTTP_BIND_IPV6;
	if (ssl)
		mask |= HTTP_BIND_SSL;

	http = http_setup(&port, data->base, mask);

	test_ok = 0;
	if (!http && ipv6) {
		tt_skip();
	}
	tt_assert(http);

	if (ssl) {
#ifdef EVENT__HAVE_OPENSSL
		SSL *ssl = SSL_new(get_ssl_ctx());
		struct bufferevent *bev = bufferevent_openssl_socket_new(
			data->base, -1, ssl,
			BUFFEREVENT_SSL_CONNECTING, BEV_OPT_DEFER_CALLBACKS);
		bufferevent_openssl_set_allow_dirty_shutdown(bev, 1);

		evcon = evhttp_connection_base_bufferevent_new(data->base, dnsbase, bev, address, port);
#else
		tt_skip();
#endif
	} else {
		evcon = evhttp_connection_base_new(data->base, dnsbase, address, port);
	}
	tt_assert(evcon);
	evhttp_connection_set_family(evcon, family);

	tt_assert(evhttp_connection_get_base(evcon) == data->base);

	exit_base = data->base;

	tt_assert(evhttp_connection_get_server(evcon) == NULL);

	/*
	 * At this point, we want to schedule a request to the HTTP
	 * server using our make request method.
	 */
	req = evhttp_request_new(http_request_done, (void*) BASIC_REQUEST_BODY);

	/* Add the information that we care about */
	evhttp_add_header(evhttp_request_get_output_headers(req), "Host", "somehost");

	/* We give ownership of the request to the connection */
	if (evhttp_make_request(evcon, req, EVHTTP_REQ_GET, "/test") == -1) {
		fprintf(stdout, "FAILED\n");
		exit(1);
	}

	event_base_dispatch(data->base);

	tt_assert(test_ok);

	/* try to make another request over the same connection */
	test_ok = 0;

	req = evhttp_request_new(http_request_done, (void*) BASIC_REQUEST_BODY);

	/* Add the information that we care about */
	evhttp_add_header(evhttp_request_get_output_headers(req), "Host", "somehost");

	/*
	 * if our connections are not supposed to be persistent; request
	 * a close from the server.
	 */
	if (!persistent)
		evhttp_add_header(evhttp_request_get_output_headers(req), "Connection", "close");

	/* We give ownership of the request to the connection */
	if (evhttp_make_request(evcon, req, EVHTTP_REQ_GET, "/test") == -1) {
		tt_abort_msg("couldn't make request");
	}

	event_base_dispatch(data->base);

	/* make another request: request empty reply */
	test_ok = 0;

	req = evhttp_request_new(http_request_empty_done, data->base);

	/* Add the information that we care about */
	evhttp_add_header(evhttp_request_get_output_headers(req), "Empty", "itis");

	/* We give ownership of the request to the connection */
	if (evhttp_make_request(evcon, req, EVHTTP_REQ_GET, "/test") == -1) {
		tt_abort_msg("Couldn't make request");
	}

	event_base_dispatch(data->base);

 end:
	if (evcon)
		evhttp_connection_free(evcon);
	if (http)
		evhttp_free(http);
}