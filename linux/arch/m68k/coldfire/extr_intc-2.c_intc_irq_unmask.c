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
typedef  int u32 ;
struct irq_data {unsigned int irq; } ;

/* Variables and functions */
 unsigned long MCFICM_INTC0 ; 
 unsigned long MCFICM_INTC1 ; 
 scalar_t__ MCFINTC_IMRH ; 
 scalar_t__ MCFINTC_IMRL ; 
 unsigned int MCFINT_VECBASE ; 
 int __raw_readl (unsigned long) ; 
 int /*<<< orphan*/  __raw_writel (int,unsigned long) ; 

__attribute__((used)) static void intc_irq_unmask(struct irq_data *d)
{
	unsigned int irq = d->irq - MCFINT_VECBASE;
	unsigned long imraddr;
	u32 val, imrbit;

#ifdef MCFICM_INTC1
	imraddr = (irq & 0x40) ? MCFICM_INTC1 : MCFICM_INTC0;
#else
	imraddr = MCFICM_INTC0;
#endif
	imraddr += ((irq & 0x20) ? MCFINTC_IMRH : MCFINTC_IMRL);
	imrbit = 0x1 << (irq & 0x1f);

	/* Don't set the "maskall" bit! */
	if ((irq & 0x20) == 0)
		imrbit |= 0x1;

	val = __raw_readl(imraddr);
	__raw_writel(val & ~imrbit, imraddr);
}