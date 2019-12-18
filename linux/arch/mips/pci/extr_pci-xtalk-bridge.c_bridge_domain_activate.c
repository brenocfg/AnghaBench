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
typedef  int u32 ;
struct irq_domain {int dummy; } ;
struct irq_data {int hwirq; TYPE_1__* parent_data; struct bridge_irq_chip_data* chip_data; } ;
struct bridge_irq_chip_data {int nasid; struct bridge_controller* bc; } ;
struct bridge_controller {int intr_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;
struct TYPE_3__ {int hwirq; } ;

/* Variables and functions */
 TYPE_2__* b_int_addr ; 
 int /*<<< orphan*/  b_int_device ; 
 int /*<<< orphan*/  b_int_enable ; 
 int /*<<< orphan*/  b_int_mode ; 
 int /*<<< orphan*/  b_wid_tflush ; 
 int bridge_read (struct bridge_controller*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bridge_set (struct bridge_controller*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  bridge_write (struct bridge_controller*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bridge_domain_activate(struct irq_domain *domain,
				  struct irq_data *irqd, bool reserve)
{
	struct bridge_irq_chip_data *data = irqd->chip_data;
	struct bridge_controller *bc = data->bc;
	int bit = irqd->parent_data->hwirq;
	int pin = irqd->hwirq;
	u32 device;

	bridge_write(bc, b_int_addr[pin].addr,
		     (((bc->intr_addr >> 30) & 0x30000) |
		      bit | (data->nasid << 8)));
	bridge_set(bc, b_int_enable, (1 << pin));
	bridge_set(bc, b_int_enable, 0x7ffffe00); /* more stuff in int_enable */

	/*
	 * Enable sending of an interrupt clear packt to the hub on a high to
	 * low transition of the interrupt pin.
	 *
	 * IRIX sets additional bits in the address which are documented as
	 * reserved in the bridge docs.
	 */
	bridge_set(bc, b_int_mode, (1UL << pin));

	/*
	 * We assume the bridge to have a 1:1 mapping between devices
	 * (slots) and intr pins.
	 */
	device = bridge_read(bc, b_int_device);
	device &= ~(7 << (pin*3));
	device |= (pin << (pin*3));
	bridge_write(bc, b_int_device, device);

	bridge_read(bc, b_wid_tflush);
	return 0;
}