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
struct irq_data {int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* irq_mask ) (struct irq_data*) ;} ;
struct irq_chip_type {TYPE_1__ chip; } ;

/* Variables and functions */
 struct irq_chip_type* irq_data_get_chip_type (struct irq_data*) ; 
 int /*<<< orphan*/  omap_ack_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct irq_data*) ; 

__attribute__((used)) static void omap_mask_ack_irq(struct irq_data *d)
{
	struct irq_chip_type *ct = irq_data_get_chip_type(d);

	ct->chip.irq_mask(d);
	omap_ack_irq(d->irq);
}