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
struct regmap {int (* precious_reg ) (int /*<<< orphan*/ ,unsigned int) ;scalar_t__ precious_table; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int regmap_check_range_table (struct regmap*,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  regmap_readable (struct regmap*,unsigned int) ; 
 int stub1 (int /*<<< orphan*/ ,unsigned int) ; 

bool regmap_precious(struct regmap *map, unsigned int reg)
{
	if (!regmap_readable(map, reg))
		return false;

	if (map->precious_reg)
		return map->precious_reg(map->dev, reg);

	if (map->precious_table)
		return regmap_check_range_table(map, reg, map->precious_table);

	return false;
}