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
struct event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVLOOP_ONCE ; 
 int /*<<< orphan*/  EV_READ ; 
 int /*<<< orphan*/  cleanup_test () ; 
 int event_add (struct event*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_del (struct event*) ; 
 int /*<<< orphan*/  event_loop (int /*<<< orphan*/ ) ; 
 scalar_t__ event_pending (struct event*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_set (struct event*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct event*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/ * pair ; 
 int /*<<< orphan*/  re_add_read_cb ; 
 struct event* readd_test_event_last_added ; 
 int /*<<< orphan*/  setup_test (char*) ; 
 int test_ok ; 
 int /*<<< orphan*/  tt_fail_perror (char*) ; 
 scalar_t__ write (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
test_nonpersist_readd(void)
{
	struct event ev1, ev2;

	setup_test("Re-add nonpersistent events: ");
	event_set(&ev1, pair[0], EV_READ, re_add_read_cb, &ev2);
	event_set(&ev2, pair[1], EV_READ, re_add_read_cb, &ev1);

	if (write(pair[0], "Hello", 5) < 0) {
		tt_fail_perror("write(pair[0])");
	}

	if (write(pair[1], "Hello", 5) < 0) {
		tt_fail_perror("write(pair[1])\n");
	}

	if (event_add(&ev1, NULL) == -1 ||
	    event_add(&ev2, NULL) == -1) {
		test_ok = 0;
	}
	if (test_ok != 0)
		exit(1);
	event_loop(EVLOOP_ONCE);
	if (test_ok != 2)
		exit(1);
	/* At this point, we executed both callbacks.  Whichever one got
	 * called first added the second, but the second then immediately got
	 * deleted before its callback was called.  At this point, though, it
	 * re-added the first.
	 */
	if (!readd_test_event_last_added) {
		test_ok = 0;
	} else if (readd_test_event_last_added == &ev1) {
		if (!event_pending(&ev1, EV_READ, NULL) ||
		    event_pending(&ev2, EV_READ, NULL))
			test_ok = 0;
	} else {
		if (event_pending(&ev1, EV_READ, NULL) ||
		    !event_pending(&ev2, EV_READ, NULL))
			test_ok = 0;
	}

	event_del(&ev1);
	event_del(&ev2);

	cleanup_test();
}