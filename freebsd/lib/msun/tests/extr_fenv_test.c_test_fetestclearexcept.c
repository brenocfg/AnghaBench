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
 int FE_INEXACT ; 
 int FE_OVERFLOW ; 
 int FE_UNDERFLOW ; 
 int NEXCEPTS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ feclearexcept (int) ; 
 scalar_t__ fetestexcept (int) ; 
 int /*<<< orphan*/  raiseexcept (int) ; 
 int* std_except_sets ; 

__attribute__((used)) static void
test_fetestclearexcept(void)
{
	int excepts, i;

	for (i = 0; i < 1 << NEXCEPTS; i++)
		assert(fetestexcept(std_except_sets[i]) == 0);
	for (i = 0; i < 1 << NEXCEPTS; i++) {
		excepts = std_except_sets[i];

		/* FE_ALL_EXCEPT might be special-cased, as on i386. */
		raiseexcept(excepts);
		assert(fetestexcept(excepts) == excepts);
		assert(feclearexcept(FE_ALL_EXCEPT) == 0);
		assert(fetestexcept(FE_ALL_EXCEPT) == 0);

		raiseexcept(excepts);
		assert(fetestexcept(excepts) == excepts);
		if ((excepts & (FE_UNDERFLOW | FE_OVERFLOW)) != 0) {
			excepts |= FE_INEXACT;
			assert((fetestexcept(ALL_STD_EXCEPT) | FE_INEXACT) ==
			    excepts);
		} else {
			assert(fetestexcept(ALL_STD_EXCEPT) == excepts);
		}
		assert(feclearexcept(excepts) == 0);
		assert(fetestexcept(ALL_STD_EXCEPT) == 0);
	}
}