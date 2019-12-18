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
typedef  int u16 ;
struct irq_data {unsigned int irq; } ;

/* Variables and functions */
#define  IRQ_TYPE_EDGE_BOTH 130 
#define  IRQ_TYPE_EDGE_FALLING 129 
#define  IRQ_TYPE_EDGE_RISING 128 
 int /*<<< orphan*/  MCFEPORT_EPPAR ; 
 int __raw_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writew (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int irq2ebit (unsigned int) ; 
 int /*<<< orphan*/  irq_set_handler (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intc_irq_set_type(struct irq_data *d, unsigned int type)
{
	unsigned int ebit, irq = d->irq;
	u16 pa, tb;

	switch (type) {
	case IRQ_TYPE_EDGE_RISING:
		tb = 0x1;
		break;
	case IRQ_TYPE_EDGE_FALLING:
		tb = 0x2;
		break;
	case IRQ_TYPE_EDGE_BOTH:
		tb = 0x3;
		break;
	default:
		/* Level triggered */
		tb = 0;
		break;
	}

	if (tb)
		irq_set_handler(irq, handle_edge_irq);

	ebit = irq2ebit(irq) * 2;
	pa = __raw_readw(MCFEPORT_EPPAR);
	pa = (pa & ~(0x3 << ebit)) | (tb << ebit);
	__raw_writew(pa, MCFEPORT_EPPAR);
	
	return 0;
}