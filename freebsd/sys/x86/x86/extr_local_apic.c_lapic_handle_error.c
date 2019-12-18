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
 int /*<<< orphan*/  LAPIC_ESR ; 
 int PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuid ; 
 int /*<<< orphan*/  lapic_eoi () ; 
 int lapic_read32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lapic_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

void
lapic_handle_error(void)
{
	uint32_t esr;

	/*
	 * Read the contents of the error status register.  Write to
	 * the register first before reading from it to force the APIC
	 * to update its value to indicate any errors that have
	 * occurred since the previous write to the register.
	 */
	lapic_write32(LAPIC_ESR, 0);
	esr = lapic_read32(LAPIC_ESR);

	printf("CPU%d: local APIC error 0x%x\n", PCPU_GET(cpuid), esr);
	lapic_eoi();
}