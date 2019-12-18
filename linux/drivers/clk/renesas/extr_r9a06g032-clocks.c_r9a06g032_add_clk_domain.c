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
struct generic_pm_domain {int flags; int /*<<< orphan*/  detach_dev; int /*<<< orphan*/  attach_dev; int /*<<< orphan*/  name; } ;
struct device_node {int /*<<< orphan*/  name; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GENPD_FLAG_ACTIVE_WAKEUP ; 
 int GENPD_FLAG_ALWAYS_ON ; 
 int GENPD_FLAG_PM_CLK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct generic_pm_domain* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_genpd_add_provider_simple (struct device_node*,struct generic_pm_domain*) ; 
 int /*<<< orphan*/  pm_domain_always_on_gov ; 
 int /*<<< orphan*/  pm_genpd_init (struct generic_pm_domain*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  r9a06g032_attach_dev ; 
 int /*<<< orphan*/  r9a06g032_detach_dev ; 

__attribute__((used)) static int r9a06g032_add_clk_domain(struct device *dev)
{
	struct device_node *np = dev->of_node;
	struct generic_pm_domain *pd;

	pd = devm_kzalloc(dev, sizeof(*pd), GFP_KERNEL);
	if (!pd)
		return -ENOMEM;

	pd->name = np->name;
	pd->flags = GENPD_FLAG_PM_CLK | GENPD_FLAG_ALWAYS_ON |
		    GENPD_FLAG_ACTIVE_WAKEUP;
	pd->attach_dev = r9a06g032_attach_dev;
	pd->detach_dev = r9a06g032_detach_dev;
	pm_genpd_init(pd, &pm_domain_always_on_gov, false);

	of_genpd_add_provider_simple(np, pd);
	return 0;
}