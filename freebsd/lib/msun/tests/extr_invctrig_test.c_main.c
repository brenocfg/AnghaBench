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
 int /*<<< orphan*/  test_axes () ; 
 int /*<<< orphan*/  test_inf () ; 
 int /*<<< orphan*/  test_large () ; 
 int /*<<< orphan*/  test_nan () ; 
 int /*<<< orphan*/  test_small () ; 
 int /*<<< orphan*/  test_zero () ; 

int
main(void)
{

	printf("1..6\n");

	test_zero();
	printf("ok 1 - invctrig zero\n");

	test_nan();
	printf("ok 2 - invctrig nan\n");

	test_inf();
	printf("ok 3 - invctrig inf\n");

	test_axes();
	printf("ok 4 - invctrig axes\n");

	test_small();
	printf("ok 5 - invctrig small\n");

	test_large();
	printf("ok 6 - invctrig large\n");

	return (0);
}