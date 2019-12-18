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
 int /*<<< orphan*/  EVUTIL_SHUT_WR ; 
 int /*<<< orphan*/  EV_READ ; 
 int /*<<< orphan*/  TEST1 ; 
 int /*<<< orphan*/  cleanup_test () ; 
 int event_add (struct event*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_dispatch () ; 
 int /*<<< orphan*/  event_set (struct event*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/ * pair ; 
 int /*<<< orphan*/  setup_test (char*) ; 
 int /*<<< orphan*/  shutdown (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simpleread_multiple_cb ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tt_fail_perror (char*) ; 
 scalar_t__ write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
test_simpleread_multiple(void)
{
	struct event one, two;

	/* Very simple read test */
	setup_test("Simple read to multiple evens: ");

	if (write(pair[0], TEST1, strlen(TEST1)+1) < 0) {
		tt_fail_perror("write");
	}

	shutdown(pair[0], EVUTIL_SHUT_WR);

	event_set(&one, pair[1], EV_READ, simpleread_multiple_cb, NULL);
	if (event_add(&one, NULL) == -1)
		exit(1);
	event_set(&two, pair[1], EV_READ, simpleread_multiple_cb, NULL);
	if (event_add(&two, NULL) == -1)
		exit(1);
	event_dispatch();

	cleanup_test();
}