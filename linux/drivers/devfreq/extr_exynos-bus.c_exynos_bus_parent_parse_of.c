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
struct opp_table {int dummy; } ;
struct exynos_bus {int edev_count; struct opp_table* opp_table; int /*<<< orphan*/  ratio; struct opp_table** edev; struct device* dev; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_SATURATION_RATIO ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct opp_table*) ; 
 int PTR_ERR (struct opp_table*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_pm_opp_put_regulators (struct opp_table*) ; 
 struct opp_table* dev_pm_opp_set_regulators (struct device*,char const**,int) ; 
 struct opp_table* devfreq_event_get_edev_by_phandle (struct device*,int) ; 
 int devfreq_event_get_edev_count (struct device*) ; 
 struct opp_table** devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int exynos_bus_parent_parse_of(struct device_node *np,
					struct exynos_bus *bus)
{
	struct device *dev = bus->dev;
	struct opp_table *opp_table;
	const char *vdd = "vdd";
	int i, ret, count, size;

	opp_table = dev_pm_opp_set_regulators(dev, &vdd, 1);
	if (IS_ERR(opp_table)) {
		ret = PTR_ERR(opp_table);
		dev_err(dev, "failed to set regulators %d\n", ret);
		return ret;
	}

	bus->opp_table = opp_table;

	/*
	 * Get the devfreq-event devices to get the current utilization of
	 * buses. This raw data will be used in devfreq ondemand governor.
	 */
	count = devfreq_event_get_edev_count(dev);
	if (count < 0) {
		dev_err(dev, "failed to get the count of devfreq-event dev\n");
		ret = count;
		goto err_regulator;
	}
	bus->edev_count = count;

	size = sizeof(*bus->edev) * count;
	bus->edev = devm_kzalloc(dev, size, GFP_KERNEL);
	if (!bus->edev) {
		ret = -ENOMEM;
		goto err_regulator;
	}

	for (i = 0; i < count; i++) {
		bus->edev[i] = devfreq_event_get_edev_by_phandle(dev, i);
		if (IS_ERR(bus->edev[i])) {
			ret = -EPROBE_DEFER;
			goto err_regulator;
		}
	}

	/*
	 * Optionally, Get the saturation ratio according to Exynos SoC
	 * When measuring the utilization of each AXI bus with devfreq-event
	 * devices, the measured real cycle might be much lower than the
	 * total cycle of bus during sampling rate. In result, the devfreq
	 * simple-ondemand governor might not decide to change the current
	 * frequency due to too utilization (= real cycle/total cycle).
	 * So, this property is used to adjust the utilization when calculating
	 * the busy_time in exynos_bus_get_dev_status().
	 */
	if (of_property_read_u32(np, "exynos,saturation-ratio", &bus->ratio))
		bus->ratio = DEFAULT_SATURATION_RATIO;

	return 0;

err_regulator:
	dev_pm_opp_put_regulators(bus->opp_table);
	bus->opp_table = NULL;

	return ret;
}