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
 int /*<<< orphan*/  vmrs_fpscr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmsr_fpscr (int /*<<< orphan*/ ) ; 

inline int
feholdexcept(fenv_t *__envp)
{
	fenv_t __env;

	vmrs_fpscr(__env);
	*__envp = __env;
	__env &= ~(FE_ALL_EXCEPT);
	vmsr_fpscr(__env);
	return (0);
}