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
 int ALL_STD_EXCEPT ; 
 int FE_ALL_EXCEPT ; 
 int FE_DIVBYZERO ; 
 int FE_INEXACT ; 
 int FE_INVALID ; 
 int FE_OVERFLOW ; 
 int FE_UNDERFLOW ; 
 int NEXCEPTS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ feclearexcept (int) ; 
 scalar_t__ feraiseexcept (int) ; 
 int fetestexcept (int) ; 
 int* std_except_sets ; 

__attribute__((used)) static void
test_feraiseexcept(void)
{
	int excepts, i;

	for (i = 0; i < 1 << NEXCEPTS; i++) {
		excepts = std_except_sets[i];

		assert(fetestexcept(FE_ALL_EXCEPT) == 0);
		assert(feraiseexcept(excepts) == 0);
		if ((excepts & (FE_UNDERFLOW | FE_OVERFLOW)) != 0) {
			excepts |= FE_INEXACT;
			assert((fetestexcept(ALL_STD_EXCEPT) | FE_INEXACT) ==
			    excepts);
		} else {
			assert(fetestexcept(ALL_STD_EXCEPT) == excepts);
		}
		assert(feclearexcept(FE_ALL_EXCEPT) == 0);
	}
	assert(feraiseexcept(FE_INVALID | FE_DIVBYZERO) == 0);
	assert(fetestexcept(ALL_STD_EXCEPT) == (FE_INVALID | FE_DIVBYZERO));
	assert(feraiseexcept(FE_OVERFLOW | FE_UNDERFLOW | FE_INEXACT) == 0);
	assert(fetestexcept(ALL_STD_EXCEPT) == ALL_STD_EXCEPT);
	assert(feclearexcept(FE_ALL_EXCEPT) == 0);
}