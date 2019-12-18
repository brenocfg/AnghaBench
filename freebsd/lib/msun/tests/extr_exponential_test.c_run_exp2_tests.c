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
 scalar_t__ exp2 (unsigned int) ; 
 scalar_t__ exp2f (unsigned int) ; 
 scalar_t__ exp2l (unsigned int) ; 
 int /*<<< orphan*/  feclearexcept (int /*<<< orphan*/ ) ; 
 scalar_t__ fetestexcept (int /*<<< orphan*/ ) ; 
 scalar_t__ ldexp (double,unsigned int) ; 
 scalar_t__ ldexpf (double,unsigned int) ; 
 scalar_t__ ldexpl (double,unsigned int) ; 

__attribute__((used)) static void
run_exp2_tests(void)
{
	unsigned i;

	/*
	 * We should insist that exp2() return exactly the correct
	 * result and not raise an inexact exception for integer
	 * arguments.
	 */
	feclearexcept(FE_ALL_EXCEPT);
	for (i = FLT_MIN_EXP - FLT_MANT_DIG; i < FLT_MAX_EXP; i++) {
		assert(exp2f(i) == ldexpf(1.0, i));
		assert(fetestexcept(ALL_STD_EXCEPT) == 0);
	}
	for (i = DBL_MIN_EXP - DBL_MANT_DIG; i < DBL_MAX_EXP; i++) {
		assert(exp2(i) == ldexp(1.0, i));
		assert(fetestexcept(ALL_STD_EXCEPT) == 0);
	}
	for (i = LDBL_MIN_EXP - LDBL_MANT_DIG; i < LDBL_MAX_EXP; i++) {
		assert(exp2l(i) == ldexpl(1.0, i));
		assert(fetestexcept(ALL_STD_EXCEPT) == 0);
	}
}