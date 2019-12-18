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
typedef  int /*<<< orphan*/  w2 ;
typedef  int /*<<< orphan*/  w1 ;
struct both {int nread; int /*<<< orphan*/  ev; } ;
typedef  int /*<<< orphan*/  r2 ;
typedef  int /*<<< orphan*/  r1 ;

/* Variables and functions */
 int /*<<< orphan*/  EV_READ ; 
 int /*<<< orphan*/  EV_WRITE ; 
 int /*<<< orphan*/  cleanup_test () ; 
 int /*<<< orphan*/  combined_read_cb ; 
 int /*<<< orphan*/  combined_write_cb ; 
 int event_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_dispatch () ; 
 int /*<<< orphan*/  event_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct both*) ; 
 int /*<<< orphan*/  memset (struct both*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * pair ; 
 int /*<<< orphan*/  setup_test (char*) ; 
 int test_ok ; 
 int /*<<< orphan*/  tt_assert (int) ; 

__attribute__((used)) static void
test_combined(void)
{
	struct both r1, r2, w1, w2;

	setup_test("Combined read/write: ");
	memset(&r1, 0, sizeof(r1));
	memset(&r2, 0, sizeof(r2));
	memset(&w1, 0, sizeof(w1));
	memset(&w2, 0, sizeof(w2));

	w1.nread = 4096;
	w2.nread = 8192;

	event_set(&r1.ev, pair[0], EV_READ, combined_read_cb, &r1);
	event_set(&w1.ev, pair[0], EV_WRITE, combined_write_cb, &w1);
	event_set(&r2.ev, pair[1], EV_READ, combined_read_cb, &r2);
	event_set(&w2.ev, pair[1], EV_WRITE, combined_write_cb, &w2);
	tt_assert(event_add(&r1.ev, NULL) != -1);
	tt_assert(!event_add(&w1.ev, NULL));
	tt_assert(!event_add(&r2.ev, NULL));
	tt_assert(!event_add(&w2.ev, NULL));
	event_dispatch();

	if (r1.nread == 8192 && r2.nread == 4096)
		test_ok = 1;

end:
	cleanup_test();
}