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
struct event_base {int dummy; } ;
struct bufferevent {int /*<<< orphan*/  ev_write; int /*<<< orphan*/  ev_read; struct event_base* ev_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEV_IS_SOCKET (struct bufferevent*) ; 
 int /*<<< orphan*/  BEV_LOCK (struct bufferevent*) ; 
 int /*<<< orphan*/  BEV_UNLOCK (struct bufferevent*) ; 
 int event_base_set (struct event_base*,int /*<<< orphan*/ *) ; 

int
bufferevent_base_set(struct event_base *base, struct bufferevent *bufev)
{
	int res = -1;

	BEV_LOCK(bufev);
	if (!BEV_IS_SOCKET(bufev))
		goto done;

	bufev->ev_base = base;

	res = event_base_set(base, &bufev->ev_read);
	if (res == -1)
		goto done;

	res = event_base_set(base, &bufev->ev_write);
done:
	BEV_UNLOCK(bufev);
	return res;
}