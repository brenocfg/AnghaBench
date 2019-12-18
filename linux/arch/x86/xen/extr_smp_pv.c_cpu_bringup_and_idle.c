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
 int /*<<< orphan*/  CPUHP_AP_ONLINE_IDLE ; 
 int /*<<< orphan*/  boot_init_stack_canary () ; 
 int /*<<< orphan*/  cpu_bringup () ; 
 int /*<<< orphan*/  cpu_startup_entry (int /*<<< orphan*/ ) ; 

void cpu_bringup_and_idle(void)
{
	cpu_bringup();
	boot_init_stack_canary();
	cpu_startup_entry(CPUHP_AP_ONLINE_IDLE);
}