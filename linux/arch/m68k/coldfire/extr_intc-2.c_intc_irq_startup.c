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
 scalar_t__ EINT0 ; 
 unsigned int EINT1 ; 
 unsigned int EINT7 ; 
 unsigned long MCFEPORT_EPDDR ; 
 unsigned long MCFEPORT_EPIER ; 
 unsigned long MCFICM_INTC0 ; 
 unsigned long MCFICM_INTC1 ; 
 scalar_t__ MCFINTC_ICR0 ; 
 unsigned int MCFINT_VECBASE ; 
 scalar_t__ __raw_readb (unsigned long) ; 
 int /*<<< orphan*/  __raw_writeb (int,unsigned long) ; 
 int /*<<< orphan*/  intc_intpri ; 
 int /*<<< orphan*/  intc_irq_unmask (struct irq_data*) ; 

__attribute__((used)) static unsigned int intc_irq_startup(struct irq_data *d)
{
	unsigned int irq = d->irq - MCFINT_VECBASE;
	unsigned long icraddr;

#ifdef MCFICM_INTC1
	icraddr = (irq & 0x40) ? MCFICM_INTC1 : MCFICM_INTC0;
#else
	icraddr = MCFICM_INTC0;
#endif
	icraddr += MCFINTC_ICR0 + (irq & 0x3f);
	if (__raw_readb(icraddr) == 0)
		__raw_writeb(intc_intpri--, icraddr);

	irq = d->irq;
	if ((irq >= EINT1) && (irq <= EINT7)) {
		u8 v;

		irq -= EINT0;

		/* Set EPORT line as input */
		v = __raw_readb(MCFEPORT_EPDDR);
		__raw_writeb(v & ~(0x1 << irq), MCFEPORT_EPDDR);

		/* Set EPORT line as interrupt source */
		v = __raw_readb(MCFEPORT_EPIER);
		__raw_writeb(v | (0x1 << irq), MCFEPORT_EPIER);
	}

	intc_irq_unmask(d);
	return 0;
}