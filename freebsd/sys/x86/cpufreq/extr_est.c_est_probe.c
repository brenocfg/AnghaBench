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
typedef  int uint64_t ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int CPUFREQ_DRV_TYPE (scalar_t__,int*) ; 
 int CPUFREQ_FLAG_INFO_ONLY ; 
 int ENXIO ; 
 int /*<<< orphan*/  MSR_MISC_ENABLE ; 
 int MSR_SS_ENABLE ; 
 scalar_t__ bootverbose ; 
 scalar_t__ device_find_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_get_parent (scalar_t__) ; 
 scalar_t__ device_is_attached (scalar_t__) ; 
 int /*<<< orphan*/  device_printf (scalar_t__,char*) ; 
 int /*<<< orphan*/  device_set_desc (scalar_t__,char*) ; 
 int rdmsr (int /*<<< orphan*/ ) ; 
 scalar_t__ resource_disabled (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
est_probe(device_t dev)
{
	device_t perf_dev;
	uint64_t msr;
	int error, type;

	if (resource_disabled("est", 0))
		return (ENXIO);

	/*
	 * If the ACPI perf driver has attached and is not just offering
	 * info, let it manage things.
	 */
	perf_dev = device_find_child(device_get_parent(dev), "acpi_perf", -1);
	if (perf_dev && device_is_attached(perf_dev)) {
		error = CPUFREQ_DRV_TYPE(perf_dev, &type);
		if (error == 0 && (type & CPUFREQ_FLAG_INFO_ONLY) == 0)
			return (ENXIO);
	}

	/* Attempt to enable SpeedStep if not currently enabled. */
	msr = rdmsr(MSR_MISC_ENABLE);
	if ((msr & MSR_SS_ENABLE) == 0) {
		wrmsr(MSR_MISC_ENABLE, msr | MSR_SS_ENABLE);
		if (bootverbose)
			device_printf(dev, "enabling SpeedStep\n");

		/* Check if the enable failed. */
		msr = rdmsr(MSR_MISC_ENABLE);
		if ((msr & MSR_SS_ENABLE) == 0) {
			device_printf(dev, "failed to enable SpeedStep\n");
			return (ENXIO);
		}
	}

	device_set_desc(dev, "Enhanced SpeedStep Frequency Control");
	return (0);
}