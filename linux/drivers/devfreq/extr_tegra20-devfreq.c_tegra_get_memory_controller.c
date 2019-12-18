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
struct tegra_mc {int dummy; } ;
struct platform_device {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  EPROBE_DEFER ; 
 struct tegra_mc* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct device_node* of_find_compatible_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct tegra_mc* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static struct tegra_mc *tegra_get_memory_controller(void)
{
	struct platform_device *pdev;
	struct device_node *np;
	struct tegra_mc *mc;

	np = of_find_compatible_node(NULL, NULL, "nvidia,tegra20-mc-gart");
	if (!np)
		return ERR_PTR(-ENOENT);

	pdev = of_find_device_by_node(np);
	of_node_put(np);
	if (!pdev)
		return ERR_PTR(-ENODEV);

	mc = platform_get_drvdata(pdev);
	if (!mc)
		return ERR_PTR(-EPROBE_DEFER);

	return mc;
}