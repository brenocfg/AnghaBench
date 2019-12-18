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
struct device {int dummy; } ;
struct ahci_host_priv {int nports; scalar_t__* target_pwrs; scalar_t__* clks; scalar_t__ got_runtime_pm; } ;

/* Variables and functions */
 int AHCI_MAX_CLKS ; 
 int /*<<< orphan*/  clk_put (scalar_t__) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 int /*<<< orphan*/  regulator_put (scalar_t__) ; 

__attribute__((used)) static void ahci_platform_put_resources(struct device *dev, void *res)
{
	struct ahci_host_priv *hpriv = res;
	int c;

	if (hpriv->got_runtime_pm) {
		pm_runtime_put_sync(dev);
		pm_runtime_disable(dev);
	}

	for (c = 0; c < AHCI_MAX_CLKS && hpriv->clks[c]; c++)
		clk_put(hpriv->clks[c]);
	/*
	 * The regulators are tied to child node device and not to the
	 * SATA device itself. So we can't use devm for automatically
	 * releasing them. We have to do it manually here.
	 */
	for (c = 0; c < hpriv->nports; c++)
		if (hpriv->target_pwrs && hpriv->target_pwrs[c])
			regulator_put(hpriv->target_pwrs[c]);

	kfree(hpriv->target_pwrs);
}