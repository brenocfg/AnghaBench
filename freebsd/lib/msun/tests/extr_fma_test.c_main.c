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
 int FE_DOWNWARD ; 
 int FE_TONEAREST ; 
 int FE_TOWARDZERO ; 
 int FE_UPWARD ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fesetround (int) ; 
 unsigned int nitems (int*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  test_accuracy () ; 
 int /*<<< orphan*/  test_big_z () ; 
 int /*<<< orphan*/  test_double_rounding () ; 
 int /*<<< orphan*/  test_infinities () ; 
 int /*<<< orphan*/  test_nans () ; 
 int /*<<< orphan*/  test_small_z () ; 
 int /*<<< orphan*/  test_zeroes () ; 

int
main(void)
{
	int rmodes[] = { FE_TONEAREST, FE_UPWARD, FE_DOWNWARD, FE_TOWARDZERO };
	unsigned i, j;

#if defined(__i386__)
	printf("1..0 # SKIP all testcases fail on i386\n");
	exit(0);
#endif

	j = 1;

	printf("1..19\n");

	for (i = 0; i < nitems(rmodes); i++, j++) {
		printf("rmode = %d\n", rmodes[i]);
		fesetround(rmodes[i]);
		test_zeroes();
		printf("ok %d - fma zeroes\n", j);
	}

	for (i = 0; i < nitems(rmodes); i++, j++) {
#if defined(__amd64__)
		printf("ok %d # SKIP testcase fails assertion on "
		    "amd64\n", j);
		continue;
#else
		printf("rmode = %d\n", rmodes[i]);
		fesetround(rmodes[i]);
		test_infinities();
		printf("ok %d - fma infinities\n", j);
#endif
	}

	fesetround(FE_TONEAREST);
	test_nans();
	printf("ok %d - fma NaNs\n", j);
	j++;

	for (i = 0; i < nitems(rmodes); i++, j++) {
		printf("rmode = %d\n", rmodes[i]);
		fesetround(rmodes[i]);
		test_small_z();
		printf("ok %d - fma small z\n", j);
	}

	for (i = 0; i < nitems(rmodes); i++, j++) {
		printf("rmode = %d\n", rmodes[i]);
		fesetround(rmodes[i]);
		test_big_z();
		printf("ok %d - fma big z\n", j);
	}

	fesetround(FE_TONEAREST);
	test_accuracy();
	printf("ok %d - fma accuracy\n", j);
	j++;

	test_double_rounding();
	printf("ok %d - fma double rounding\n", j);
	j++;

	/*
	 * TODO:
	 * - Tests for subnormals
	 * - Cancellation tests (e.g., z = (double)x*y, but x*y is inexact)
	 */

	return (0);
}