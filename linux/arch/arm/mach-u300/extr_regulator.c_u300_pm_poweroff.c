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
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 scalar_t__ main_power_15 ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  regulator_disable (scalar_t__) ; 
 int /*<<< orphan*/  sigfillset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void u300_pm_poweroff(void)
{
	sigset_t old, all;

	sigfillset(&all);
	if (!sigprocmask(SIG_BLOCK, &all, &old)) {
		/* Disable LDO D to shut down the system */
		if (main_power_15)
			regulator_disable(main_power_15);
		else
			pr_err("regulator not available to shut down system\n");
		(void) sigprocmask(SIG_SETMASK, &old, NULL);
	}
	return;
}