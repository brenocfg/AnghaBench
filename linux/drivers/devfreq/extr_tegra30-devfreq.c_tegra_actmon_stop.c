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
 int /*<<< orphan*/  ACTMON_DEV_CTRL ; 
 int /*<<< orphan*/  ACTMON_DEV_INTR_STATUS ; 
 int ACTMON_INTR_STATUS_CLEAR ; 
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  actmon_write_barrier (struct tegra_devfreq*) ; 
 int /*<<< orphan*/  device_writel (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_actmon_stop(struct tegra_devfreq *tegra)
{
	unsigned int i;

	disable_irq(tegra->irq);

	for (i = 0; i < ARRAY_SIZE(tegra->devices); i++) {
		device_writel(&tegra->devices[i], 0x00000000, ACTMON_DEV_CTRL);
		device_writel(&tegra->devices[i], ACTMON_INTR_STATUS_CLEAR,
			      ACTMON_DEV_INTR_STATUS);
	}

	actmon_write_barrier(tegra);

	enable_irq(tegra->irq);
}