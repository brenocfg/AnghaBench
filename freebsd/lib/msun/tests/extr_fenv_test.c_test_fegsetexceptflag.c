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
typedef  int /*<<< orphan*/  fexcept_t ;

/* Variables and functions */
 int ALL_STD_EXCEPT ; 
 int FE_ALL_EXCEPT ; 
 int NEXCEPTS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ feclearexcept (int) ; 
 scalar_t__ fegetexceptflag (int /*<<< orphan*/ *,int) ; 
 scalar_t__ fesetexceptflag (int /*<<< orphan*/ *,int) ; 
 int fetestexcept (int) ; 
 int /*<<< orphan*/  raiseexcept (int) ; 
 int* std_except_sets ; 

__attribute__((used)) static void
test_fegsetexceptflag(void)
{
	fexcept_t flag;
	int excepts, i;

	assert(fetestexcept(FE_ALL_EXCEPT) == 0);
	for (i = 0; i < 1 << NEXCEPTS; i++) {
		excepts = std_except_sets[i];

		assert(fegetexceptflag(&flag, excepts) == 0);
		raiseexcept(ALL_STD_EXCEPT);
		assert(fesetexceptflag(&flag, excepts) == 0);
		assert(fetestexcept(ALL_STD_EXCEPT) ==
		    (ALL_STD_EXCEPT ^ excepts));

		assert(fegetexceptflag(&flag, FE_ALL_EXCEPT) == 0);
		assert(feclearexcept(FE_ALL_EXCEPT) == 0);
		assert(fesetexceptflag(&flag, excepts) == 0);
		assert(fetestexcept(ALL_STD_EXCEPT) == 0);
		assert(fesetexceptflag(&flag, ALL_STD_EXCEPT ^ excepts) == 0);
		assert(fetestexcept(ALL_STD_EXCEPT) ==
		    (ALL_STD_EXCEPT ^ excepts));

		assert(feclearexcept(FE_ALL_EXCEPT) == 0);
	}
}