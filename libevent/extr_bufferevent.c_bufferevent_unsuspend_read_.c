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
struct bufferevent_private {int /*<<< orphan*/  read_suspended; } ;
struct bufferevent {int enabled; TYPE_1__* be_ops; } ;
typedef  int /*<<< orphan*/  bufferevent_suspend_flags ;
struct TYPE_2__ {int /*<<< orphan*/  (* enable ) (struct bufferevent*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BEV_LOCK (struct bufferevent*) ; 
 int /*<<< orphan*/  BEV_UNLOCK (struct bufferevent*) ; 
 struct bufferevent_private* BEV_UPCAST (struct bufferevent*) ; 
 int EV_READ ; 
 int /*<<< orphan*/  stub1 (struct bufferevent*,int) ; 

void
bufferevent_unsuspend_read_(struct bufferevent *bufev, bufferevent_suspend_flags what)
{
	struct bufferevent_private *bufev_private = BEV_UPCAST(bufev);
	BEV_LOCK(bufev);
	bufev_private->read_suspended &= ~what;
	if (!bufev_private->read_suspended && (bufev->enabled & EV_READ))
		bufev->be_ops->enable(bufev, EV_READ);
	BEV_UNLOCK(bufev);
}