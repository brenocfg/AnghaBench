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

/* Variables and functions */
 int /*<<< orphan*/  BLANK () ; 
 int /*<<< orphan*/  OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_REG_CWP ; 
 int /*<<< orphan*/  SC_REG_FP ; 
 int /*<<< orphan*/  SC_REG_G4 ; 
 int /*<<< orphan*/  SC_REG_G5 ; 
 int /*<<< orphan*/  SC_REG_G6 ; 
 int /*<<< orphan*/  SC_REG_PSTATE ; 
 int /*<<< orphan*/  SC_REG_TICK ; 
 int /*<<< orphan*/  SC_REG_WSTATE ; 
 int /*<<< orphan*/  cwp ; 
 int /*<<< orphan*/  fp ; 
 int /*<<< orphan*/  g4 ; 
 int /*<<< orphan*/  g5 ; 
 int /*<<< orphan*/  g6 ; 
 int /*<<< orphan*/  pstate ; 
 int /*<<< orphan*/  saved_context ; 
 int /*<<< orphan*/  tick ; 
 int /*<<< orphan*/  wstate ; 

int sparc64_foo(void)
{
#ifdef CONFIG_HIBERNATION
	BLANK();
	OFFSET(SC_REG_FP, saved_context, fp);
	OFFSET(SC_REG_CWP, saved_context, cwp);
	OFFSET(SC_REG_WSTATE, saved_context, wstate);

	OFFSET(SC_REG_TICK, saved_context, tick);
	OFFSET(SC_REG_PSTATE, saved_context, pstate);

	OFFSET(SC_REG_G4, saved_context, g4);
	OFFSET(SC_REG_G5, saved_context, g5);
	OFFSET(SC_REG_G6, saved_context, g6);
#endif
	return 0;
}