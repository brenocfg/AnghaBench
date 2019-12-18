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
 scalar_t__ MIPS_CPU_IRQ_BASE ; 
 unsigned int ST0_IM ; 
 unsigned int STATUSF_IP2 ; 
 unsigned int STATUSF_IP7 ; 
 int /*<<< orphan*/  adm8668_irq_cascade () ; 
 int /*<<< orphan*/  do_IRQ (scalar_t__) ; 
 unsigned int read_c0_cause () ; 
 unsigned int read_c0_status () ; 
 int /*<<< orphan*/  spurious_interrupt () ; 

void plat_irq_dispatch(void)
{
	unsigned int pending;

	pending = read_c0_cause() & read_c0_status() & ST0_IM;

	/* timer interrupt, that we renumbered */
	if (pending & STATUSF_IP7)
		do_IRQ(MIPS_CPU_IRQ_BASE + 7);
	else if (pending & STATUSF_IP2)
		adm8668_irq_cascade();
	else
		spurious_interrupt();
}