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
struct perf_event_attr {scalar_t__ exclude_user; scalar_t__ exclude_kernel; scalar_t__ exclude_host; int /*<<< orphan*/  exclude_hv; scalar_t__ exclude_guest; scalar_t__ exclude_idle; } ;
struct hw_perf_event {unsigned long config_base; } ;

/* Variables and functions */
 unsigned long ARMV8_PMU_EXCLUDE_EL0 ; 
 unsigned long ARMV8_PMU_EXCLUDE_EL1 ; 
 unsigned long ARMV8_PMU_INCLUDE_EL2 ; 
 int EPERM ; 
 scalar_t__ is_kernel_in_hyp_mode () ; 

__attribute__((used)) static int armv8pmu_set_event_filter(struct hw_perf_event *event,
				     struct perf_event_attr *attr)
{
	unsigned long config_base = 0;

	if (attr->exclude_idle)
		return -EPERM;

	/*
	 * If we're running in hyp mode, then we *are* the hypervisor.
	 * Therefore we ignore exclude_hv in this configuration, since
	 * there's no hypervisor to sample anyway. This is consistent
	 * with other architectures (x86 and Power).
	 */
	if (is_kernel_in_hyp_mode()) {
		if (!attr->exclude_kernel && !attr->exclude_host)
			config_base |= ARMV8_PMU_INCLUDE_EL2;
		if (attr->exclude_guest)
			config_base |= ARMV8_PMU_EXCLUDE_EL1;
		if (attr->exclude_host)
			config_base |= ARMV8_PMU_EXCLUDE_EL0;
	} else {
		if (!attr->exclude_hv && !attr->exclude_host)
			config_base |= ARMV8_PMU_INCLUDE_EL2;
	}

	/*
	 * Filter out !VHE kernels and guest kernels
	 */
	if (attr->exclude_kernel)
		config_base |= ARMV8_PMU_EXCLUDE_EL1;

	if (attr->exclude_user)
		config_base |= ARMV8_PMU_EXCLUDE_EL0;

	/*
	 * Install the filter into config_base as this is used to
	 * construct the event type.
	 */
	event->config_base = config_base;

	return 0;
}