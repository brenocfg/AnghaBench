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
struct tegra_devfreq {int /*<<< orphan*/  irq; int /*<<< orphan*/ * devices; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACTMON_GLB_PERIOD_CTRL ; 
 scalar_t__ ACTMON_SAMPLING_PERIOD ; 
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  actmon_write_barrier (struct tegra_devfreq*) ; 
 int /*<<< orphan*/  actmon_writel (struct tegra_devfreq*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_actmon_configure_device (struct tegra_devfreq*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tegra_actmon_start(struct tegra_devfreq *tegra)
{
	unsigned int i;

	disable_irq(tegra->irq);

	actmon_writel(tegra, ACTMON_SAMPLING_PERIOD - 1,
		      ACTMON_GLB_PERIOD_CTRL);

	for (i = 0; i < ARRAY_SIZE(tegra->devices); i++)
		tegra_actmon_configure_device(tegra, &tegra->devices[i]);

	actmon_write_barrier(tegra);

	enable_irq(tegra->irq);
}