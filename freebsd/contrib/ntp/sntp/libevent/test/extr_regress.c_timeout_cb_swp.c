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
struct timeval {int member_0; int /*<<< orphan*/  member_1; } ;
struct event {int dummy; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIGUSR1 ; 
 int called ; 
 int /*<<< orphan*/  event_loopexit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evtimer_add (struct event*,struct timeval*) ; 
 int /*<<< orphan*/  raise (int /*<<< orphan*/ ) ; 
 scalar_t__ test_ok ; 

__attribute__((used)) static void
timeout_cb_swp(evutil_socket_t fd, short event, void *arg)
{
	if (called == -1) {
		struct timeval tv = {5, 0};

		called = 0;
		evtimer_add((struct event *)arg, &tv);
		raise(SIGUSR1);
		return;
	}
	test_ok = 0;
	event_loopexit(NULL);
}