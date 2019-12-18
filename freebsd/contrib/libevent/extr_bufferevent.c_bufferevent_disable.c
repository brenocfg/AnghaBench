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
struct bufferevent {short enabled; TYPE_1__* be_ops; } ;
struct TYPE_2__ {scalar_t__ (* disable ) (struct bufferevent*,short) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BEV_LOCK (struct bufferevent*) ; 
 int /*<<< orphan*/  BEV_UNLOCK (struct bufferevent*) ; 
 scalar_t__ stub1 (struct bufferevent*,short) ; 

int
bufferevent_disable(struct bufferevent *bufev, short event)
{
	int r = 0;

	BEV_LOCK(bufev);
	bufev->enabled &= ~event;

	if (bufev->be_ops->disable(bufev, event) < 0)
		r = -1;

	BEV_UNLOCK(bufev);
	return r;
}