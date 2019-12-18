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
 int /*<<< orphan*/  nlm_cpumask ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  wait_for_cpus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xlp_boot_core0_siblings () ; 
 int /*<<< orphan*/  xlp_enable_secondary_cores (int /*<<< orphan*/ *) ; 

void xlp_wakeup_secondary_cpus(void)
{
	/*
	 * In case of u-boot, the secondaries are in reset
	 * first wakeup core 0 threads
	 */
	xlp_boot_core0_siblings();
	if (!wait_for_cpus(0, 0))
		pr_err("Node 0 : timeout core 0\n");

	/* now get other cores out of reset */
	xlp_enable_secondary_cores(&nlm_cpumask);
}