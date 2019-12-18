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
struct timeval {int tv_usec; } ;
struct bufferevent {int dummy; } ;
struct basic_test_data {int /*<<< orphan*/  base; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;
typedef  int /*<<< orphan*/  ev_uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  EV_TIMEOUT ; 
 int /*<<< orphan*/  bufferevent_free (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_setcb (struct bufferevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bufferevent* bufferevent_socket_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_write (struct bufferevent*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_base_dispatch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_base_once (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bufferevent*,struct timeval*) ; 
 int /*<<< orphan*/  evhttp_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evutil_closesocket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evutil_timerclear (struct timeval*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  http ; 
 int http_bind (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  http_complete_write ; 
 int /*<<< orphan*/  http_connect (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  http_errorcb ; 
 int /*<<< orphan*/  http_readcb ; 
 int /*<<< orphan*/  http_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  http_writecb ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int test_ok ; 
 int /*<<< orphan*/  tt_assert (int) ; 

__attribute__((used)) static void
http_basic_test(void *arg)
{
	struct basic_test_data *data = arg;
	struct timeval tv;
	struct bufferevent *bev = NULL;
	evutil_socket_t fd;
	const char *http_request;
	ev_uint16_t port = 0, port2 = 0;

	test_ok = 0;

	http = http_setup(&port, data->base, 0);

	/* bind to a second socket */
	if (http_bind(http, &port2, 0) == -1) {
		fprintf(stdout, "FAILED (bind)\n");
		exit(1);
	}

	fd = http_connect("127.0.0.1", port);

	/* Stupid thing to send a request */
	bev = bufferevent_socket_new(data->base, fd, 0);
	bufferevent_setcb(bev, http_readcb, http_writecb,
	    http_errorcb, data->base);

	/* first half of the http request */
	http_request =
	    "GET /test HTTP/1.1\r\n"
	    "Host: some";

	bufferevent_write(bev, http_request, strlen(http_request));
	evutil_timerclear(&tv);
	tv.tv_usec = 10000;
	event_base_once(data->base,
	    -1, EV_TIMEOUT, http_complete_write, bev, &tv);

	event_base_dispatch(data->base);

	tt_assert(test_ok == 3);

	/* connect to the second port */
	bufferevent_free(bev);
	evutil_closesocket(fd);

	fd = http_connect("127.0.0.1", port2);

	/* Stupid thing to send a request */
	bev = bufferevent_socket_new(data->base, fd, 0);
	bufferevent_setcb(bev, http_readcb, http_writecb,
	    http_errorcb, data->base);

	http_request =
	    "GET /test HTTP/1.1\r\n"
	    "Host: somehost\r\n"
	    "Connection: close\r\n"
	    "\r\n";

	bufferevent_write(bev, http_request, strlen(http_request));

	event_base_dispatch(data->base);

	tt_assert(test_ok == 5);

	/* Connect to the second port again. This time, send an absolute uri. */
	bufferevent_free(bev);
	evutil_closesocket(fd);

	fd = http_connect("127.0.0.1", port2);

	/* Stupid thing to send a request */
	bev = bufferevent_socket_new(data->base, fd, 0);
	bufferevent_setcb(bev, http_readcb, http_writecb,
	    http_errorcb, data->base);

	http_request =
	    "GET http://somehost.net/test HTTP/1.1\r\n"
	    "Host: somehost\r\n"
	    "Connection: close\r\n"
	    "\r\n";

	bufferevent_write(bev, http_request, strlen(http_request));

	event_base_dispatch(data->base);

	tt_assert(test_ok == 7);

	evhttp_free(http);
 end:
	if (bev)
		bufferevent_free(bev);
}