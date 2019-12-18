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

/* Variables and functions */
 int /*<<< orphan*/  cpufreq_dt_pdev ; 
 int /*<<< orphan*/  cpufreq_opp_table ; 
 int /*<<< orphan*/  dev_pm_opp_put_supported_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imx_cpufreq_dt_remove(struct platform_device *pdev)
{
	platform_device_unregister(cpufreq_dt_pdev);
	dev_pm_opp_put_supported_hw(cpufreq_opp_table);

	return 0;
}