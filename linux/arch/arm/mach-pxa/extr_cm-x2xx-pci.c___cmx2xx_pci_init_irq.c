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
 int /*<<< orphan*/  IRQ_TYPE_EDGE_RISING ; 
 int /*<<< orphan*/  cmx2xx_it8152_irq_demux ; 
 int cmx2xx_it8152_irq_gpio ; 
 int /*<<< orphan*/  gpio_to_irq (int) ; 
 int /*<<< orphan*/  irq_set_chained_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_irq_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  it8152_init_irq () ; 

void __cmx2xx_pci_init_irq(int irq_gpio)
{
	it8152_init_irq();

	cmx2xx_it8152_irq_gpio = irq_gpio;

	irq_set_irq_type(gpio_to_irq(irq_gpio), IRQ_TYPE_EDGE_RISING);

	irq_set_chained_handler(gpio_to_irq(irq_gpio),
				cmx2xx_it8152_irq_demux);
}