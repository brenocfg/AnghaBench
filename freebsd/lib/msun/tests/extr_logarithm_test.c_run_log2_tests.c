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
 int /*<<< orphan*/  ALL_STD_EXCEPT ; 
 unsigned int DBL_MANT_DIG ; 
 unsigned int DBL_MAX_EXP ; 
 unsigned int DBL_MIN_EXP ; 
 int /*<<< orphan*/  FE_ALL_EXCEPT ; 
 unsigned int FLT_MANT_DIG ; 
 unsigned int FLT_MAX_EXP ; 
 unsigned int FLT_MIN_EXP ; 
 unsigned int LDBL_MANT_DIG ; 
 unsigned int LDBL_MAX_EXP ; 
 unsigned int LDBL_MIN_EXP ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ feclearexcept (int /*<<< orphan*/ ) ; 
 scalar_t__ fetestexcept (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldexp (double,unsigned int) ; 
 int /*<<< orphan*/  ldexpf (double,unsigned int) ; 
 int /*<<< orphan*/  ldexpl (double,unsigned int) ; 
 unsigned int log2 (int /*<<< orphan*/ ) ; 
 unsigned int log2f (int /*<<< orphan*/ ) ; 
 unsigned int log2l (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
run_log2_tests(void)
{
	unsigned i;

	/*
	 * We should insist that log2() return exactly the correct
	 * result and not raise an inexact exception for powers of 2.
	 */
	assert(feclearexcept(FE_ALL_EXCEPT) == 0);
	for (i = FLT_MIN_EXP - FLT_MANT_DIG; i < FLT_MAX_EXP; i++) {
		assert(log2f(ldexpf(1.0, i)) == i);
		assert(fetestexcept(ALL_STD_EXCEPT) == 0);
	}
	for (i = DBL_MIN_EXP - DBL_MANT_DIG; i < DBL_MAX_EXP; i++) {
		assert(log2(ldexp(1.0, i)) == i);
		assert(fetestexcept(ALL_STD_EXCEPT) == 0);
	}
	for (i = LDBL_MIN_EXP - LDBL_MANT_DIG; i < LDBL_MAX_EXP; i++) {
		assert(log2l(ldexpl(1.0, i)) == i);
#if 0
		/* XXX This test does not pass yet. */
		assert(fetestexcept(ALL_STD_EXCEPT) == 0);
#endif
	}
}