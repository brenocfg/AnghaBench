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
struct clk {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 scalar_t__ RASPBERRYPI_FREQ_INTERVAL ; 
 int /*<<< orphan*/  ULONG_MAX ; 
 struct clk* clk_get (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_put (struct clk*) ; 
 int /*<<< orphan*/  clk_round_rate (struct clk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpufreq_dt ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int dev_pm_opp_add (struct device*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_pm_opp_remove_all_dynamic (struct device*) ; 
 struct device* get_cpu_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_register_simple (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 unsigned long roundup (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int raspberrypi_cpufreq_probe(struct platform_device *pdev)
{
	struct device *cpu_dev;
	unsigned long min, max;
	unsigned long rate;
	struct clk *clk;
	int ret;

	cpu_dev = get_cpu_device(0);
	if (!cpu_dev) {
		pr_err("Cannot get CPU for cpufreq driver\n");
		return -ENODEV;
	}

	clk = clk_get(cpu_dev, NULL);
	if (IS_ERR(clk)) {
		dev_err(cpu_dev, "Cannot get clock for CPU0\n");
		return PTR_ERR(clk);
	}

	/*
	 * The max and min frequencies are configurable in the Raspberry Pi
	 * firmware, so we query them at runtime.
	 */
	min = roundup(clk_round_rate(clk, 0), RASPBERRYPI_FREQ_INTERVAL);
	max = roundup(clk_round_rate(clk, ULONG_MAX), RASPBERRYPI_FREQ_INTERVAL);
	clk_put(clk);

	for (rate = min; rate <= max; rate += RASPBERRYPI_FREQ_INTERVAL) {
		ret = dev_pm_opp_add(cpu_dev, rate, 0);
		if (ret)
			goto remove_opp;
	}

	cpufreq_dt = platform_device_register_simple("cpufreq-dt", -1, NULL, 0);
	ret = PTR_ERR_OR_ZERO(cpufreq_dt);
	if (ret) {
		dev_err(cpu_dev, "Failed to create platform device, %d\n", ret);
		goto remove_opp;
	}

	return 0;

remove_opp:
	dev_pm_opp_remove_all_dynamic(cpu_dev);

	return ret;
}