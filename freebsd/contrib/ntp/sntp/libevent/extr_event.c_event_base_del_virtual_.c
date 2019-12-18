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
struct event_base {scalar_t__ virtual_event_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVBASE_ACQUIRE_LOCK (struct event_base*,int /*<<< orphan*/ ) ; 
 scalar_t__ EVBASE_NEED_NOTIFY (struct event_base*) ; 
 int /*<<< orphan*/  EVBASE_RELEASE_LOCK (struct event_base*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 int /*<<< orphan*/  evthread_notify_base (struct event_base*) ; 
 int /*<<< orphan*/  th_base_lock ; 

void
event_base_del_virtual_(struct event_base *base)
{
	EVBASE_ACQUIRE_LOCK(base, th_base_lock);
	EVUTIL_ASSERT(base->virtual_event_count > 0);
	base->virtual_event_count--;
	if (base->virtual_event_count == 0 && EVBASE_NEED_NOTIFY(base))
		evthread_notify_base(base);
	EVBASE_RELEASE_LOCK(base, th_base_lock);
}