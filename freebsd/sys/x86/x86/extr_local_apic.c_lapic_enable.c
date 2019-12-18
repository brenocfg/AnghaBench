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
typedef  int uint32_t ;

/* Variables and functions */
 int APIC_SPURIOUS_INT ; 
 int APIC_SVR_EOI_SUPPRESSION ; 
 int APIC_SVR_FEN ; 
 int APIC_SVR_FOCUS ; 
 int APIC_SVR_SWEN ; 
 int APIC_SVR_VECTOR ; 
 int /*<<< orphan*/  LAPIC_SVR ; 
 scalar_t__ lapic_eoi_suppression ; 
 int lapic_read32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lapic_write32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
lapic_enable(void)
{
	uint32_t value;

	/* Program the spurious vector to enable the local APIC. */
	value = lapic_read32(LAPIC_SVR);
	value &= ~(APIC_SVR_VECTOR | APIC_SVR_FOCUS);
	value |= APIC_SVR_FEN | APIC_SVR_SWEN | APIC_SPURIOUS_INT;
	if (lapic_eoi_suppression)
		value |= APIC_SVR_EOI_SUPPRESSION;
	lapic_write32(LAPIC_SVR, value);
}