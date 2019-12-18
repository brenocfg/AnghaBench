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
 int CAUSEB_IP2 ; 
 int CAUSEF_IP7 ; 
 int JMR3927_IRQ_IOCINT ; 
 scalar_t__ JMR3927_IRQ_IRC ; 
 int jmr3927_ioc_irqroute () ; 

__attribute__((used)) static int jmr3927_irq_dispatch(int pending)
{
	int irq;

	if ((pending & CAUSEF_IP7) == 0)
		return -1;
	irq = (pending >> CAUSEB_IP2) & 0x0f;
	irq += JMR3927_IRQ_IRC;
	if (irq == JMR3927_IRQ_IOCINT)
		irq = jmr3927_ioc_irqroute();
	return irq;
}