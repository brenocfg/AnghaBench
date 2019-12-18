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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ APIC_LVTPC ; 
 int /*<<< orphan*/  WARN (int,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pmu_apic_update (scalar_t__) ; 

__attribute__((used)) static void xen_apic_write(u32 reg, u32 val)
{
	if (reg == APIC_LVTPC) {
		(void)pmu_apic_update(reg);
		return;
	}

	/* Warn to see if there's any stray references */
	WARN(1,"register: %x, value: %x\n", reg, val);
}