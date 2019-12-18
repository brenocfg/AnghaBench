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
typedef  int /*<<< orphan*/  terminate_state ;
struct timeval {int tv_usec; } ;
struct terminate_state {scalar_t__ gotclosecb; struct bufferevent* bev; scalar_t__ fd; int /*<<< orphan*/  base; } ;
struct bufferevent {int dummy; } ;
struct basic_test_data {int /*<<< orphan*/  base; } ;
typedef  scalar_t__ evutil_socket_t ;
typedef  int /*<<< orphan*/  ev_uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  EV_TIMEOUT ; 
 int /*<<< orphan*/  bufferevent_setcb (struct bufferevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bufferevent* bufferevent_socket_new (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_write (struct bufferevent*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_base_dispatch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_base_once (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct terminate_state*,struct timeval*) ; 
 int /*<<< orphan*/  evhttp_del_cb (scalar_t__,char*) ; 
 int /*<<< orphan*/  evhttp_free (scalar_t__) ; 
 scalar_t__ evhttp_set_cb (scalar_t__,char*,int /*<<< orphan*/ ,struct terminate_state*) ; 
 int /*<<< orphan*/  evutil_closesocket (scalar_t__) ; 
 int /*<<< orphan*/  evutil_timerclear (struct timeval*) ; 
 scalar_t__ http ; 
 scalar_t__ http_connect (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  http_errorcb ; 
 scalar_t__ http_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  http_writecb ; 
 int /*<<< orphan*/  memset (struct terminate_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  terminate_chunked_cb ; 
 int /*<<< orphan*/  terminate_chunked_client ; 
 int /*<<< orphan*/  terminate_readcb ; 
 scalar_t__ test_ok ; 
 int /*<<< orphan*/  tt_assert (int) ; 

__attribute__((used)) static void
http_terminate_chunked_test(void *arg)
{
	struct basic_test_data *data = arg;
	struct bufferevent *bev = NULL;
	struct timeval tv;
	const char *http_request;
	ev_uint16_t port = 0;
	evutil_socket_t fd = -1;
	struct terminate_state terminate_state;

	test_ok = 0;

	http = http_setup(&port, data->base, 0);
	evhttp_del_cb(http, "/test");
	tt_assert(evhttp_set_cb(http, "/test",
		terminate_chunked_cb, &terminate_state) == 0);

	fd = http_connect("127.0.0.1", port);

	/* Stupid thing to send a request */
	bev = bufferevent_socket_new(data->base, fd, 0);
	bufferevent_setcb(bev, terminate_readcb, http_writecb,
	    http_errorcb, data->base);

	memset(&terminate_state, 0, sizeof(terminate_state));
	terminate_state.base = data->base;
	terminate_state.fd = fd;
	terminate_state.bev = bev;
	terminate_state.gotclosecb = 0;

	/* first half of the http request */
	http_request =
	    "GET /test HTTP/1.1\r\n"
	    "Host: some\r\n\r\n";

	bufferevent_write(bev, http_request, strlen(http_request));
	evutil_timerclear(&tv);
	tv.tv_usec = 10000;
	event_base_once(data->base, -1, EV_TIMEOUT, terminate_chunked_client, &terminate_state,
	    &tv);

	event_base_dispatch(data->base);

	if (terminate_state.gotclosecb == 0)
		test_ok = 0;

 end:
	if (fd >= 0)
		evutil_closesocket(fd);
	if (http)
		evhttp_free(http);
}