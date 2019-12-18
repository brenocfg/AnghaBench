#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int fexcept_t ;
struct TYPE_4__ {int __status; } ;
typedef  TYPE_1__ fenv_t ;
typedef  int __uint32_t ;

/* Variables and functions */
 scalar_t__ __HAS_SSE () ; 
 int /*<<< orphan*/  __fldenv (TYPE_1__*) ; 
 int /*<<< orphan*/  __fnstenv (TYPE_1__*) ; 
 int /*<<< orphan*/  __ldmxcsr (int*) ; 
 int /*<<< orphan*/  __stmxcsr (int*) ; 

int
fesetexceptflag(const fexcept_t *flagp, int excepts)
{
	fenv_t env;
	__uint32_t mxcsr;

	__fnstenv(&env);
	env.__status &= ~excepts;
	env.__status |= *flagp & excepts;
	__fldenv(&env);

	if (__HAS_SSE()) {
		__stmxcsr(&mxcsr);
		mxcsr &= ~excepts;
		mxcsr |= *flagp & excepts;
		__ldmxcsr(&mxcsr);
	}

	return (0);
}