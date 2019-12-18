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
 int /*<<< orphan*/  C_SW0 ; 
 int /*<<< orphan*/  __sync () ; 
 int /*<<< orphan*/  bmips_booted_mask ; 
 int /*<<< orphan*/  bmips_smp_movevec ; 
 int /*<<< orphan*/  cpumask_set_cpu (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_c0_cause (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm63xx_fixup_cpu1(void)
{
	/*
	 * The bootloader has set up the CPU1 reset vector at
	 * 0xa000_0200.
	 * This conflicts with the special interrupt vector (IV).
	 * The bootloader has also set up CPU1 to respond to the wrong
	 * IPI interrupt.
	 * Here we will start up CPU1 in the background and ask it to
	 * reconfigure itself then go back to sleep.
	 */
	memcpy((void *)0xa0000200, &bmips_smp_movevec, 0x20);
	__sync();
	set_c0_cause(C_SW0);
	cpumask_set_cpu(1, &bmips_booted_mask);
}