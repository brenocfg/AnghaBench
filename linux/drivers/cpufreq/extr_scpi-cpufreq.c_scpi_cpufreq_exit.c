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
struct scpi_data {int /*<<< orphan*/  cpu_dev; int /*<<< orphan*/  clk; } ;
struct cpufreq_policy {int /*<<< orphan*/  freq_table; struct scpi_data* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_pm_opp_free_cpufreq_table (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_pm_opp_remove_all_dynamic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct scpi_data*) ; 

__attribute__((used)) static int scpi_cpufreq_exit(struct cpufreq_policy *policy)
{
	struct scpi_data *priv = policy->driver_data;

	clk_put(priv->clk);
	dev_pm_opp_free_cpufreq_table(priv->cpu_dev, &policy->freq_table);
	dev_pm_opp_remove_all_dynamic(priv->cpu_dev);
	kfree(priv);

	return 0;
}