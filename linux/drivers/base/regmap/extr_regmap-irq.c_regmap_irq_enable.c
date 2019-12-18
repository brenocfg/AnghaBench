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
struct regmap_irq_chip_data {unsigned int* type_buf; int clear_status; unsigned int* mask_buf; TYPE_2__* chip; struct regmap* map; } ;
struct TYPE_3__ {unsigned int type_falling_val; unsigned int type_rising_val; } ;
struct regmap_irq {size_t reg_offset; unsigned int mask; TYPE_1__ type; } ;
struct regmap {size_t reg_stride; } ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;
struct TYPE_4__ {scalar_t__ clear_on_unmask; scalar_t__ type_in_mask; } ;

/* Variables and functions */
 struct regmap_irq_chip_data* irq_data_get_irq_chip_data (struct irq_data*) ; 
 struct regmap_irq* irq_to_regmap_irq (struct regmap_irq_chip_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void regmap_irq_enable(struct irq_data *data)
{
	struct regmap_irq_chip_data *d = irq_data_get_irq_chip_data(data);
	struct regmap *map = d->map;
	const struct regmap_irq *irq_data = irq_to_regmap_irq(d, data->hwirq);
	unsigned int mask, type;

	type = irq_data->type.type_falling_val | irq_data->type.type_rising_val;

	/*
	 * The type_in_mask flag means that the underlying hardware uses
	 * separate mask bits for rising and falling edge interrupts, but
	 * we want to make them into a single virtual interrupt with
	 * configurable edge.
	 *
	 * If the interrupt we're enabling defines the falling or rising
	 * masks then instead of using the regular mask bits for this
	 * interrupt, use the value previously written to the type buffer
	 * at the corresponding offset in regmap_irq_set_type().
	 */
	if (d->chip->type_in_mask && type)
		mask = d->type_buf[irq_data->reg_offset / map->reg_stride];
	else
		mask = irq_data->mask;

	if (d->chip->clear_on_unmask)
		d->clear_status = true;

	d->mask_buf[irq_data->reg_offset / map->reg_stride] &= ~mask;
}