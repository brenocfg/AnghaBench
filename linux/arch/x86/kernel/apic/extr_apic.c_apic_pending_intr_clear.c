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
union apic_ir {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  apic_check_and_ack (union apic_ir*,union apic_ir*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void apic_pending_intr_clear(void)
{
	union apic_ir irr, isr;
	unsigned int i;

	/* 512 loops are way oversized and give the APIC a chance to obey. */
	for (i = 0; i < 512; i++) {
		if (!apic_check_and_ack(&irr, &isr))
			return;
	}
	/* Dump the IRR/ISR content if that failed */
	pr_warn("APIC: Stale IRR: %256pb ISR: %256pb\n", irr.map, isr.map);
}