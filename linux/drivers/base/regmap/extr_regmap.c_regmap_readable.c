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
struct TYPE_2__ {scalar_t__ format_write; } ;
struct regmap {unsigned int max_register; int (* readable_reg ) (int /*<<< orphan*/ ,unsigned int) ;scalar_t__ rd_table; int /*<<< orphan*/  dev; TYPE_1__ format; int /*<<< orphan*/  reg_read; } ;

/* Variables and functions */
 int regmap_check_range_table (struct regmap*,unsigned int,scalar_t__) ; 
 int stub1 (int /*<<< orphan*/ ,unsigned int) ; 

bool regmap_readable(struct regmap *map, unsigned int reg)
{
	if (!map->reg_read)
		return false;

	if (map->max_register && reg > map->max_register)
		return false;

	if (map->format.format_write)
		return false;

	if (map->readable_reg)
		return map->readable_reg(map->dev, reg);

	if (map->rd_table)
		return regmap_check_range_table(map, reg, map->rd_table);

	return true;
}