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
typedef  int u_short ;

/* Variables and functions */
 int /*<<< orphan*/  fnclex () ; 
 int /*<<< orphan*/  fnstsw (int*) ; 

__attribute__((used)) static void
fpu_clean_state(void)
{
	static float dummy_variable = 0.0;
	u_short status;

	/*
	 * Clear the ES bit in the x87 status word if it is currently
	 * set, in order to avoid causing a fault in the upcoming load.
	 */
	fnstsw(&status);
	if (status & 0x80)
		fnclex();

	/*
	 * Load the dummy variable into the x87 stack.  This mangles
	 * the x87 stack, but we don't care since we're about to call
	 * fxrstor() anyway.
	 */
	__asm __volatile("ffree %%st(7); flds %0" : : "m" (dummy_variable));
}