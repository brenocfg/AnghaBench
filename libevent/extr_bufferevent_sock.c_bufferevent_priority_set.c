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
struct bufferevent_private {int /*<<< orphan*/  deferred; } ;
struct bufferevent {int /*<<< orphan*/  ev_write; int /*<<< orphan*/  ev_read; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEV_IS_SOCKET (struct bufferevent*) ; 
 int /*<<< orphan*/  BEV_LOCK (struct bufferevent*) ; 
 int /*<<< orphan*/  BEV_UNLOCK (struct bufferevent*) ; 
 struct bufferevent_private* BEV_UPCAST (struct bufferevent*) ; 
 int /*<<< orphan*/  event_deferred_cb_set_priority_ (int /*<<< orphan*/ *,int) ; 
 int event_priority_set (int /*<<< orphan*/ *,int) ; 

int
bufferevent_priority_set(struct bufferevent *bufev, int priority)
{
	int r = -1;
	struct bufferevent_private *bufev_p = BEV_UPCAST(bufev);

	BEV_LOCK(bufev);
	if (!BEV_IS_SOCKET(bufev))
		goto done;

	if (event_priority_set(&bufev->ev_read, priority) == -1)
		goto done;
	if (event_priority_set(&bufev->ev_write, priority) == -1)
		goto done;

	event_deferred_cb_set_priority_(&bufev_p->deferred, priority);

	r = 0;
done:
	BEV_UNLOCK(bufev);
	return r;
}