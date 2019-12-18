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

void arch_cpu_idle(void)
{
	unsigned long tmp;

	/*
	 * Put local_irq_enable and idle in same execute packet
	 * to make them atomic and avoid race to idle with
	 * interrupts enabled.
	 */
	asm volatile ("   mvc .s2 CSR,%0\n"
		      "   or  .d2 1,%0,%0\n"
		      "   mvc .s2 %0,CSR\n"
		      "|| idle\n"
		      : "=b"(tmp));
}