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
struct irq_data {unsigned int irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IT8152_INTC_LDCNIMR ; 
 int /*<<< orphan*/  IT8152_INTC_LPCNIMR ; 
 int /*<<< orphan*/  IT8152_INTC_PDCNIMR ; 
 unsigned int IT8152_LD_IRQ (int /*<<< orphan*/ ) ; 
 unsigned int IT8152_LP_IRQ (int /*<<< orphan*/ ) ; 
 unsigned int IT8152_PD_IRQ (int /*<<< orphan*/ ) ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void it8152_unmask_irq(struct irq_data *d)
{
	unsigned int irq = d->irq;

       if (irq >= IT8152_LD_IRQ(0)) {
	       __raw_writel((__raw_readl(IT8152_INTC_LDCNIMR) &
			     ~(1 << (irq - IT8152_LD_IRQ(0)))),
			    IT8152_INTC_LDCNIMR);
       } else if (irq >= IT8152_LP_IRQ(0)) {
	       __raw_writel((__raw_readl(IT8152_INTC_LPCNIMR) &
			     ~(1 << (irq - IT8152_LP_IRQ(0)))),
			    IT8152_INTC_LPCNIMR);
       } else if (irq >= IT8152_PD_IRQ(0)) {
	       __raw_writel((__raw_readl(IT8152_INTC_PDCNIMR) &
			     ~(1 << (irq - IT8152_PD_IRQ(0)))),
			    IT8152_INTC_PDCNIMR);
       }
}