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
typedef  int u_int ;

/* Variables and functions */
 scalar_t__ LAPIC_IRR0 ; 
 int lapic_read32 (scalar_t__) ; 

__attribute__((used)) static int
native_lapic_intr_pending(u_int vector)
{
	uint32_t irr;

	/*
	 * The IRR registers are an array of registers each of which
	 * only describes 32 interrupts in the low 32 bits.  Thus, we
	 * divide the vector by 32 to get the register index.
	 * Finally, we modulus the vector by 32 to determine the
	 * individual bit to test.
	 */
	irr = lapic_read32(LAPIC_IRR0 + vector / 32);
	return (irr & 1 << (vector % 32));
}