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
struct evhttp {int dummy; } ;
struct bufferevent {int dummy; } ;
struct basic_test_data {int /*<<< orphan*/  base; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;
typedef  int /*<<< orphan*/  ev_uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  EV_TIMEOUT ; 
 int HTTP_BIND_SSL ; 
 int /*<<< orphan*/  bufferevent_free (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_setcb (struct bufferevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_write (struct bufferevent*,char const*,int /*<<< orphan*/ ) ; 
 struct bufferevent* create_bev (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  event_base_dispatch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_base_once (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bufferevent*,struct timeval*) ; 
 int /*<<< orphan*/  evhttp_free (struct evhttp*) ; 
 int /*<<< orphan*/  evutil_closesocket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evutil_timerclear (struct timeval*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  exit_base ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int http_bind (struct evhttp*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  http_complete_write ; 
 int /*<<< orphan*/  http_connect (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  http_errorcb ; 
 int /*<<< orphan*/  http_readcb ; 
 struct evhttp* http_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  http_writecb ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int test_ok ; 
 int /*<<< orphan*/  tt_assert (int) ; 

__attribute__((used)) static void
http_basic_test_impl(void *arg, int ssl)
{
	struct basic_test_data *data = arg;
	struct timeval tv;
	struct bufferevent *bev = NULL;
	evutil_socket_t fd;
	const char *http_request;
	ev_uint16_t port = 0, port2 = 0;
	int server_flags = ssl ? HTTP_BIND_SSL : 0;
	struct evhttp *http = http_setup(&port, data->base, server_flags);

	exit_base = data->base;
	test_ok = 0;

	/* bind to a second socket */
	if (http_bind(http, &port2, server_flags) == -1) {
		fprintf(stdout, "FAILED (bind)\n");
		exit(1);
	}

	fd = http_connect("127.0.0.1", port);

	/* Stupid thing to send a request */
	bev = create_bev(data->base, fd, ssl);
	bufferevent_setcb(bev, http_readcb, http_writecb,
	    http_errorcb, data->base);

	/* first half of the http request */
	http_request =
	    "GET /test HTTP/1.1\r\n"
	    "Host: some";

	bufferevent_write(bev, http_request, strlen(http_request));
	evutil_timerclear(&tv);
	tv.tv_usec = 100000;
	event_base_once(data->base,
	    -1, EV_TIMEOUT, http_complete_write, bev, &tv);

	event_base_dispatch(data->base);

	tt_assert(test_ok == 3);

	/* connect to the second port */
	bufferevent_free(bev);
	evutil_closesocket(fd);

	fd = http_connect("127.0.0.1", port2);

	/* Stupid thing to send a request */
	bev = create_bev(data->base, fd, ssl);
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
	bev = create_bev(data->base, fd, ssl);
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