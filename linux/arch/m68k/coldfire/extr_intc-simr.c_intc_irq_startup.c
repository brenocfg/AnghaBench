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
typedef  int u8 ;
struct irq_data {unsigned int irq; } ;

/* Variables and functions */
 unsigned int EINT1 ; 
 unsigned int EINT7 ; 
 scalar_t__ MCFEPORT_EPDDR ; 
 scalar_t__ MCFEPORT_EPIER ; 
 scalar_t__ MCFINTC0_ICR0 ; 
 scalar_t__ MCFINTC1_ICR0 ; 
 scalar_t__ MCFINTC2_ICR0 ; 
 scalar_t__ MCFINT_VECBASE ; 
 int __raw_readb (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writeb (int,scalar_t__) ; 
 int /*<<< orphan*/  intc_irq_unmask (struct irq_data*) ; 
 unsigned int irq2ebit (unsigned int) ; 

__attribute__((used)) static unsigned int intc_irq_startup(struct irq_data *d)
{
	unsigned int irq = d->irq;

	if ((irq >= EINT1) && (irq <= EINT7)) {
		unsigned int ebit = irq2ebit(irq);
		u8 v;

#if defined(MCFEPORT_EPDDR)
		/* Set EPORT line as input */
		v = __raw_readb(MCFEPORT_EPDDR);
		__raw_writeb(v & ~(0x1 << ebit), MCFEPORT_EPDDR);
#endif

		/* Set EPORT line as interrupt source */
		v = __raw_readb(MCFEPORT_EPIER);
		__raw_writeb(v | (0x1 << ebit), MCFEPORT_EPIER);
	}

	irq -= MCFINT_VECBASE;
	if (MCFINTC2_ICR0 && (irq > 128))
		__raw_writeb(5, MCFINTC2_ICR0 + irq - 128);
	else if (MCFINTC1_ICR0 && (irq > 64))
		__raw_writeb(5, MCFINTC1_ICR0 + irq - 64);
	else
		__raw_writeb(5, MCFINTC0_ICR0 + irq);

	intc_irq_unmask(d);
	return 0;
}