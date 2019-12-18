#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  boost_enabled; } ;

/* Variables and functions */
 TYPE_1__ acpi_cpufreq_driver ; 
 int boost_set_msr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpufreq_boost_online(unsigned int cpu)
{
	/*
	 * On the CPU_UP path we simply keep the boost-disable flag
	 * in sync with the current global state.
	 */
	return boost_set_msr(acpi_cpufreq_driver.boost_enabled);
}