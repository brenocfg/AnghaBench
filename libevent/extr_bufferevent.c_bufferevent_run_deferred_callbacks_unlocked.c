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
struct event_callback {int dummy; } ;
struct bufferevent {void* cbarg; int /*<<< orphan*/  (* errorcb ) (struct bufferevent*,short,void*) ;int /*<<< orphan*/  (* writecb ) (struct bufferevent*,void*) ;int /*<<< orphan*/  (* readcb ) (struct bufferevent*,void*) ;} ;
struct bufferevent_private {short eventcb_pending; int errno_pending; scalar_t__ writecb_pending; scalar_t__ readcb_pending; struct bufferevent bev; } ;
typedef  int /*<<< orphan*/  (* bufferevent_event_cb ) (struct bufferevent*,short,void*) ;
typedef  int /*<<< orphan*/  (* bufferevent_data_cb ) (struct bufferevent*,void*) ;

/* Variables and functions */
 short BEV_EVENT_CONNECTED ; 
 int /*<<< orphan*/  BEV_LOCK (struct bufferevent*) ; 
 int /*<<< orphan*/  EVUTIL_SET_SOCKET_ERROR (int) ; 
 int /*<<< orphan*/  UNLOCKED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_decref_and_unlock_ (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_inbuf_wm_check (struct bufferevent*) ; 

__attribute__((used)) static void
bufferevent_run_deferred_callbacks_unlocked(struct event_callback *cb, void *arg)
{
	struct bufferevent_private *bufev_private = arg;
	struct bufferevent *bufev = &bufev_private->bev;

	BEV_LOCK(bufev);
#define UNLOCKED(stmt) \
	do { BEV_UNLOCK(bufev); stmt; BEV_LOCK(bufev); } while(0)

	if ((bufev_private->eventcb_pending & BEV_EVENT_CONNECTED) &&
	    bufev->errorcb) {
		/* The "connected" happened before any reads or writes, so
		   send it first. */
		bufferevent_event_cb errorcb = bufev->errorcb;
		void *cbarg = bufev->cbarg;
		bufev_private->eventcb_pending &= ~BEV_EVENT_CONNECTED;
		UNLOCKED(errorcb(bufev, BEV_EVENT_CONNECTED, cbarg));
	}
	if (bufev_private->readcb_pending && bufev->readcb) {
		bufferevent_data_cb readcb = bufev->readcb;
		void *cbarg = bufev->cbarg;
		bufev_private->readcb_pending = 0;
		UNLOCKED(readcb(bufev, cbarg));
		bufferevent_inbuf_wm_check(bufev);
	}
	if (bufev_private->writecb_pending && bufev->writecb) {
		bufferevent_data_cb writecb = bufev->writecb;
		void *cbarg = bufev->cbarg;
		bufev_private->writecb_pending = 0;
		UNLOCKED(writecb(bufev, cbarg));
	}
	if (bufev_private->eventcb_pending && bufev->errorcb) {
		bufferevent_event_cb errorcb = bufev->errorcb;
		void *cbarg = bufev->cbarg;
		short what = bufev_private->eventcb_pending;
		int err = bufev_private->errno_pending;
		bufev_private->eventcb_pending = 0;
		bufev_private->errno_pending = 0;
		EVUTIL_SET_SOCKET_ERROR(err);
		UNLOCKED(errorcb(bufev,what,cbarg));
	}
	bufferevent_decref_and_unlock_(bufev);
#undef UNLOCKED
}