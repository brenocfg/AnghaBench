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
 int /*<<< orphan*/  init_exceptsets () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  test_dfl_env () ; 
 int /*<<< orphan*/  test_fegsetenv () ; 
 int /*<<< orphan*/  test_fegsetexceptflag () ; 
 int /*<<< orphan*/  test_fegsetround () ; 
 int /*<<< orphan*/  test_feholdupdate () ; 
 int /*<<< orphan*/  test_feraiseexcept () ; 
 int /*<<< orphan*/  test_fetestclearexcept () ; 
 int /*<<< orphan*/  test_masking () ; 

int
main(void)
{

	printf("1..8\n");
	init_exceptsets();
	test_dfl_env();
	printf("ok 1 - fenv\n");
	test_fetestclearexcept();
	printf("ok 2 - fenv\n");
	test_fegsetexceptflag();
	printf("ok 3 - fenv\n");
	test_feraiseexcept();
	printf("ok 4 - fenv\n");
	test_fegsetround();
	printf("ok 5 - fenv\n");
	test_fegsetenv();
	printf("ok 6 - fenv\n");
	test_masking();
	printf("ok 7 - fenv\n");
	test_feholdupdate();
	printf("ok 8 - fenv\n");

	return (0);
}