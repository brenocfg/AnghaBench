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
struct irq_data {int irq; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IRQ_TYPE_EDGE_BOTH 133 
#define  IRQ_TYPE_EDGE_FALLING 132 
#define  IRQ_TYPE_EDGE_RISING 131 
#define  IRQ_TYPE_LEVEL_HIGH 130 
#define  IRQ_TYPE_LEVEL_LOW 129 
#define  IRQ_TYPE_NONE 128 
 int /*<<< orphan*/  LS1X_INTC_INTEDGE (unsigned int) ; 
 int /*<<< orphan*/  LS1X_INTC_INTPOL (unsigned int) ; 
 int LS1X_IRQ_BASE ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ls1x_irq_settype(struct irq_data *d, unsigned int type)
{
	unsigned int bit = (d->irq - LS1X_IRQ_BASE) & 0x1f;
	unsigned int n = (d->irq - LS1X_IRQ_BASE) >> 5;

	switch (type) {
	case IRQ_TYPE_LEVEL_HIGH:
		__raw_writel(__raw_readl(LS1X_INTC_INTPOL(n))
			| (1 << bit), LS1X_INTC_INTPOL(n));
		__raw_writel(__raw_readl(LS1X_INTC_INTEDGE(n))
			& ~(1 << bit), LS1X_INTC_INTEDGE(n));
		break;
	case IRQ_TYPE_LEVEL_LOW:
		__raw_writel(__raw_readl(LS1X_INTC_INTPOL(n))
			& ~(1 << bit), LS1X_INTC_INTPOL(n));
		__raw_writel(__raw_readl(LS1X_INTC_INTEDGE(n))
			& ~(1 << bit), LS1X_INTC_INTEDGE(n));
		break;
	case IRQ_TYPE_EDGE_RISING:
		__raw_writel(__raw_readl(LS1X_INTC_INTPOL(n))
			| (1 << bit), LS1X_INTC_INTPOL(n));
		__raw_writel(__raw_readl(LS1X_INTC_INTEDGE(n))
			| (1 << bit), LS1X_INTC_INTEDGE(n));
		break;
	case IRQ_TYPE_EDGE_FALLING:
		__raw_writel(__raw_readl(LS1X_INTC_INTPOL(n))
			& ~(1 << bit), LS1X_INTC_INTPOL(n));
		__raw_writel(__raw_readl(LS1X_INTC_INTEDGE(n))
			| (1 << bit), LS1X_INTC_INTEDGE(n));
		break;
	case IRQ_TYPE_EDGE_BOTH:
		__raw_writel(__raw_readl(LS1X_INTC_INTPOL(n))
			& ~(1 << bit), LS1X_INTC_INTPOL(n));
		__raw_writel(__raw_readl(LS1X_INTC_INTEDGE(n))
			| (1 << bit), LS1X_INTC_INTEDGE(n));
		break;
	case IRQ_TYPE_NONE:
		break;
	default:
		return -EINVAL;
	}

	return 0;
}