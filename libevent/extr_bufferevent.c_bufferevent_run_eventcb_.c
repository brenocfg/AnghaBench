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
struct bufferevent_private {int options; short eventcb_pending; int /*<<< orphan*/  errno_pending; } ;
struct bufferevent {int /*<<< orphan*/  cbarg; int /*<<< orphan*/  (* errorcb ) (struct bufferevent*,short,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int BEV_OPT_DEFER_CALLBACKS ; 
 struct bufferevent_private* BEV_UPCAST (struct bufferevent*) ; 
 int /*<<< orphan*/  EVUTIL_SOCKET_ERROR () ; 
 int /*<<< orphan*/  SCHEDULE_DEFERRED (struct bufferevent_private*) ; 
 int /*<<< orphan*/  stub1 (struct bufferevent*,short,int /*<<< orphan*/ ) ; 

void
bufferevent_run_eventcb_(struct bufferevent *bufev, short what, int options)
{
	/* Requires that we hold the lock and a reference */
	struct bufferevent_private *p = BEV_UPCAST(bufev);
	if (bufev->errorcb == NULL)
		return;
	if ((p->options|options) & BEV_OPT_DEFER_CALLBACKS) {
		p->eventcb_pending |= what;
		p->errno_pending = EVUTIL_SOCKET_ERROR();
		SCHEDULE_DEFERRED(p);
	} else {
		bufev->errorcb(bufev, what, bufev->cbarg);
	}
}