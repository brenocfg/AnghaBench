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
struct bufferevent_private {int /*<<< orphan*/  dns_request; } ;
struct bufferevent {int /*<<< orphan*/  enabled; int /*<<< orphan*/  ev_base; int /*<<< orphan*/  ev_write; int /*<<< orphan*/  ev_read; int /*<<< orphan*/  output; int /*<<< orphan*/  input; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  BEV_IS_SOCKET (struct bufferevent*) ; 
 int /*<<< orphan*/  BEV_LOCK (struct bufferevent*) ; 
 int /*<<< orphan*/  BEV_UNLOCK (struct bufferevent*) ; 
 struct bufferevent_private* BEV_UPCAST (struct bufferevent*) ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int /*<<< orphan*/ ) ; 
 int EV_FINALIZE ; 
 int EV_PERSIST ; 
 int EV_READ ; 
 int EV_WRITE ; 
 int /*<<< orphan*/  bufferevent_enable (struct bufferevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_readcb ; 
 int /*<<< orphan*/  bufferevent_writecb ; 
 int /*<<< orphan*/  evbuffer_unfreeze (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  event_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct bufferevent*) ; 
 int /*<<< orphan*/  event_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evutil_getaddrinfo_cancel_async_ (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
be_socket_setfd(struct bufferevent *bufev, evutil_socket_t fd)
{
	struct bufferevent_private *bufev_p = BEV_UPCAST(bufev);

	BEV_LOCK(bufev);
	EVUTIL_ASSERT(BEV_IS_SOCKET(bufev));

	event_del(&bufev->ev_read);
	event_del(&bufev->ev_write);

	evbuffer_unfreeze(bufev->input, 0);
	evbuffer_unfreeze(bufev->output, 1);

	event_assign(&bufev->ev_read, bufev->ev_base, fd,
	    EV_READ|EV_PERSIST|EV_FINALIZE, bufferevent_readcb, bufev);
	event_assign(&bufev->ev_write, bufev->ev_base, fd,
	    EV_WRITE|EV_PERSIST|EV_FINALIZE, bufferevent_writecb, bufev);

	if (fd >= 0)
		bufferevent_enable(bufev, bufev->enabled);

	evutil_getaddrinfo_cancel_async_(bufev_p->dns_request);

	BEV_UNLOCK(bufev);
}