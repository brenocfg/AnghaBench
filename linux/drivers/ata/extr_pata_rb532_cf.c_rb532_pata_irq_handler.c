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
struct rb532_cf_info {int /*<<< orphan*/  irq; int /*<<< orphan*/  gpio_line; } ;
struct ata_host {struct rb532_cf_info* private_data; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_TYPE_LEVEL_HIGH ; 
 int /*<<< orphan*/  IRQ_TYPE_LEVEL_LOW ; 
 int /*<<< orphan*/  ata_sff_interrupt (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ gpiod_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_irq_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t rb532_pata_irq_handler(int irq, void *dev_instance)
{
	struct ata_host *ah = dev_instance;
	struct rb532_cf_info *info = ah->private_data;

	if (gpiod_get_value(info->gpio_line)) {
		irq_set_irq_type(info->irq, IRQ_TYPE_LEVEL_LOW);
		ata_sff_interrupt(info->irq, dev_instance);
	} else {
		irq_set_irq_type(info->irq, IRQ_TYPE_LEVEL_HIGH);
	}

	return IRQ_HANDLED;
}