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
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  break_cb ; 
 int /*<<< orphan*/  cleanup_test () ; 
 int event_base_got_break (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_base_got_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_dispatch () ; 
 int /*<<< orphan*/  evtimer_add (struct event*,struct timeval*) ; 
 int /*<<< orphan*/  evtimer_del (struct event*) ; 
 int /*<<< orphan*/  evtimer_set (struct event*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fail_cb ; 
 int /*<<< orphan*/  global_base ; 
 int /*<<< orphan*/  setup_test (char*) ; 
 int /*<<< orphan*/  tt_assert (int) ; 

__attribute__((used)) static void
test_loopbreak(void)
{
	struct event ev1, ev2;
	struct timeval tv;

	setup_test("Loop break: ");

	tv.tv_sec = 0;
	tv.tv_usec = 0;
	evtimer_set(&ev1, break_cb, NULL);
	evtimer_add(&ev1, &tv);
	evtimer_set(&ev2, fail_cb, NULL);
	evtimer_add(&ev2, &tv);

	event_dispatch();

	tt_assert(!event_base_got_exit(global_base));
	tt_assert(event_base_got_break(global_base));

	evtimer_del(&ev1);
	evtimer_del(&ev2);

end:
	cleanup_test();
}