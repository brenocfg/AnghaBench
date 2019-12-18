#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int nr_regs; scalar_t__ ack; scalar_t__ mask; } ;

/* Variables and functions */
 unsigned long _read_pending_irq_reg (scalar_t__,scalar_t__) ; 
 TYPE_1__ omap4_prcm_irq_setup ; 

__attribute__((used)) static void omap44xx_prm_read_pending_irqs(unsigned long *events)
{
	int i;

	for (i = 0; i < omap4_prcm_irq_setup.nr_regs; i++)
		events[i] = _read_pending_irq_reg(omap4_prcm_irq_setup.mask +
				i * 4, omap4_prcm_irq_setup.ack + i * 4);
}