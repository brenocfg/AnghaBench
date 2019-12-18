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
struct private_data {int /*<<< orphan*/  opp_table; scalar_t__ reg_name; scalar_t__ have_static_opps; int /*<<< orphan*/  cpu_dev; } ;
struct cpufreq_policy {int /*<<< orphan*/  clk; int /*<<< orphan*/  related_cpus; int /*<<< orphan*/  freq_table; struct private_data* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_pm_opp_free_cpufreq_table (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_pm_opp_of_cpumask_remove_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_pm_opp_put_regulators (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct private_data*) ; 

__attribute__((used)) static int cpufreq_exit(struct cpufreq_policy *policy)
{
	struct private_data *priv = policy->driver_data;

	dev_pm_opp_free_cpufreq_table(priv->cpu_dev, &policy->freq_table);
	if (priv->have_static_opps)
		dev_pm_opp_of_cpumask_remove_table(policy->related_cpus);
	if (priv->reg_name)
		dev_pm_opp_put_regulators(priv->opp_table);

	clk_put(policy->clk);
	kfree(priv);

	return 0;
}