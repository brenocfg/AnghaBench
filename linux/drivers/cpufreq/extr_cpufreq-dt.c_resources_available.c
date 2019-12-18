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
struct regulator {int dummy; } ;
struct device {int dummy; } ;
typedef  struct regulator clk ;

/* Variables and functions */
 int ENODEV ; 
 int EPROBE_DEFER ; 
 int PTR_ERR_OR_ZERO (struct regulator*) ; 
 struct regulator* clk_get (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_put (struct regulator*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 char* find_supply_name (struct device*) ; 
 struct device* get_cpu_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct regulator* regulator_get_optional (struct device*,char const*) ; 
 int /*<<< orphan*/  regulator_put (struct regulator*) ; 

__attribute__((used)) static int resources_available(void)
{
	struct device *cpu_dev;
	struct regulator *cpu_reg;
	struct clk *cpu_clk;
	int ret = 0;
	const char *name;

	cpu_dev = get_cpu_device(0);
	if (!cpu_dev) {
		pr_err("failed to get cpu0 device\n");
		return -ENODEV;
	}

	cpu_clk = clk_get(cpu_dev, NULL);
	ret = PTR_ERR_OR_ZERO(cpu_clk);
	if (ret) {
		/*
		 * If cpu's clk node is present, but clock is not yet
		 * registered, we should try defering probe.
		 */
		if (ret == -EPROBE_DEFER)
			dev_dbg(cpu_dev, "clock not ready, retry\n");
		else
			dev_err(cpu_dev, "failed to get clock: %d\n", ret);

		return ret;
	}

	clk_put(cpu_clk);

	name = find_supply_name(cpu_dev);
	/* Platform doesn't require regulator */
	if (!name)
		return 0;

	cpu_reg = regulator_get_optional(cpu_dev, name);
	ret = PTR_ERR_OR_ZERO(cpu_reg);
	if (ret) {
		/*
		 * If cpu's regulator supply node is present, but regulator is
		 * not yet registered, we should try defering probe.
		 */
		if (ret == -EPROBE_DEFER)
			dev_dbg(cpu_dev, "cpu0 regulator not ready, retry\n");
		else
			dev_dbg(cpu_dev, "no regulator for cpu0: %d\n", ret);

		return ret;
	}

	regulator_put(cpu_reg);
	return 0;
}