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
typedef  int fexcept_t ;
typedef  int /*<<< orphan*/  fenv_t ;

/* Variables and functions */
 int FE_ALL_EXCEPT ; 
 int /*<<< orphan*/  feraiseexcept (int) ; 
 int /*<<< orphan*/  vmrs_fpscr (int) ; 
 int /*<<< orphan*/  vmsr_fpscr (int /*<<< orphan*/  const) ; 

inline int
feupdateenv(const fenv_t *__envp)
{
	fexcept_t __fpsr;

	vmrs_fpscr(__fpsr);
	vmsr_fpscr(*__envp);
	feraiseexcept(__fpsr & FE_ALL_EXCEPT);
	return (0);
}