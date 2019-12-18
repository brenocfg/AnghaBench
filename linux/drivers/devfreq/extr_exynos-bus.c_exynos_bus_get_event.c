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
struct exynos_bus {int edev_count; int /*<<< orphan*/ * edev; } ;
struct devfreq_event_data {unsigned long load_count; unsigned long total_count; } ;

/* Variables and functions */
 int devfreq_event_get_event (int /*<<< orphan*/ ,struct devfreq_event_data*) ; 

__attribute__((used)) static int exynos_bus_get_event(struct exynos_bus *bus,
				struct devfreq_event_data *edata)
{
	struct devfreq_event_data event_data;
	unsigned long load_count = 0, total_count = 0;
	int i, ret = 0;

	for (i = 0; i < bus->edev_count; i++) {
		if (!bus->edev[i])
			continue;

		ret = devfreq_event_get_event(bus->edev[i], &event_data);
		if (ret < 0)
			return ret;

		if (i == 0 || event_data.load_count > load_count) {
			load_count = event_data.load_count;
			total_count = event_data.total_count;
		}
	}

	edata->load_count = load_count;
	edata->total_count = total_count;

	return ret;
}