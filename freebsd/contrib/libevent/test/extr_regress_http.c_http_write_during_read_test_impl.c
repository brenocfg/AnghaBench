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
typedef  int /*<<< orphan*/  ev_uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  EV_READ ; 
 int /*<<< orphan*/  EV_TIMEOUT ; 
 int /*<<< orphan*/  HTTP_BIND_SSL ; 
 int /*<<< orphan*/  bufferevent_disable (struct bufferevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_free (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_setcb (struct bufferevent*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_write (struct bufferevent*,char const*,int /*<<< orphan*/ ) ; 
 struct bufferevent* create_bev (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_base_dispatch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_base_once (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bufferevent*,struct timeval*) ; 
 int /*<<< orphan*/  evhttp_free (struct evhttp*) ; 
 int /*<<< orphan*/  evutil_timerclear (struct timeval*) ; 
 int /*<<< orphan*/  exit_base ; 
 int http_connect (char*,int /*<<< orphan*/ ) ; 
 struct evhttp* http_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  http_write_during_read ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ test_ok ; 

__attribute__((used)) static void
http_write_during_read_test_impl(void *arg, int ssl)
{
	struct basic_test_data *data = arg;
	ev_uint16_t port = 0;
	struct bufferevent *bev = NULL;
	struct timeval tv;
	int fd;
	const char *http_request;
	struct evhttp *http = http_setup(&port, data->base, ssl ? HTTP_BIND_SSL : 0);

	test_ok = 0;
	exit_base = data->base;

	fd = http_connect("127.0.0.1", port);
	bev = create_bev(data->base, fd, 0);
	bufferevent_setcb(bev, NULL, NULL, NULL, data->base);
	bufferevent_disable(bev, EV_READ);

	http_request =
	    "GET /large HTTP/1.1\r\n"
	    "Host: somehost\r\n"
	    "\r\n";

	bufferevent_write(bev, http_request, strlen(http_request));
	evutil_timerclear(&tv);
	tv.tv_usec = 10000;
	event_base_once(data->base, -1, EV_TIMEOUT, http_write_during_read, bev, &tv);

	event_base_dispatch(data->base);

	if (bev)
		bufferevent_free(bev);
	if (http)
		evhttp_free(http);
}