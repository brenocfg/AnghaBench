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
 int /*<<< orphan*/  APIC_SVR_SWEN ; 
 int /*<<< orphan*/  LAPIC_SVR ; 
 int /*<<< orphan*/  lapic_read32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lapic_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
native_lapic_disable(void)
{
	uint32_t value;

	/* Software disable the local APIC. */
	value = lapic_read32(LAPIC_SVR);
	value &= ~APIC_SVR_SWEN;
	lapic_write32(LAPIC_SVR, value);
}