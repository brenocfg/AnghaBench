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
 int /*<<< orphan*/  EV_WRITE ; 
 int /*<<< orphan*/  cleanup_test () ; 
 int event_add (struct event*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_dispatch () ; 
 int /*<<< orphan*/  event_set (struct event*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct event*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/ * pair ; 
 int /*<<< orphan*/  setup_test (char*) ; 
 int /*<<< orphan*/  simple_write_cb ; 

__attribute__((used)) static void
test_simplewrite(void)
{
	struct event ev;

	/* Very simple write test */
	setup_test("Simple write: ");

	event_set(&ev, pair[0], EV_WRITE, simple_write_cb, &ev);
	if (event_add(&ev, NULL) == -1)
		exit(1);
	event_dispatch();

	cleanup_test();
}