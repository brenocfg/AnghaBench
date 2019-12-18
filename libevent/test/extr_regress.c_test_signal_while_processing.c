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
struct timeval {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct event_base {int dummy; } ;
struct event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGUSR1 ; 
 int called ; 
 int /*<<< orphan*/  cleanup_test () ; 
 int /*<<< orphan*/  event_base_free (struct event_base*) ; 
 int /*<<< orphan*/  event_dispatch () ; 
 struct event_base* event_init () ; 
 int /*<<< orphan*/  evtimer_add (struct event*,struct timeval*) ; 
 int /*<<< orphan*/  evtimer_set (struct event*,int /*<<< orphan*/ ,struct event*) ; 
 int /*<<< orphan*/  setup_test (char*) ; 
 int /*<<< orphan*/  signal_add (struct event*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_cb_swp ; 
 int /*<<< orphan*/  signal_set (struct event*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int test_ok ; 
 int /*<<< orphan*/  timeout_cb_swp ; 

__attribute__((used)) static void
test_signal_while_processing(void)
{
	struct event_base *base = event_init();
	struct event ev, ev_timer;
	struct timeval tv = {0, 0};

	setup_test("Receiving a signal while processing other signal: ");

	called = -1;
	test_ok = 1;
	signal_set(&ev, SIGUSR1, signal_cb_swp, NULL);
	signal_add(&ev, NULL);
	evtimer_set(&ev_timer, timeout_cb_swp, &ev_timer);
	evtimer_add(&ev_timer, &tv);
	event_dispatch();

	event_base_free(base);
	cleanup_test();
	return;
}