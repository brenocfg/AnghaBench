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
struct regmap_irq_chip_data {int /*<<< orphan*/  map; TYPE_1__* chip; } ;
struct TYPE_2__ {scalar_t__ mask_writeonly; } ;

/* Variables and functions */
 int regmap_update_bits (int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 
 int regmap_write_bits (int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static int regmap_irq_update_bits(struct regmap_irq_chip_data *d,
				  unsigned int reg, unsigned int mask,
				  unsigned int val)
{
	if (d->chip->mask_writeonly)
		return regmap_write_bits(d->map, reg, mask, val);
	else
		return regmap_update_bits(d->map, reg, mask, val);
}