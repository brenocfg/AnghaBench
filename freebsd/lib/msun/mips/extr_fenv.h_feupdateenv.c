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
typedef  int /*<<< orphan*/  fenv_t ;

/* Variables and functions */
 int /*<<< orphan*/  __cfc1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  feraiseexcept (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fesetenv (int /*<<< orphan*/  const*) ; 

inline int
feupdateenv(const fenv_t *__envp)
{
	fexcept_t fcsr;

	__cfc1(fcsr);
	fesetenv(__envp);
	feraiseexcept(fcsr);

	return (0);
}