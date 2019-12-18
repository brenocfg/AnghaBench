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
struct regmap_irq_sub_irq_map {int num_regs; unsigned int* offset; } ;
struct regmap_irq_chip_data {unsigned int irq_reg_stride; int /*<<< orphan*/ * status_buf; struct regmap* map; struct regmap_irq_chip* chip; } ;
struct regmap_irq_chip {scalar_t__ status_base; struct regmap_irq_sub_irq_map* sub_reg_offsets; } ;
struct regmap {unsigned int reg_stride; } ;

/* Variables and functions */
 int regmap_read (struct regmap*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int read_sub_irq_data(struct regmap_irq_chip_data *data,
					   unsigned int b)
{
	const struct regmap_irq_chip *chip = data->chip;
	struct regmap *map = data->map;
	struct regmap_irq_sub_irq_map *subreg;
	int i, ret = 0;

	if (!chip->sub_reg_offsets) {
		/* Assume linear mapping */
		ret = regmap_read(map, chip->status_base +
				  (b * map->reg_stride * data->irq_reg_stride),
				   &data->status_buf[b]);
	} else {
		subreg = &chip->sub_reg_offsets[b];
		for (i = 0; i < subreg->num_regs; i++) {
			unsigned int offset = subreg->offset[i];

			ret = regmap_read(map, chip->status_base + offset,
					  &data->status_buf[offset]);
			if (ret)
				break;
		}
	}
	return ret;
}