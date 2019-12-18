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
struct event_overlapped {int dummy; } ;
struct bufferevent {int /*<<< orphan*/  ev_base; int /*<<< orphan*/  input; } ;
struct TYPE_2__ {struct bufferevent bev; scalar_t__ connecting; } ;
struct bufferevent_async {TYPE_1__ bev; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;
typedef  int /*<<< orphan*/  ev_uintptr_t ;
typedef  int /*<<< orphan*/  ev_ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  BEV_EVENT_CONNECTED ; 
 int /*<<< orphan*/  BEV_EVENT_ERROR ; 
 int /*<<< orphan*/  BEV_LOCK (struct bufferevent*) ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (scalar_t__) ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_UPDATE_CONNECT_CONTEXT ; 
 int /*<<< orphan*/  bev_async_set_wsa_error (struct bufferevent*,struct event_overlapped*) ; 
 int /*<<< orphan*/  bufferevent_async_set_connected_ (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_decref_and_unlock_ (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_run_eventcb_ (struct bufferevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evbuffer_overlapped_get_fd_ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_base_del_virtual_ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct bufferevent_async* upcast_connect (struct event_overlapped*) ; 

__attribute__((used)) static void
connect_complete(struct event_overlapped *eo, ev_uintptr_t key,
    ev_ssize_t nbytes, int ok)
{
	struct bufferevent_async *bev_a = upcast_connect(eo);
	struct bufferevent *bev = &bev_a->bev.bev;
	evutil_socket_t sock;

	BEV_LOCK(bev);

	EVUTIL_ASSERT(bev_a->bev.connecting);
	bev_a->bev.connecting = 0;
	sock = evbuffer_overlapped_get_fd_(bev_a->bev.bev.input);
	/* XXXX Handle error? */
	setsockopt(sock, SOL_SOCKET, SO_UPDATE_CONNECT_CONTEXT, NULL, 0);

	if (ok)
		bufferevent_async_set_connected_(bev);
	else
		bev_async_set_wsa_error(bev, eo);

	bufferevent_run_eventcb_(bev,
			ok? BEV_EVENT_CONNECTED : BEV_EVENT_ERROR, 0);

	event_base_del_virtual_(bev->ev_base);

	bufferevent_decref_and_unlock_(bev);
}