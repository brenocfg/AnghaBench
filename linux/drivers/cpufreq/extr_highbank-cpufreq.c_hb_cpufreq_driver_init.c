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
struct platform_device_info {char* name; } ;
struct device_node {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 struct clk* clk_get (struct device*,int /*<<< orphan*/ *) ; 
 int clk_notifier_register (struct clk*,int /*<<< orphan*/ *) ; 
 struct device* get_cpu_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_cpufreq_clk_nb ; 
 int /*<<< orphan*/  of_machine_is_compatible (char*) ; 
 struct device_node* of_node_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  platform_device_register_full (struct platform_device_info*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static int hb_cpufreq_driver_init(void)
{
	struct platform_device_info devinfo = { .name = "cpufreq-dt", };
	struct device *cpu_dev;
	struct clk *cpu_clk;
	struct device_node *np;
	int ret;

	if ((!of_machine_is_compatible("calxeda,highbank")) &&
		(!of_machine_is_compatible("calxeda,ecx-2000")))
		return -ENODEV;

	cpu_dev = get_cpu_device(0);
	if (!cpu_dev) {
		pr_err("failed to get highbank cpufreq device\n");
		return -ENODEV;
	}

	np = of_node_get(cpu_dev->of_node);
	if (!np) {
		pr_err("failed to find highbank cpufreq node\n");
		return -ENOENT;
	}

	cpu_clk = clk_get(cpu_dev, NULL);
	if (IS_ERR(cpu_clk)) {
		ret = PTR_ERR(cpu_clk);
		pr_err("failed to get cpu0 clock: %d\n", ret);
		goto out_put_node;
	}

	ret = clk_notifier_register(cpu_clk, &hb_cpufreq_clk_nb);
	if (ret) {
		pr_err("failed to register clk notifier: %d\n", ret);
		goto out_put_node;
	}

	/* Instantiate cpufreq-dt */
	platform_device_register_full(&devinfo);

out_put_node:
	of_node_put(np);
	return ret;
}