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
struct device {int /*<<< orphan*/  of_node; int /*<<< orphan*/  driver; } ;
struct amba_id {int dummy; } ;
struct amba_driver {int (* probe ) (struct amba_device*,struct amba_id const*) ;int /*<<< orphan*/  id_table; } ;
struct amba_device {int dummy; } ;

/* Variables and functions */
 int amba_get_enable_pclk (struct amba_device*) ; 
 struct amba_id* amba_lookup (int /*<<< orphan*/ ,struct amba_device*) ; 
 int /*<<< orphan*/  amba_put_disable_pclk (struct amba_device*) ; 
 int dev_pm_domain_attach (struct device*,int) ; 
 int /*<<< orphan*/  dev_pm_domain_detach (struct device*,int) ; 
 int of_clk_set_defaults (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (struct device*) ; 
 int stub1 (struct amba_device*,struct amba_id const*) ; 
 struct amba_device* to_amba_device (struct device*) ; 
 struct amba_driver* to_amba_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amba_probe(struct device *dev)
{
	struct amba_device *pcdev = to_amba_device(dev);
	struct amba_driver *pcdrv = to_amba_driver(dev->driver);
	const struct amba_id *id = amba_lookup(pcdrv->id_table, pcdev);
	int ret;

	do {
		ret = of_clk_set_defaults(dev->of_node, false);
		if (ret < 0)
			break;

		ret = dev_pm_domain_attach(dev, true);
		if (ret)
			break;

		ret = amba_get_enable_pclk(pcdev);
		if (ret) {
			dev_pm_domain_detach(dev, true);
			break;
		}

		pm_runtime_get_noresume(dev);
		pm_runtime_set_active(dev);
		pm_runtime_enable(dev);

		ret = pcdrv->probe(pcdev, id);
		if (ret == 0)
			break;

		pm_runtime_disable(dev);
		pm_runtime_set_suspended(dev);
		pm_runtime_put_noidle(dev);

		amba_put_disable_pclk(pcdev);
		dev_pm_domain_detach(dev, true);
	} while (0);

	return ret;
}