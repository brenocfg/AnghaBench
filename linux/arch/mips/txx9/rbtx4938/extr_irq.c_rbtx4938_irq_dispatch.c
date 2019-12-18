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
 int MIPS_CPU_IRQ_BASE ; 
 int RBTX4938_IRQ_IOCINT ; 
 int STATUSF_IP0 ; 
 int STATUSF_IP1 ; 
 int STATUSF_IP2 ; 
 int STATUSF_IP7 ; 
 int toshiba_rbtx4938_irq_nested (int) ; 
 int txx9_irq () ; 

__attribute__((used)) static int rbtx4938_irq_dispatch(int pending)
{
	int irq;

	if (pending & STATUSF_IP7)
		irq = MIPS_CPU_IRQ_BASE + 7;
	else if (pending & STATUSF_IP2) {
		irq = txx9_irq();
		if (irq == RBTX4938_IRQ_IOCINT)
			irq = toshiba_rbtx4938_irq_nested(irq);
	} else if (pending & STATUSF_IP1)
		irq = MIPS_CPU_IRQ_BASE + 0;
	else if (pending & STATUSF_IP0)
		irq = MIPS_CPU_IRQ_BASE + 1;
	else
		irq = -1;
	return irq;
}