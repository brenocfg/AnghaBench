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
typedef  int /*<<< orphan*/  fenv_t ;

/* Variables and functions */
 int /*<<< orphan*/  FE_ALL_EXCEPT ; 
 scalar_t__ FE_DOWNWARD ; 
 int FE_INEXACT ; 
 int FE_OVERFLOW ; 
 scalar_t__ FE_TONEAREST ; 
 int FE_UNDERFLOW ; 
 int NEXCEPTS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ feclearexcept (int) ; 
 scalar_t__ fegetenv (int /*<<< orphan*/ *) ; 
 scalar_t__ fegetround () ; 
 scalar_t__ fesetenv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fesetround (scalar_t__) ; 
 int fetestexcept (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raiseexcept (int) ; 
 int* std_except_sets ; 

__attribute__((used)) static void
test_fegsetenv(void)
{
	fenv_t env1, env2;
	int excepts, i;

	for (i = 0; i < 1 << NEXCEPTS; i++) {
		excepts = std_except_sets[i];

		assert(fetestexcept(FE_ALL_EXCEPT) == 0);
		assert(fegetround() == FE_TONEAREST);
		assert(fegetenv(&env1) == 0);

		/*
		 * fe[gs]etenv() should be able to save and restore
		 * exception flags without the spurious inexact
		 * exceptions that afflict raiseexcept().
		 */
		raiseexcept(excepts);
		if ((excepts & (FE_UNDERFLOW | FE_OVERFLOW)) != 0 &&
		    (excepts & FE_INEXACT) == 0)
			assert(feclearexcept(FE_INEXACT) == 0);

		fesetround(FE_DOWNWARD);
		assert(fegetenv(&env2) == 0);
		assert(fesetenv(&env1) == 0);
		assert(fetestexcept(FE_ALL_EXCEPT) == 0);
		assert(fegetround() == FE_TONEAREST);

		assert(fesetenv(&env2) == 0);
		assert(fetestexcept(FE_ALL_EXCEPT) == excepts);
		assert(fegetround() == FE_DOWNWARD);
		assert(fesetenv(&env1) == 0);
		assert(fetestexcept(FE_ALL_EXCEPT) == 0);
		assert(fegetround() == FE_TONEAREST);
	}
}