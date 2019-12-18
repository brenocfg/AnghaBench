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
 int /*<<< orphan*/  FP_PE ; 
 int /*<<< orphan*/  fpsetprec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  run_exp2_tests () ; 
 int /*<<< orphan*/  run_generic_tests () ; 

int
main(void)
{

	printf("1..3\n");

	run_generic_tests();
	printf("ok 1 - exponential\n");

#ifdef __i386__
	fpsetprec(FP_PE);
	run_generic_tests();
#endif
	printf("ok 2 - exponential\n");

	run_exp2_tests();
	printf("ok 3 - exponential\n");

	return (0);
}