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

/* Variables and functions */
 int /*<<< orphan*/  APIC_DFR ; 
 unsigned long APIC_DFR_FLAT ; 
 int /*<<< orphan*/  APIC_LDR ; 
 unsigned long APIC_LDR_MASK ; 
 unsigned long SET_APIC_LOGICAL_ID (unsigned long) ; 
 unsigned long apic_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apic_write (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long smp_processor_id () ; 

void flat_init_apic_ldr(void)
{
	unsigned long val;
	unsigned long num, id;

	num = smp_processor_id();
	id = 1UL << num;
	apic_write(APIC_DFR, APIC_DFR_FLAT);
	val = apic_read(APIC_LDR) & ~APIC_LDR_MASK;
	val |= SET_APIC_LOGICAL_ID(id);
	apic_write(APIC_LDR, val);
}