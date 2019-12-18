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
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  run_accuracy_tests () ; 
 int /*<<< orphan*/  run_generic_tests () ; 
 int /*<<< orphan*/  run_log1p_accuracy_tests () ; 
 int /*<<< orphan*/  run_log2_tests () ; 
 int /*<<< orphan*/  run_roundingmode_tests () ; 

int
main(void)
{

	printf("1..5\n");

	run_generic_tests();
	printf("ok 1 - logarithm\n");

	run_log2_tests();
	printf("ok 2 - logarithm\n");

	run_roundingmode_tests();
	printf("ok 3 - logarithm\n");

	run_accuracy_tests();
	printf("ok 4 - logarithm\n");

	run_log1p_accuracy_tests();
	printf("ok 5 - logarithm\n");

	return (0);
}