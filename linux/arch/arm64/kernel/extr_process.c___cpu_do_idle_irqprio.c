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
 unsigned long GIC_PRIO_IRQON ; 
 unsigned long GIC_PRIO_PSR_I_SET ; 
 unsigned long PSR_I_BIT ; 
 int /*<<< orphan*/  __cpu_do_idle () ; 
 int /*<<< orphan*/  daif ; 
 unsigned long gic_read_pmr () ; 
 int /*<<< orphan*/  gic_write_pmr (unsigned long) ; 
 unsigned long read_sysreg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_sysreg (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __cpu_do_idle_irqprio(void)
{
	unsigned long pmr;
	unsigned long daif_bits;

	daif_bits = read_sysreg(daif);
	write_sysreg(daif_bits | PSR_I_BIT, daif);

	/*
	 * Unmask PMR before going idle to make sure interrupts can
	 * be raised.
	 */
	pmr = gic_read_pmr();
	gic_write_pmr(GIC_PRIO_IRQON | GIC_PRIO_PSR_I_SET);

	__cpu_do_idle();

	gic_write_pmr(pmr);
	write_sysreg(daif_bits, daif);
}