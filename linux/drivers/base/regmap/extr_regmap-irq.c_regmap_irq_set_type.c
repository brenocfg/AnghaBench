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
struct regmap_irq_type {unsigned int types_supported; int type_reg_offset; int type_reg_mask; int type_falling_val; int type_rising_val; int type_level_low_val; int type_level_high_val; } ;
struct regmap_irq_chip_data {int* type_buf; struct regmap* map; } ;
struct regmap_irq {struct regmap_irq_type type; } ;
struct regmap {int reg_stride; } ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IRQ_TYPE_EDGE_BOTH 132 
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 struct regmap_irq_chip_data* irq_data_get_irq_chip_data (struct irq_data*) ; 
 struct regmap_irq* irq_to_regmap_irq (struct regmap_irq_chip_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int regmap_irq_set_type(struct irq_data *data, unsigned int type)
{
	struct regmap_irq_chip_data *d = irq_data_get_irq_chip_data(data);
	struct regmap *map = d->map;
	const struct regmap_irq *irq_data = irq_to_regmap_irq(d, data->hwirq);
	int reg;
	const struct regmap_irq_type *t = &irq_data->type;

	if ((t->types_supported & type) != type)
		return 0;

	reg = t->type_reg_offset / map->reg_stride;

	if (t->type_reg_mask)
		d->type_buf[reg] &= ~t->type_reg_mask;
	else
		d->type_buf[reg] &= ~(t->type_falling_val |
				      t->type_rising_val |
				      t->type_level_low_val |
				      t->type_level_high_val);
	switch (type) {
	case IRQ_TYPE_EDGE_FALLING:
		d->type_buf[reg] |= t->type_falling_val;
		break;

	case IRQ_TYPE_EDGE_RISING:
		d->type_buf[reg] |= t->type_rising_val;
		break;

	case IRQ_TYPE_EDGE_BOTH:
		d->type_buf[reg] |= (t->type_falling_val |
					t->type_rising_val);
		break;

	case IRQ_TYPE_LEVEL_HIGH:
		d->type_buf[reg] |= t->type_level_high_val;
		break;

	case IRQ_TYPE_LEVEL_LOW:
		d->type_buf[reg] |= t->type_level_low_val;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}