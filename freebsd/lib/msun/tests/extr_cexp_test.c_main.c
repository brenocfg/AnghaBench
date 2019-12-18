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
 int /*<<< orphan*/  test_imaginaries () ; 
 int /*<<< orphan*/  test_inf () ; 
 int /*<<< orphan*/  test_large () ; 
 int /*<<< orphan*/  test_nan () ; 
 int /*<<< orphan*/  test_reals () ; 
 int /*<<< orphan*/  test_small () ; 
 int /*<<< orphan*/  test_zero () ; 

int
main(void)
{

	printf("1..7\n");

	test_zero();
	printf("ok 1 - cexp zero\n");

	test_nan();
	printf("ok 2 - cexp nan\n");

	test_inf();
	printf("ok 3 - cexp inf\n");

	test_reals();
	printf("ok 4 - cexp reals\n");

	test_imaginaries();
	printf("ok 5 - cexp imaginaries\n");

	test_small();
	printf("ok 6 - cexp small\n");

	test_large();
	printf("ok 7 - cexp large\n");

	return (0);
}