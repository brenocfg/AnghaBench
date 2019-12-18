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
struct event_base {int event_continue; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVBASE_ACQUIRE_LOCK (struct event_base*,int /*<<< orphan*/ ) ; 
 scalar_t__ EVBASE_NEED_NOTIFY (struct event_base*) ; 
 int /*<<< orphan*/  EVBASE_RELEASE_LOCK (struct event_base*,int /*<<< orphan*/ ) ; 
 int evthread_notify_base (struct event_base*) ; 
 int /*<<< orphan*/  th_base_lock ; 

int
event_base_loopcontinue(struct event_base *event_base)
{
	int r = 0;
	if (event_base == NULL)
		return (-1);

	EVBASE_ACQUIRE_LOCK(event_base, th_base_lock);
	event_base->event_continue = 1;

	if (EVBASE_NEED_NOTIFY(event_base)) {
		r = evthread_notify_base(event_base);
	} else {
		r = (0);
	}
	EVBASE_RELEASE_LOCK(event_base, th_base_lock);
	return r;
}