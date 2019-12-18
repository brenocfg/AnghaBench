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
 int /*<<< orphan*/  APIC_ICR ; 
 int NMI_VECTOR ; 
 unsigned int __prepare_ICR (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __xapic_wait_icr_idle () ; 
 int /*<<< orphan*/  native_apic_mem_write (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  safe_apic_wait_icr_idle () ; 
 scalar_t__ unlikely (int) ; 

void __default_send_IPI_shortcut(unsigned int shortcut, int vector)
{
	/*
	 * Subtle. In the case of the 'never do double writes' workaround
	 * we have to lock out interrupts to be safe.  As we don't care
	 * of the value read we use an atomic rmw access to avoid costly
	 * cli/sti.  Otherwise we use an even cheaper single atomic write
	 * to the APIC.
	 */
	unsigned int cfg;

	/*
	 * Wait for idle.
	 */
	if (unlikely(vector == NMI_VECTOR))
		safe_apic_wait_icr_idle();
	else
		__xapic_wait_icr_idle();

	/*
	 * No need to touch the target chip field. Also the destination
	 * mode is ignored when a shorthand is used.
	 */
	cfg = __prepare_ICR(shortcut, vector, 0);

	/*
	 * Send the IPI. The write to APIC_ICR fires this off.
	 */
	native_apic_mem_write(APIC_ICR, cfg);
}