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
typedef  struct evhttp_connection evdns_base ;
struct basic_test_data {void* base; } ;
typedef  int /*<<< orphan*/  ev_uint16_t ;
typedef  int /*<<< orphan*/  address ;

/* Variables and functions */
 scalar_t__ BASIC_REQUEST_BODY ; 
 int /*<<< orphan*/  EVHTTP_REQ_GET ; 
 int /*<<< orphan*/  evdns_base_free (struct evhttp_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdns_base_nameserver_ip_add (struct evhttp_connection*,char*) ; 
 struct evhttp_connection* evdns_base_new (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_base_dispatch (void*) ; 
 int /*<<< orphan*/  evhttp_add_header (int /*<<< orphan*/ ,char*,char*) ; 
 struct evhttp_connection* evhttp_connection_base_new (void*,struct evhttp_connection*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_connection_free (struct evhttp_connection*) ; 
 int /*<<< orphan*/  evhttp_free (struct evhttp*) ; 
 int evhttp_make_request (struct evhttp_connection*,struct evhttp_request*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  evhttp_request_get_output_headers (struct evhttp_request*) ; 
 struct evhttp_request* evhttp_request_new (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  evutil_snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 void* exit_base ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  http_request_done ; 
 int /*<<< orphan*/  http_request_empty_done ; 
 struct evhttp* http_setup (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regress_clean_dnsserver () ; 
 struct evhttp_connection* regress_dnsserver (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  search_table ; 
 int /*<<< orphan*/  stdout ; 
 struct evhttp_connection* test_ok ; 
 int /*<<< orphan*/  tt_abort_msg (char*) ; 
 int /*<<< orphan*/  tt_assert (struct evhttp_connection*) ; 

__attribute__((used)) static void
http_connection_async_test(void *arg)
{
	struct basic_test_data *data = arg;
	ev_uint16_t port = 0;
	struct evhttp_connection *evcon = NULL;
	struct evhttp_request *req = NULL;
	struct evdns_base *dns_base = NULL;
	ev_uint16_t portnum = 0;
	char address[64];
	struct evhttp *http = http_setup(&port, data->base, 0);

	exit_base = data->base;
	tt_assert(regress_dnsserver(data->base, &portnum, search_table));

	dns_base = evdns_base_new(data->base, 0/* init name servers */);
	tt_assert(dns_base);

	/* Add ourself as the only nameserver, and make sure we really are
	 * the only nameserver. */
	evutil_snprintf(address, sizeof(address), "127.0.0.1:%d", portnum);
	evdns_base_nameserver_ip_add(dns_base, address);

	test_ok = 0;

	evcon = evhttp_connection_base_new(data->base, dns_base, "127.0.0.1", port);
	tt_assert(evcon);

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
	if (dns_base)
		evdns_base_free(dns_base, 0);
	regress_clean_dnsserver();
}