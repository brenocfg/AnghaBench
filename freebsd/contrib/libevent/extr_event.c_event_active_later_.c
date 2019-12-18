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
struct event {int /*<<< orphan*/  ev_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVBASE_ACQUIRE_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVBASE_RELEASE_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_active_later_nolock_ (struct event*,int) ; 
 int /*<<< orphan*/  th_base_lock ; 

void
event_active_later_(struct event *ev, int res)
{
	EVBASE_ACQUIRE_LOCK(ev->ev_base, th_base_lock);
	event_active_later_nolock_(ev, res);
	EVBASE_RELEASE_LOCK(ev->ev_base, th_base_lock);
}