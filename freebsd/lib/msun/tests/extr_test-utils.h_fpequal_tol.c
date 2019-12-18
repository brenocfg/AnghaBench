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
 unsigned int CS_BOTH ; 
 unsigned int FPE_ABS_ZERO ; 
 scalar_t__ fabsl (long double) ; 
 int /*<<< orphan*/  feholdexcept (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fesetenv (int /*<<< orphan*/ *) ; 
 scalar_t__ isnan (long double) ; 
 int /*<<< orphan*/  signbit (long double) ; 

__attribute__((used)) static int
fpequal_tol(long double x, long double y, long double tol,
    unsigned int flags)
{
	fenv_t env;
	int ret;

	if (isnan(x) && isnan(y))
		return (1);
	if (!signbit(x) != !signbit(y) && (flags & CS_BOTH))
		return (0);
	if (x == y)
		return (1);
	if (tol == 0)
		return (0);

	/* Hard case: need to check the tolerance. */
	feholdexcept(&env);
	/*
	 * For our purposes here, if y=0, we interpret tol as an absolute
	 * tolerance. This is to account for roundoff in the input, e.g.,
	 * cos(Pi/2) ~= 0.
	 */
	if ((flags & FPE_ABS_ZERO) && y == 0.0)
		ret = fabsl(x - y) <= fabsl(tol);
	else
		ret = fabsl(x - y) <= fabsl(y * tol);
	fesetenv(&env);
	return (ret);
}