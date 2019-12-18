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
struct bufferevent {int /*<<< orphan*/  cbarg; int /*<<< orphan*/  (* errorcb ) (struct bufferevent*,short,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* writecb ) (struct bufferevent*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* readcb ) (struct bufferevent*,int /*<<< orphan*/ ) ;} ;
struct bufferevent_private {int eventcb_pending; int errno_pending; scalar_t__ writecb_pending; scalar_t__ readcb_pending; struct bufferevent bev; } ;

/* Variables and functions */
 int BEV_EVENT_CONNECTED ; 
 int /*<<< orphan*/  BEV_LOCK (struct bufferevent*) ; 
 int /*<<< orphan*/  EVUTIL_SET_SOCKET_ERROR (int) ; 
 int /*<<< orphan*/  bufferevent_decref_and_unlock_ (struct bufferevent*) ; 
 int /*<<< orphan*/  stub1 (struct bufferevent*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct bufferevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct bufferevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct bufferevent*,short,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bufferevent_run_deferred_callbacks_locked(struct event_callback *cb, void *arg)
{
	struct bufferevent_private *bufev_private = arg;
	struct bufferevent *bufev = &bufev_private->bev;

	BEV_LOCK(bufev);
	if ((bufev_private->eventcb_pending & BEV_EVENT_CONNECTED) &&
	    bufev->errorcb) {
		/* The "connected" happened before any reads or writes, so
		   send it first. */
		bufev_private->eventcb_pending &= ~BEV_EVENT_CONNECTED;
		bufev->errorcb(bufev, BEV_EVENT_CONNECTED, bufev->cbarg);
	}
	if (bufev_private->readcb_pending && bufev->readcb) {
		bufev_private->readcb_pending = 0;
		bufev->readcb(bufev, bufev->cbarg);
	}
	if (bufev_private->writecb_pending && bufev->writecb) {
		bufev_private->writecb_pending = 0;
		bufev->writecb(bufev, bufev->cbarg);
	}
	if (bufev_private->eventcb_pending && bufev->errorcb) {
		short what = bufev_private->eventcb_pending;
		int err = bufev_private->errno_pending;
		bufev_private->eventcb_pending = 0;
		bufev_private->errno_pending = 0;
		EVUTIL_SET_SOCKET_ERROR(err);
		bufev->errorcb(bufev, what, bufev->cbarg);
	}
	bufferevent_decref_and_unlock_(bufev);
}