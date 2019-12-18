#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct exynos_bus {int /*<<< orphan*/ * opp_table; int /*<<< orphan*/  clk; struct devfreq* devfreq; struct device* dev; int /*<<< orphan*/  lock; } ;
struct device_node {int dummy; } ;
struct devfreq_simple_ondemand_data {int upthreshold; int downdifferential; struct devfreq* parent; } ;
struct devfreq_passive_data {int upthreshold; int downdifferential; struct devfreq* parent; } ;
struct devfreq_dev_profile {int polling_ms; int /*<<< orphan*/  exit; void* target; int /*<<< orphan*/  get_dev_status; } ;
struct devfreq {TYPE_1__* profile; } ;
struct TYPE_2__ {int max_state; int* freq_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVFREQ_GOV_PASSIVE ; 
 int /*<<< orphan*/  DEVFREQ_GOV_SIMPLE_ONDEMAND ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct devfreq*) ; 
 int PTR_ERR (struct devfreq*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_pm_opp_of_remove_table (struct device*) ; 
 int /*<<< orphan*/  dev_pm_opp_put_regulators (int /*<<< orphan*/ *) ; 
 struct devfreq* devfreq_get_devfreq_by_phandle (struct device*,int /*<<< orphan*/ ) ; 
 void* devm_devfreq_add_device (struct device*,struct devfreq_dev_profile*,int /*<<< orphan*/ ,struct devfreq_simple_ondemand_data*) ; 
 int devm_devfreq_register_opp_notifier (struct device*,struct devfreq*) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int exynos_bus_enable_edev (struct exynos_bus*) ; 
 int /*<<< orphan*/  exynos_bus_exit ; 
 int /*<<< orphan*/  exynos_bus_get_dev_status ; 
 int exynos_bus_parent_parse_of (struct device_node*,struct exynos_bus*) ; 
 int exynos_bus_parse_of (struct device_node*,struct exynos_bus*) ; 
 int /*<<< orphan*/  exynos_bus_passive_exit ; 
 int exynos_bus_set_event (struct exynos_bus*) ; 
 void* exynos_bus_target ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct exynos_bus*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,unsigned long,unsigned long) ; 

__attribute__((used)) static int exynos_bus_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node, *node;
	struct devfreq_dev_profile *profile;
	struct devfreq_simple_ondemand_data *ondemand_data;
	struct devfreq_passive_data *passive_data;
	struct devfreq *parent_devfreq;
	struct exynos_bus *bus;
	int ret, max_state;
	unsigned long min_freq, max_freq;
	bool passive = false;

	if (!np) {
		dev_err(dev, "failed to find devicetree node\n");
		return -EINVAL;
	}

	bus = devm_kzalloc(&pdev->dev, sizeof(*bus), GFP_KERNEL);
	if (!bus)
		return -ENOMEM;
	mutex_init(&bus->lock);
	bus->dev = &pdev->dev;
	platform_set_drvdata(pdev, bus);

	profile = devm_kzalloc(dev, sizeof(*profile), GFP_KERNEL);
	if (!profile)
		return -ENOMEM;

	node = of_parse_phandle(dev->of_node, "devfreq", 0);
	if (node) {
		of_node_put(node);
		passive = true;
	} else {
		ret = exynos_bus_parent_parse_of(np, bus);
		if (ret < 0)
			return ret;
	}

	/* Parse the device-tree to get the resource information */
	ret = exynos_bus_parse_of(np, bus);
	if (ret < 0)
		goto err_reg;

	if (passive)
		goto passive;

	/* Initialize the struct profile and governor data for parent device */
	profile->polling_ms = 50;
	profile->target = exynos_bus_target;
	profile->get_dev_status = exynos_bus_get_dev_status;
	profile->exit = exynos_bus_exit;

	ondemand_data = devm_kzalloc(dev, sizeof(*ondemand_data), GFP_KERNEL);
	if (!ondemand_data) {
		ret = -ENOMEM;
		goto err;
	}
	ondemand_data->upthreshold = 40;
	ondemand_data->downdifferential = 5;

	/* Add devfreq device to monitor and handle the exynos bus */
	bus->devfreq = devm_devfreq_add_device(dev, profile,
						DEVFREQ_GOV_SIMPLE_ONDEMAND,
						ondemand_data);
	if (IS_ERR(bus->devfreq)) {
		dev_err(dev, "failed to add devfreq device\n");
		ret = PTR_ERR(bus->devfreq);
		goto err;
	}

	/* Register opp_notifier to catch the change of OPP  */
	ret = devm_devfreq_register_opp_notifier(dev, bus->devfreq);
	if (ret < 0) {
		dev_err(dev, "failed to register opp notifier\n");
		goto err;
	}

	/*
	 * Enable devfreq-event to get raw data which is used to determine
	 * current bus load.
	 */
	ret = exynos_bus_enable_edev(bus);
	if (ret < 0) {
		dev_err(dev, "failed to enable devfreq-event devices\n");
		goto err;
	}

	ret = exynos_bus_set_event(bus);
	if (ret < 0) {
		dev_err(dev, "failed to set event to devfreq-event devices\n");
		goto err;
	}

	goto out;
passive:
	/* Initialize the struct profile and governor data for passive device */
	profile->target = exynos_bus_target;
	profile->exit = exynos_bus_passive_exit;

	/* Get the instance of parent devfreq device */
	parent_devfreq = devfreq_get_devfreq_by_phandle(dev, 0);
	if (IS_ERR(parent_devfreq)) {
		ret = -EPROBE_DEFER;
		goto err;
	}

	passive_data = devm_kzalloc(dev, sizeof(*passive_data), GFP_KERNEL);
	if (!passive_data) {
		ret = -ENOMEM;
		goto err;
	}
	passive_data->parent = parent_devfreq;

	/* Add devfreq device for exynos bus with passive governor */
	bus->devfreq = devm_devfreq_add_device(dev, profile, DEVFREQ_GOV_PASSIVE,
						passive_data);
	if (IS_ERR(bus->devfreq)) {
		dev_err(dev,
			"failed to add devfreq dev with passive governor\n");
		ret = PTR_ERR(bus->devfreq);
		goto err;
	}

out:
	max_state = bus->devfreq->profile->max_state;
	min_freq = (bus->devfreq->profile->freq_table[0] / 1000);
	max_freq = (bus->devfreq->profile->freq_table[max_state - 1] / 1000);
	pr_info("exynos-bus: new bus device registered: %s (%6ld KHz ~ %6ld KHz)\n",
			dev_name(dev), min_freq, max_freq);

	return 0;

err:
	dev_pm_opp_of_remove_table(dev);
	clk_disable_unprepare(bus->clk);
err_reg:
	if (!passive) {
		dev_pm_opp_put_regulators(bus->opp_table);
		bus->opp_table = NULL;
	}

	return ret;
}