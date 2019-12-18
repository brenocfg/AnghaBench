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
 int /*<<< orphan*/  pr_warn_once (char*) ; 
 int /*<<< orphan*/  smp_call_function_single (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stop_nmi_watchdog ; 

void watchdog_nmi_disable(unsigned int cpu)
{
	if (atomic_read(&nmi_active) == -1)
		pr_warn_once("NMI watchdog cannot be enabled or disabled\n");
	else
		smp_call_function_single(cpu, stop_nmi_watchdog, NULL, 1);
}