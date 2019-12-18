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
struct event_base {int dummy; } ;
struct event {int dummy; } ;
struct basic_test_data {int /*<<< orphan*/ * pair; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_READ ; 
 int /*<<< orphan*/  dummy_read_cb ; 
 int /*<<< orphan*/  event_active (struct event*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  event_add (struct event*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_assign (struct event*,struct event_base*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_base_free (struct event_base*) ; 
 struct event_base* event_init () ; 
 int /*<<< orphan*/  tt_assert (struct event_base*) ; 
 int /*<<< orphan*/  tt_fail_msg (char*) ; 

__attribute__((used)) static void
test_free_active_base(void *ptr)
{
	struct basic_test_data *data = ptr;
	struct event_base *base1;
	struct event ev1;

	base1 = event_init();
	if (base1) {
		event_assign(&ev1, base1, data->pair[1], EV_READ,
			     dummy_read_cb, NULL);
		event_add(&ev1, NULL);
		event_base_free(base1);	 /* should not crash */
	} else {
		tt_fail_msg("failed to create event_base for test");
	}

	base1 = event_init();
	tt_assert(base1);
	event_assign(&ev1, base1, 0, 0, dummy_read_cb, NULL);
	event_active(&ev1, EV_READ, 1);
	event_base_free(base1);
end:
	;
}