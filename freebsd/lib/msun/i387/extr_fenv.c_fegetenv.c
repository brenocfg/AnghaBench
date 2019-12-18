#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  __control; } ;
typedef  TYPE_1__ fenv_t ;
typedef  int /*<<< orphan*/  __uint32_t ;

/* Variables and functions */
 scalar_t__ __HAS_SSE () ; 
 int /*<<< orphan*/  __fldcw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __fnstenv (TYPE_1__*) ; 
 int /*<<< orphan*/  __set_mxcsr (TYPE_1__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __stmxcsr (int /*<<< orphan*/ *) ; 

int
fegetenv(fenv_t *envp)
{
	__uint32_t mxcsr;

	__fnstenv(envp);
	/*
	 * fnstenv masks all exceptions, so we need to restore
	 * the old control word to avoid this side effect.
	 */
	__fldcw(&envp->__control);
	if (__HAS_SSE()) {
		__stmxcsr(&mxcsr);
		__set_mxcsr(*envp, mxcsr);
	}
	return (0);
}