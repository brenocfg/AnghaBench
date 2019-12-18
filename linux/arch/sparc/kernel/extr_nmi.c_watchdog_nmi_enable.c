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
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nmi_active ; 
 int /*<<< orphan*/  nmi_init_done ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  smp_call_function_single (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  start_nmi_watchdog ; 

int watchdog_nmi_enable(unsigned int cpu)
{
	if (atomic_read(&nmi_active) == -1) {
		pr_warn("NMI watchdog cannot be enabled or disabled\n");
		return -1;
	}

	/*
	 * watchdog thread could start even before nmi_init is called.
	 * Just Return in that case. Let nmi_init finish the init
	 * process first.
	 */
	if (!nmi_init_done)
		return 0;

	smp_call_function_single(cpu, start_nmi_watchdog, NULL, 1);

	return 0;
}