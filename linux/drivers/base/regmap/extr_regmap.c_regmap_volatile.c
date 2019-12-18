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
struct TYPE_2__ {int /*<<< orphan*/  format_write; } ;
struct regmap {int (* volatile_reg ) (int /*<<< orphan*/ ,unsigned int) ;scalar_t__ cache_ops; scalar_t__ volatile_table; int /*<<< orphan*/  dev; TYPE_1__ format; } ;

/* Variables and functions */
 int regmap_check_range_table (struct regmap*,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  regmap_readable (struct regmap*,unsigned int) ; 
 int stub1 (int /*<<< orphan*/ ,unsigned int) ; 

bool regmap_volatile(struct regmap *map, unsigned int reg)
{
	if (!map->format.format_write && !regmap_readable(map, reg))
		return false;

	if (map->volatile_reg)
		return map->volatile_reg(map->dev, reg);

	if (map->volatile_table)
		return regmap_check_range_table(map, reg, map->volatile_table);

	if (map->cache_ops)
		return false;
	else
		return true;
}