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
struct locomo {int irq_base; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int IRQ_NOPROBE ; 
 int IRQ_NOREQUEST ; 
 int /*<<< orphan*/  IRQ_TYPE_EDGE_FALLING ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  irq_clear_status_flags (int,int) ; 
 int /*<<< orphan*/  irq_set_chained_handler_and_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct locomo*) ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_data (int,struct locomo*) ; 
 int /*<<< orphan*/  irq_set_irq_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  locomo_chip ; 
 int /*<<< orphan*/  locomo_handler ; 

__attribute__((used)) static void locomo_setup_irq(struct locomo *lchip)
{
	int irq = lchip->irq_base;

	/*
	 * Install handler for IRQ_LOCOMO_HW.
	 */
	irq_set_irq_type(lchip->irq, IRQ_TYPE_EDGE_FALLING);
	irq_set_chained_handler_and_data(lchip->irq, locomo_handler, lchip);

	/* Install handlers for IRQ_LOCOMO_* */
	for ( ; irq <= lchip->irq_base + 3; irq++) {
		irq_set_chip_and_handler(irq, &locomo_chip, handle_level_irq);
		irq_set_chip_data(irq, lchip);
		irq_clear_status_flags(irq, IRQ_NOREQUEST | IRQ_NOPROBE);
	}
}