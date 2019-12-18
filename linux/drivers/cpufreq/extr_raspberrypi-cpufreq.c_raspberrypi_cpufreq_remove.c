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
struct platform_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpufreq_dt ; 
 int /*<<< orphan*/  dev_pm_opp_remove_all_dynamic (struct device*) ; 
 struct device* get_cpu_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int raspberrypi_cpufreq_remove(struct platform_device *pdev)
{
	struct device *cpu_dev;

	cpu_dev = get_cpu_device(0);
	if (cpu_dev)
		dev_pm_opp_remove_all_dynamic(cpu_dev);

	platform_device_unregister(cpufreq_dt);

	return 0;
}