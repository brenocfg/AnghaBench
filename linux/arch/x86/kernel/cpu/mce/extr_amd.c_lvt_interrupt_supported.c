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
typedef  int u32 ;

/* Variables and functions */
 int BIT (int) ; 

__attribute__((used)) static bool lvt_interrupt_supported(unsigned int bank, u32 msr_high_bits)
{
	/*
	 * bank 4 supports APIC LVT interrupts implicitly since forever.
	 */
	if (bank == 4)
		return true;

	/*
	 * IntP: interrupt present; if this bit is set, the thresholding
	 * bank can generate APIC LVT interrupts
	 */
	return msr_high_bits & BIT(28);
}