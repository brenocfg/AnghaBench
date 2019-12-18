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
typedef  int fenv_t ;

/* Variables and functions */
 int FE_ALL_EXCEPT ; 
 int _ENABLE_MASK ; 
 int /*<<< orphan*/  __ldxfsr (int) ; 
 int /*<<< orphan*/  __stxfsr (int*) ; 

inline int
feholdexcept(fenv_t *__envp)
{
	fenv_t __r;

	__stxfsr(&__r);
	*__envp = __r;
	__r &= ~(FE_ALL_EXCEPT | _ENABLE_MASK);
	__ldxfsr(__r);
	return (0);
}