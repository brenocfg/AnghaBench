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
typedef  int __uint32_t ;
typedef  int __uint16_t ;

/* Variables and functions */
 int FE_ALL_EXCEPT ; 
 scalar_t__ __HAS_SSE () ; 
 int /*<<< orphan*/  __fnstsw (int*) ; 
 int /*<<< orphan*/  __stmxcsr (int*) ; 
 int /*<<< orphan*/  feraiseexcept (int) ; 
 int /*<<< orphan*/  fesetenv (int /*<<< orphan*/  const*) ; 

int
feupdateenv(const fenv_t *envp)
{
	__uint32_t mxcsr;
	__uint16_t status;

	__fnstsw(&status);
	if (__HAS_SSE())
		__stmxcsr(&mxcsr);
	else
		mxcsr = 0;
	fesetenv(envp);
	feraiseexcept((mxcsr | status) & FE_ALL_EXCEPT);
	return (0);
}