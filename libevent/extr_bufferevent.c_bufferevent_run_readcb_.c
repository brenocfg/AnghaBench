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
struct bufferevent_private {int options; int readcb_pending; } ;
struct bufferevent {int /*<<< orphan*/  cbarg; int /*<<< orphan*/  (* readcb ) (struct bufferevent*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int BEV_OPT_DEFER_CALLBACKS ; 
 struct bufferevent_private* BEV_UPCAST (struct bufferevent*) ; 
 int /*<<< orphan*/  SCHEDULE_DEFERRED (struct bufferevent_private*) ; 
 int /*<<< orphan*/  bufferevent_inbuf_wm_check (struct bufferevent*) ; 
 int /*<<< orphan*/  stub1 (struct bufferevent*,int /*<<< orphan*/ ) ; 

void
bufferevent_run_readcb_(struct bufferevent *bufev, int options)
{
	/* Requires that we hold the lock and a reference */
	struct bufferevent_private *p = BEV_UPCAST(bufev);
	if (bufev->readcb == NULL)
		return;
	if ((p->options|options) & BEV_OPT_DEFER_CALLBACKS) {
		p->readcb_pending = 1;
		SCHEDULE_DEFERRED(p);
	} else {
		bufev->readcb(bufev, bufev->cbarg);
		bufferevent_inbuf_wm_check(bufev);
	}
}