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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_LVT_M ; 
 int /*<<< orphan*/  LAPIC_LVT_PCINT ; 
 int /*<<< orphan*/  lapic_read32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lapic_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
native_lapic_reenable_pmc(void)
{
#ifdef HWPMC_HOOKS
	uint32_t value;

	value = lapic_read32(LAPIC_LVT_PCINT);
	value &= ~APIC_LVT_M;
	lapic_write32(LAPIC_LVT_PCINT, value);
#endif
}