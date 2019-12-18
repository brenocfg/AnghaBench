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
struct timeval {int tv_usec; scalar_t__ tv_sec; } ;
struct evhttp_request {int dummy; } ;
struct event_base {int dummy; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  event_base_loopexit (struct event_base*,struct timeval*) ; 
 int /*<<< orphan*/  evhttp_cancel_request (struct evhttp_request*) ; 
 struct event_base* evhttp_connection_get_base (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_request_get_connection (struct evhttp_request*) ; 
 int /*<<< orphan*/  evutil_timerclear (struct timeval*) ; 
 int /*<<< orphan*/  test_ok ; 

__attribute__((used)) static void
http_do_cancel(evutil_socket_t fd, short what, void *arg)
{
	struct evhttp_request *req = arg;
	struct timeval tv;
	struct event_base *base;
	evutil_timerclear(&tv);
	tv.tv_sec = 0;
	tv.tv_usec = 500 * 1000;

	base = evhttp_connection_get_base(evhttp_request_get_connection(req));
	evhttp_cancel_request(req);

	event_base_loopexit(base, &tv);

	++test_ok;
}