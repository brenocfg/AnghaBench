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
typedef  scalar_t__ u_int ;
struct TYPE_2__ {scalar_t__ cpu_hyperthread; scalar_t__ cpu_disabled; scalar_t__ cpu_bsp; } ;

/* Variables and functions */
 scalar_t__ MAXCPU ; 
 scalar_t__* cpu_apic_ids ; 
 TYPE_1__* cpu_info ; 
 int /*<<< orphan*/  hyperthreading_intr_allowed ; 
 int /*<<< orphan*/  intr_add_cpu (scalar_t__) ; 

void
set_interrupt_apic_ids(void)
{
	u_int i, apic_id;

	for (i = 0; i < MAXCPU; i++) {
		apic_id = cpu_apic_ids[i];
		if (apic_id == -1)
			continue;
		if (cpu_info[apic_id].cpu_bsp)
			continue;
		if (cpu_info[apic_id].cpu_disabled)
			continue;

		/* Don't let hyperthreads service interrupts. */
		if (cpu_info[apic_id].cpu_hyperthread &&
		    !hyperthreading_intr_allowed)
			continue;

		intr_add_cpu(i);
	}
}