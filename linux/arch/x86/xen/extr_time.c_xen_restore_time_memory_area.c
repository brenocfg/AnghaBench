#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * v; } ;
struct vcpu_register_time_memory_area {TYPE_1__ addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  pvti; } ;

/* Variables and functions */
 int HYPERVISOR_vcpu_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vcpu_register_time_memory_area*) ; 
 int /*<<< orphan*/  VCPUOP_register_vcpu_time_memory_area ; 
 int /*<<< orphan*/  pr_notice (char*,int) ; 
 int /*<<< orphan*/  pvclock_resume () ; 
 TYPE_2__* xen_clock ; 
 scalar_t__ xen_clock_value_saved ; 
 scalar_t__ xen_clocksource_read () ; 
 scalar_t__ xen_sched_clock_offset ; 

void xen_restore_time_memory_area(void)
{
	struct vcpu_register_time_memory_area t;
	int ret;

	if (!xen_clock)
		goto out;

	t.addr.v = &xen_clock->pvti;

	ret = HYPERVISOR_vcpu_op(VCPUOP_register_vcpu_time_memory_area, 0, &t);

	/*
	 * We don't disable VCLOCK_PVCLOCK entirely if it fails to register the
	 * secondary time info with Xen or if we migrated to a host without the
	 * necessary flags. On both of these cases what happens is either
	 * process seeing a zeroed out pvti or seeing no PVCLOCK_TSC_STABLE_BIT
	 * bit set. Userspace checks the latter and if 0, it discards the data
	 * in pvti and fallbacks to a system call for a reliable timestamp.
	 */
	if (ret != 0)
		pr_notice("Cannot restore secondary vcpu_time_info (err %d)",
			  ret);

out:
	/* Need pvclock_resume() before using xen_clocksource_read(). */
	pvclock_resume();
	xen_sched_clock_offset = xen_clocksource_read() - xen_clock_value_saved;
}