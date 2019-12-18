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
struct timeval {int tv_usec; scalar_t__ tv_sec; } ;
struct event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cleanup_test () ; 
 int /*<<< orphan*/  event_dispatch () ; 
 int /*<<< orphan*/  evtimer_add (struct event*,struct timeval*) ; 
 int /*<<< orphan*/  evtimer_set (struct event*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evutil_gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evutil_timerclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_test (char*) ; 
 int /*<<< orphan*/  tcalled ; 
 int test_ok ; 
 int /*<<< orphan*/  test_timeval_diff_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  timeout_cb ; 
 int /*<<< orphan*/  tset ; 

__attribute__((used)) static void
test_simpletimeout(void)
{
	struct timeval tv;
	struct event ev;

	setup_test("Simple timeout: ");

	tv.tv_usec = 200*1000;
	tv.tv_sec = 0;
	evutil_timerclear(&tcalled);
	evtimer_set(&ev, timeout_cb, NULL);
	evtimer_add(&ev, &tv);

	evutil_gettimeofday(&tset, NULL);
	event_dispatch();
	test_timeval_diff_eq(&tset, &tcalled, 200);

	test_ok = 1;
end:
	cleanup_test();
}