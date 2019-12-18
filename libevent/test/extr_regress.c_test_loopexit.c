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
struct timeval {int tv_usec; int tv_sec; } ;
struct event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cleanup_test () ; 
 int /*<<< orphan*/  event_base_got_break (int /*<<< orphan*/ ) ; 
 int event_base_got_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_dispatch () ; 
 int /*<<< orphan*/  event_loopexit (struct timeval*) ; 
 int /*<<< orphan*/  evtimer_add (struct event*,struct timeval*) ; 
 int /*<<< orphan*/  evtimer_del (struct event*) ; 
 int /*<<< orphan*/  evtimer_set (struct event*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evutil_gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  global_base ; 
 int /*<<< orphan*/  setup_test (char*) ; 
 int test_ok ; 
 int /*<<< orphan*/  test_timeval_diff_eq (struct timeval*,struct timeval*,int) ; 
 int /*<<< orphan*/  timeout_cb ; 
 int /*<<< orphan*/  tt_assert (int) ; 

__attribute__((used)) static void
test_loopexit(void)
{
	struct timeval tv, tv_start, tv_end;
	struct event ev;

	setup_test("Loop exit: ");

	tv.tv_usec = 0;
	tv.tv_sec = 60*60*24;
	evtimer_set(&ev, timeout_cb, NULL);
	evtimer_add(&ev, &tv);

	tv.tv_usec = 300*1000;
	tv.tv_sec = 0;
	event_loopexit(&tv);

	evutil_gettimeofday(&tv_start, NULL);
	event_dispatch();
	evutil_gettimeofday(&tv_end, NULL);

	evtimer_del(&ev);

	tt_assert(event_base_got_exit(global_base));
	tt_assert(!event_base_got_break(global_base));

	test_timeval_diff_eq(&tv_start, &tv_end, 300);

	test_ok = 1;
end:
	cleanup_test();
}