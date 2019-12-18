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
struct generic_pm_domain {int /*<<< orphan*/  power_on; int /*<<< orphan*/  power_off; int /*<<< orphan*/  name; } ;
struct scpi_pm_domain {int domain; struct generic_pm_domain genpd; int /*<<< orphan*/  name; struct scpi_ops* ops; } ;
struct scpi_ops {int /*<<< orphan*/  device_get_power_state; int /*<<< orphan*/  device_set_power_state; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct genpd_onecell_data {int num_domains; struct generic_pm_domain** domains; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 struct genpd_onecell_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct scpi_ops* get_scpi_ops () ; 
 int /*<<< orphan*/  of_genpd_add_provider_onecell (struct device_node*,struct genpd_onecell_data*) ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  pm_genpd_init (struct generic_pm_domain*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  scpi_pd_power_off ; 
 int /*<<< orphan*/  scpi_pd_power_on ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,struct device_node*,int) ; 

__attribute__((used)) static int scpi_pm_domain_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct scpi_pm_domain *scpi_pd;
	struct genpd_onecell_data *scpi_pd_data;
	struct generic_pm_domain **domains;
	struct scpi_ops *scpi_ops;
	int ret, num_domains, i;

	scpi_ops = get_scpi_ops();
	if (!scpi_ops)
		return -EPROBE_DEFER;

	if (!np) {
		dev_err(dev, "device tree node not found\n");
		return -ENODEV;
	}

	if (!scpi_ops->device_set_power_state ||
	    !scpi_ops->device_get_power_state) {
		dev_err(dev, "power domains not supported in the firmware\n");
		return -ENODEV;
	}

	ret = of_property_read_u32(np, "num-domains", &num_domains);
	if (ret) {
		dev_err(dev, "number of domains not found\n");
		return -EINVAL;
	}

	scpi_pd = devm_kcalloc(dev, num_domains, sizeof(*scpi_pd), GFP_KERNEL);
	if (!scpi_pd)
		return -ENOMEM;

	scpi_pd_data = devm_kzalloc(dev, sizeof(*scpi_pd_data), GFP_KERNEL);
	if (!scpi_pd_data)
		return -ENOMEM;

	domains = devm_kcalloc(dev, num_domains, sizeof(*domains), GFP_KERNEL);
	if (!domains)
		return -ENOMEM;

	for (i = 0; i < num_domains; i++, scpi_pd++) {
		domains[i] = &scpi_pd->genpd;

		scpi_pd->domain = i;
		scpi_pd->ops = scpi_ops;
		sprintf(scpi_pd->name, "%pOFn.%d", np, i);
		scpi_pd->genpd.name = scpi_pd->name;
		scpi_pd->genpd.power_off = scpi_pd_power_off;
		scpi_pd->genpd.power_on = scpi_pd_power_on;

		/*
		 * Treat all power domains as off at boot.
		 *
		 * The SCP firmware itself may have switched on some domains,
		 * but for reference counting purpose, keep it this way.
		 */
		pm_genpd_init(&scpi_pd->genpd, NULL, true);
	}

	scpi_pd_data->domains = domains;
	scpi_pd_data->num_domains = num_domains;

	of_genpd_add_provider_onecell(np, scpi_pd_data);

	return 0;
}