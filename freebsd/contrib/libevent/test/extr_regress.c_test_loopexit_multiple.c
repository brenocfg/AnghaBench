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
struct event_base {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cleanup_test () ; 
 int /*<<< orphan*/  event_base_dispatch (struct event_base*) ; 
 int /*<<< orphan*/  event_base_free (struct event_base*) ; 
 int /*<<< orphan*/  event_base_got_break (struct event_base*) ; 
 int event_base_got_exit (struct event_base*) ; 
 int /*<<< orphan*/  event_base_loopexit (struct event_base*,struct timeval*) ; 
 struct event_base* event_base_new () ; 
 int /*<<< orphan*/  evutil_gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_test (char*) ; 
 int test_ok ; 
 int /*<<< orphan*/  test_timeval_diff_eq (struct timeval*,struct timeval*,int) ; 
 int /*<<< orphan*/  tt_assert (int) ; 

__attribute__((used)) static void
test_loopexit_multiple(void)
{
	struct timeval tv, tv_start, tv_end;
	struct event_base *base;

	setup_test("Loop Multiple exit: ");

	base = event_base_new();

	tv.tv_usec = 200*1000;
	tv.tv_sec = 0;
	event_base_loopexit(base, &tv);

	tv.tv_usec = 0;
	tv.tv_sec = 3;
	event_base_loopexit(base, &tv);

	evutil_gettimeofday(&tv_start, NULL);
	event_base_dispatch(base);
	evutil_gettimeofday(&tv_end, NULL);

	tt_assert(event_base_got_exit(base));
	tt_assert(!event_base_got_break(base));

	event_base_free(base);

	test_timeval_diff_eq(&tv_start, &tv_end, 200);

	test_ok = 1;

end:
	cleanup_test();
}