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
 int /*<<< orphan*/  MSR_K6_EPMR ; 
 int POWERNOW_IOPORT ; 
 unsigned long X86_CR0_CD ; 
 int* index_to_register ; 
 unsigned long inl (int) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  outl (unsigned long,int) ; 
 unsigned long read_cr0 () ; 
 int /*<<< orphan*/  wbinvd () ; 
 int /*<<< orphan*/  write_cr0 (unsigned long) ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void powernow_k6_set_cpu_multiplier(unsigned int best_i)
{
	unsigned long outvalue, invalue;
	unsigned long msrval;
	unsigned long cr0;

	/* we now need to transform best_i to the BVC format, see AMD#23446 */

	/*
	 * The processor doesn't respond to inquiry cycles while changing the
	 * frequency, so we must disable cache.
	 */
	local_irq_disable();
	cr0 = read_cr0();
	write_cr0(cr0 | X86_CR0_CD);
	wbinvd();

	outvalue = (1<<12) | (1<<10) | (1<<9) | (index_to_register[best_i]<<5);

	msrval = POWERNOW_IOPORT + 0x1;
	wrmsr(MSR_K6_EPMR, msrval, 0); /* enable the PowerNow port */
	invalue = inl(POWERNOW_IOPORT + 0x8);
	invalue = invalue & 0x1f;
	outvalue = outvalue | invalue;
	outl(outvalue, (POWERNOW_IOPORT + 0x8));
	msrval = POWERNOW_IOPORT + 0x0;
	wrmsr(MSR_K6_EPMR, msrval, 0); /* disable it again */

	write_cr0(cr0);
	local_irq_enable();
}