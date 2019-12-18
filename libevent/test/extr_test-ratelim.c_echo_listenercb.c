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
struct event {int dummy; } ;
struct evconnlistener {int dummy; } ;
struct bufferevent {int dummy; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int BEV_OPT_CLOSE_ON_FREE ; 
 int BEV_OPT_THREADSAFE ; 
 int /*<<< orphan*/  EV_PERSIST ; 
 int EV_READ ; 
 int EV_WRITE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_add_to_rate_limit_group (struct bufferevent*,scalar_t__) ; 
 int /*<<< orphan*/  bufferevent_enable (struct bufferevent*,int) ; 
 int /*<<< orphan*/ * bufferevent_get_token_bucket_cfg (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_set_rate_limit (struct bufferevent*,scalar_t__) ; 
 int /*<<< orphan*/  bufferevent_setcb (struct bufferevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct bufferevent* bufferevent_socket_new (struct event_base*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  check_bucket_levels_cb ; 
 scalar_t__ conn_bucket_cfg ; 
 int /*<<< orphan*/  echo_eventcb ; 
 int /*<<< orphan*/  echo_readcb ; 
 int /*<<< orphan*/  echo_writecb ; 
 int /*<<< orphan*/  event_add (struct event*,int /*<<< orphan*/ ) ; 
 struct event* event_new (struct event_base*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bufferevent*) ; 
 int /*<<< orphan*/  ms100_common ; 
 int /*<<< orphan*/  n_echo_conns_open ; 
 scalar_t__ ratelim_group ; 

__attribute__((used)) static void
echo_listenercb(struct evconnlistener *listener, evutil_socket_t newsock,
    struct sockaddr *sourceaddr, int socklen, void *ctx)
{
	struct event_base *base = ctx;
	int flags = BEV_OPT_CLOSE_ON_FREE|BEV_OPT_THREADSAFE;
	struct bufferevent *bev;

	bev = bufferevent_socket_new(base, newsock, flags);
	bufferevent_setcb(bev, echo_readcb, echo_writecb, echo_eventcb, NULL);
	if (conn_bucket_cfg) {
		struct event *check_event =
		    event_new(base, -1, EV_PERSIST, check_bucket_levels_cb, bev);
		bufferevent_set_rate_limit(bev, conn_bucket_cfg);

		assert(bufferevent_get_token_bucket_cfg(bev) != NULL);
		event_add(check_event, ms100_common);
	}
	if (ratelim_group)
		bufferevent_add_to_rate_limit_group(bev, ratelim_group);
	++n_echo_conns_open;
	bufferevent_enable(bev, EV_READ|EV_WRITE);
}