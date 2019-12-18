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
struct TYPE_2__ {int /*<<< orphan*/ * v; } ;
struct vcpu_register_time_memory_area {TYPE_1__ addr; } ;

/* Variables and functions */
 int HYPERVISOR_vcpu_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vcpu_register_time_memory_area*) ; 
 int /*<<< orphan*/  VCPUOP_register_vcpu_time_memory_area ; 
 int /*<<< orphan*/  clear_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_notice (char*,int) ; 
 int /*<<< orphan*/  xen_clock ; 
 scalar_t__ xen_clock_value_saved ; 
 scalar_t__ xen_clocksource_read () ; 
 scalar_t__ xen_sched_clock_offset ; 

void xen_save_time_memory_area(void)
{
	struct vcpu_register_time_memory_area t;
	int ret;

	xen_clock_value_saved = xen_clocksource_read() - xen_sched_clock_offset;

	if (!xen_clock)
		return;

	t.addr.v = NULL;

	ret = HYPERVISOR_vcpu_op(VCPUOP_register_vcpu_time_memory_area, 0, &t);
	if (ret != 0)
		pr_notice("Cannot save secondary vcpu_time_info (err %d)",
			  ret);
	else
		clear_page(xen_clock);
}