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

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 scalar_t__ geteuid () ; 
 scalar_t__ getuid () ; 
 int /*<<< orphan*/  run (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ something_failed ; 
 int /*<<< orphan*/ * tests ; 
 int tests_count ; 

int
main(int argc, char *argv[])
{
	int i;

	/*
	 * This test suite will need to become quite a bit more enlightened
	 * if the notion of privilege is truly separated from root, as tests
	 * make assumptions about when privilege will be present.  In
	 * particular, VFS-related tests need to manage uids in order to
	 * force the use of privilege, and will likely need checking.
	 */
	if (getuid() != 0 && geteuid() != 0)
		errx(-1, "must be run as root");

	/*
	 * Run each test four times, varying whether the process is running
	 * as root and in jail in order to test all possible combinations.
	 */
	for (i = 0; i < tests_count; i++) {
		run(&tests[i], 0, 0);
		run(&tests[i], 0, 1);
		run(&tests[i], 1, 0);
		run(&tests[i], 1, 1);
	}
	return (something_failed ? EXIT_FAILURE : EXIT_SUCCESS);
}