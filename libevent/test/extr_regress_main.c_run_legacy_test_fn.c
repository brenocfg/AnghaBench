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
struct basic_test_data {int /*<<< orphan*/  (* legacy_test_fn ) () ;} ;

/* Variables and functions */
 scalar_t__ called ; 
 int in_legacy_test_wrapper ; 
 int /*<<< orphan*/  stub1 () ; 
 scalar_t__ test_ok ; 
 int /*<<< orphan*/  tt_abort_msg (char*) ; 

void
run_legacy_test_fn(void *ptr)
{
	struct basic_test_data *data = ptr;
	test_ok = called = 0;

	in_legacy_test_wrapper = 1;
	data->legacy_test_fn(); /* This part actually calls the test */
	in_legacy_test_wrapper = 0;

	if (!test_ok)
		tt_abort_msg("Legacy unit test failed");

end:
	test_ok = 0;
}