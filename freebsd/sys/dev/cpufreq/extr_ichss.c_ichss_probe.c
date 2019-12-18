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
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int CPUFREQ_DRV_TYPE (scalar_t__,int*) ; 
 int CPUFREQ_FLAG_INFO_ONLY ; 
 int ENXIO ; 
 scalar_t__ device_find_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_get_parent (scalar_t__) ; 
 scalar_t__ device_is_attached (scalar_t__) ; 
 int /*<<< orphan*/  device_set_desc (scalar_t__,char*) ; 

__attribute__((used)) static int
ichss_probe(device_t dev)
{
	device_t est_dev, perf_dev;
	int error, type;

	/*
	 * If the ACPI perf driver has attached and is not just offering
	 * info, let it manage things.  Also, if Enhanced SpeedStep is
	 * available, don't attach.
	 */
	perf_dev = device_find_child(device_get_parent(dev), "acpi_perf", -1);
	if (perf_dev && device_is_attached(perf_dev)) {
		error = CPUFREQ_DRV_TYPE(perf_dev, &type);
		if (error == 0 && (type & CPUFREQ_FLAG_INFO_ONLY) == 0)
			return (ENXIO);
	}
	est_dev = device_find_child(device_get_parent(dev), "est", -1);
	if (est_dev && device_is_attached(est_dev))
		return (ENXIO);

	device_set_desc(dev, "SpeedStep ICH");
	return (-1000);
}