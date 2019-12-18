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
struct irq_desc {int dummy; } ;

/* Variables and functions */
 unsigned int HD64461_IRQBASE ; 
 int HD64461_IRQ_NUM ; 
 int /*<<< orphan*/  HD64461_NIRR ; 
 unsigned short __raw_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 

__attribute__((used)) static void hd64461_irq_demux(struct irq_desc *desc)
{
	unsigned short intv = __raw_readw(HD64461_NIRR);
	unsigned int ext_irq = HD64461_IRQBASE;

	intv &= (1 << HD64461_IRQ_NUM) - 1;

	for (; intv; intv >>= 1, ext_irq++) {
		if (!(intv & 1))
			continue;

		generic_handle_irq(ext_irq);
	}
}