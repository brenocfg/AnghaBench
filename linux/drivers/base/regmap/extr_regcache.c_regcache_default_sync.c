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
struct regmap {int cache_bypass; int /*<<< orphan*/  dev; scalar_t__ reg_stride; } ;

/* Variables and functions */
 int _regmap_write (struct regmap*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int,int) ; 
 int regcache_read (struct regmap*,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  regcache_reg_needs_sync (struct regmap*,unsigned int,unsigned int) ; 
 scalar_t__ regmap_volatile (struct regmap*,unsigned int) ; 
 int /*<<< orphan*/  regmap_writeable (struct regmap*,unsigned int) ; 

__attribute__((used)) static int regcache_default_sync(struct regmap *map, unsigned int min,
				 unsigned int max)
{
	unsigned int reg;

	for (reg = min; reg <= max; reg += map->reg_stride) {
		unsigned int val;
		int ret;

		if (regmap_volatile(map, reg) ||
		    !regmap_writeable(map, reg))
			continue;

		ret = regcache_read(map, reg, &val);
		if (ret)
			return ret;

		if (!regcache_reg_needs_sync(map, reg, val))
			continue;

		map->cache_bypass = true;
		ret = _regmap_write(map, reg, val);
		map->cache_bypass = false;
		if (ret) {
			dev_err(map->dev, "Unable to sync register %#x. %d\n",
				reg, ret);
			return ret;
		}
		dev_dbg(map->dev, "Synced register %#x, value %#x\n", reg, val);
	}

	return 0;
}