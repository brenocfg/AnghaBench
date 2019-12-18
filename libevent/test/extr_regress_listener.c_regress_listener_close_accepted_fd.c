#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_storage {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {scalar_t__ sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct event_base {int dummy; } ;
struct evconnlistener {int dummy; } ;
struct basic_test_data {struct event_base* base; } ;
typedef  int /*<<< orphan*/  ss ;
typedef  int /*<<< orphan*/  sin ;
typedef  int /*<<< orphan*/  evutil_socket_t ;
typedef  int ev_socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  EVUTIL_INVALID_SOCKET ; 
 unsigned int LEV_OPT_CLOSE_ON_FREE ; 
 unsigned int LEV_OPT_REUSEABLE ; 
 int /*<<< orphan*/  acceptcb_free ; 
 int /*<<< orphan*/  evconnlistener_get_fd (struct evconnlistener*) ; 
 struct evconnlistener* evconnlistener_new_bind (struct event_base*,int /*<<< orphan*/ ,int*,unsigned int,int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  event_base_dispatch (struct event_base*) ; 
 int /*<<< orphan*/  evutil_socket_connect_ (int /*<<< orphan*/ *,struct sockaddr*,int) ; 
 scalar_t__ getsockname (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tt_assert (int) ; 

__attribute__((used)) static void
regress_listener_close_accepted_fd(void *arg)
{
	struct basic_test_data *data = arg;
	struct event_base *base = data->base;
	struct evconnlistener *listener = NULL;
	struct sockaddr_in sin;
	struct sockaddr_storage ss;
	ev_socklen_t slen = sizeof(ss);
	int count = 1;
	unsigned int flags = LEV_OPT_CLOSE_ON_FREE|LEV_OPT_REUSEABLE;
	evutil_socket_t fd = EVUTIL_INVALID_SOCKET;

	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = htonl(0x7f000001); /* 127.0.0.1 */
	sin.sin_port = 0; /* "You pick!" */

	/* Start a listener with a bogus socket. */
	listener = evconnlistener_new_bind(base, acceptcb_free, &count,
	    flags, -1, (struct sockaddr *)&sin, sizeof(sin));
	tt_assert(listener);

	tt_assert(getsockname(evconnlistener_get_fd(listener),
		(struct sockaddr*)&ss, &slen) == 0);
	evutil_socket_connect_(&fd, (struct sockaddr*)&ss, slen);

	event_base_dispatch(base);

end:
	;
}