#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* mask; void* ack; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq_set_wake; int /*<<< orphan*/  irq_release_resources; int /*<<< orphan*/  irq_request_resources; int /*<<< orphan*/  irq_disable; int /*<<< orphan*/  irq_enable; int /*<<< orphan*/  irq_set_type; int /*<<< orphan*/  irq_unmask; int /*<<< orphan*/  irq_mask; int /*<<< orphan*/  irq_ack; } ;
struct irq_chip_type {int /*<<< orphan*/  handler; void* type; TYPE_2__ regs; TYPE_1__ chip; } ;
struct irq_chip_generic {struct irq_chip_type* chip_types; struct dwapb_gpio* private; int /*<<< orphan*/  reg_base; } ;
struct gpio_chip {unsigned int ngpio; int /*<<< orphan*/  to_irq; } ;
struct fwnode_handle {int dummy; } ;
struct dwapb_port_property {int ngpio; scalar_t__* irq; int /*<<< orphan*/  irq_shared; struct fwnode_handle* fwnode; } ;
struct dwapb_gpio_port {struct gpio_chip gc; } ;
struct dwapb_gpio {int /*<<< orphan*/ * domain; int /*<<< orphan*/  dev; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_INTMASK ; 
 int /*<<< orphan*/  GPIO_PORTA_EOI ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  IRQ_GC_INIT_NESTED_LOCK ; 
 int /*<<< orphan*/  IRQ_NOREQUEST ; 
 void* IRQ_TYPE_EDGE_BOTH ; 
 void* IRQ_TYPE_LEVEL_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int devm_request_irq (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct dwapb_gpio*) ; 
 int /*<<< orphan*/  dwapb_gpio_to_irq ; 
 int /*<<< orphan*/  dwapb_irq_disable ; 
 int /*<<< orphan*/  dwapb_irq_enable ; 
 int /*<<< orphan*/  dwapb_irq_handler ; 
 int /*<<< orphan*/  dwapb_irq_handler_mfd ; 
 int /*<<< orphan*/  dwapb_irq_relres ; 
 int /*<<< orphan*/  dwapb_irq_reqres ; 
 int /*<<< orphan*/  dwapb_irq_set_type ; 
 int /*<<< orphan*/  dwapb_irq_set_wake ; 
 void* gpio_reg_convert (struct dwapb_gpio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int irq_alloc_domain_generic_chips (int /*<<< orphan*/ *,unsigned int,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_create_mapping (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/ * irq_domain_create_linear (struct fwnode_handle*,unsigned int,int /*<<< orphan*/ *,struct dwapb_gpio*) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_gc_ack_set_bit ; 
 int /*<<< orphan*/  irq_gc_mask_clr_bit ; 
 int /*<<< orphan*/  irq_gc_mask_set_bit ; 
 int /*<<< orphan*/  irq_generic_chip_ops ; 
 struct irq_chip_generic* irq_get_domain_generic_chip (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chained_handler_and_data (scalar_t__,int /*<<< orphan*/ ,struct dwapb_gpio*) ; 

__attribute__((used)) static void dwapb_configure_irqs(struct dwapb_gpio *gpio,
				 struct dwapb_gpio_port *port,
				 struct dwapb_port_property *pp)
{
	struct gpio_chip *gc = &port->gc;
	struct fwnode_handle  *fwnode = pp->fwnode;
	struct irq_chip_generic	*irq_gc = NULL;
	unsigned int hwirq, ngpio = gc->ngpio;
	struct irq_chip_type *ct;
	int err, i;

	gpio->domain = irq_domain_create_linear(fwnode, ngpio,
						 &irq_generic_chip_ops, gpio);
	if (!gpio->domain)
		return;

	err = irq_alloc_domain_generic_chips(gpio->domain, ngpio, 2,
					     "gpio-dwapb", handle_level_irq,
					     IRQ_NOREQUEST, 0,
					     IRQ_GC_INIT_NESTED_LOCK);
	if (err) {
		dev_info(gpio->dev, "irq_alloc_domain_generic_chips failed\n");
		irq_domain_remove(gpio->domain);
		gpio->domain = NULL;
		return;
	}

	irq_gc = irq_get_domain_generic_chip(gpio->domain, 0);
	if (!irq_gc) {
		irq_domain_remove(gpio->domain);
		gpio->domain = NULL;
		return;
	}

	irq_gc->reg_base = gpio->regs;
	irq_gc->private = gpio;

	for (i = 0; i < 2; i++) {
		ct = &irq_gc->chip_types[i];
		ct->chip.irq_ack = irq_gc_ack_set_bit;
		ct->chip.irq_mask = irq_gc_mask_set_bit;
		ct->chip.irq_unmask = irq_gc_mask_clr_bit;
		ct->chip.irq_set_type = dwapb_irq_set_type;
		ct->chip.irq_enable = dwapb_irq_enable;
		ct->chip.irq_disable = dwapb_irq_disable;
		ct->chip.irq_request_resources = dwapb_irq_reqres;
		ct->chip.irq_release_resources = dwapb_irq_relres;
#ifdef CONFIG_PM_SLEEP
		ct->chip.irq_set_wake = dwapb_irq_set_wake;
#endif
		ct->regs.ack = gpio_reg_convert(gpio, GPIO_PORTA_EOI);
		ct->regs.mask = gpio_reg_convert(gpio, GPIO_INTMASK);
		ct->type = IRQ_TYPE_LEVEL_MASK;
	}

	irq_gc->chip_types[0].type = IRQ_TYPE_LEVEL_MASK;
	irq_gc->chip_types[1].type = IRQ_TYPE_EDGE_BOTH;
	irq_gc->chip_types[1].handler = handle_edge_irq;

	if (!pp->irq_shared) {
		int i;

		for (i = 0; i < pp->ngpio; i++) {
			if (pp->irq[i] >= 0)
				irq_set_chained_handler_and_data(pp->irq[i],
						dwapb_irq_handler, gpio);
		}
	} else {
		/*
		 * Request a shared IRQ since where MFD would have devices
		 * using the same irq pin
		 */
		err = devm_request_irq(gpio->dev, pp->irq[0],
				       dwapb_irq_handler_mfd,
				       IRQF_SHARED, "gpio-dwapb-mfd", gpio);
		if (err) {
			dev_err(gpio->dev, "error requesting IRQ\n");
			irq_domain_remove(gpio->domain);
			gpio->domain = NULL;
			return;
		}
	}

	for (hwirq = 0 ; hwirq < ngpio ; hwirq++)
		irq_create_mapping(gpio->domain, hwirq);

	port->gc.to_irq = dwapb_gpio_to_irq;
}