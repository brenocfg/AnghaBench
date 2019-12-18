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
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  EV_READ ; 
 int /*<<< orphan*/  EV_TIMEOUT ; 
 int /*<<< orphan*/  event_active (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int n_pai_calls ; 
 int /*<<< orphan*/ * pai_events ; 

__attribute__((used)) static void
prio_active_inversion_cb(evutil_socket_t fd, short what, void *arg)
{
	int *call_order = arg;
	*call_order = n_pai_calls++;
	if (n_pai_calls == 1) {
		/* This should activate later, even though it shares a
		   priority with us. */
		event_active(&pai_events[1], EV_READ, 1);
		/* This should activate next, since its priority is higher,
		   even though we activated it second. */
		event_active(&pai_events[2], EV_TIMEOUT, 1);
	}
}