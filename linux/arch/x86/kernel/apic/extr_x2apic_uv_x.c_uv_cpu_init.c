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
struct TYPE_2__ {int /*<<< orphan*/  pnode; int /*<<< orphan*/  nr_online_cpus; } ;

/* Variables and functions */
 scalar_t__ UV_NON_UNIQUE_APIC ; 
 scalar_t__ get_uv_system_type () ; 
 int /*<<< orphan*/  set_x2apic_extra_bits (int /*<<< orphan*/ ) ; 
 scalar_t__ smp_processor_id () ; 
 TYPE_1__* uv_hub_info ; 

void uv_cpu_init(void)
{
	/* CPU 0 initialization will be done via uv_system_init. */
	if (smp_processor_id() == 0)
		return;

	uv_hub_info->nr_online_cpus++;

	if (get_uv_system_type() == UV_NON_UNIQUE_APIC)
		set_x2apic_extra_bits(uv_hub_info->pnode);
}