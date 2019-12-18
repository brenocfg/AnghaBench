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
struct sockaddr {int dummy; } ;
struct event_base {int dummy; } ;
struct evconnlistener {int dummy; } ;
struct bufferevent {int dummy; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  BEV_OPT_CLOSE_ON_FREE ; 
 int EV_READ ; 
 int EV_WRITE ; 
 int /*<<< orphan*/  bufferevent_enable (struct bufferevent*,int) ; 
 int /*<<< orphan*/  bufferevent_setcb (struct bufferevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct bufferevent* bufferevent_socket_new (struct event_base*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct event_base* evconnlistener_get_base (struct evconnlistener*) ; 
 int /*<<< orphan*/  server_event_cb ; 
 int /*<<< orphan*/  server_read_cb ; 

__attribute__((used)) static void
listener_accept_cb(struct evconnlistener *listener, evutil_socket_t sock,
                   struct sockaddr *addr, int len, void *ptr)
{
	struct event_base *base = evconnlistener_get_base(listener);
	struct bufferevent *bev = bufferevent_socket_new(base, sock,
		BEV_OPT_CLOSE_ON_FREE);
	bufferevent_setcb(bev, server_read_cb, NULL, server_event_cb, NULL);
	bufferevent_enable(bev, EV_READ|EV_WRITE);
}