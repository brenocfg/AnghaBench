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
struct regmap {int cache_dirty; int (* reg_write ) (void*,unsigned int,unsigned int) ;int /*<<< orphan*/  dev; scalar_t__ cache_only; int /*<<< orphan*/  defer_caching; int /*<<< orphan*/  cache_bypass; } ;

/* Variables and functions */
 int EIO ; 
 void* _regmap_map_get_context (struct regmap*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int regcache_write (struct regmap*,unsigned int,unsigned int) ; 
 scalar_t__ regmap_should_log (struct regmap*) ; 
 int /*<<< orphan*/  regmap_writeable (struct regmap*,unsigned int) ; 
 int stub1 (void*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  trace_regmap_reg_write (struct regmap*,unsigned int,unsigned int) ; 

int _regmap_write(struct regmap *map, unsigned int reg,
		  unsigned int val)
{
	int ret;
	void *context = _regmap_map_get_context(map);

	if (!regmap_writeable(map, reg))
		return -EIO;

	if (!map->cache_bypass && !map->defer_caching) {
		ret = regcache_write(map, reg, val);
		if (ret != 0)
			return ret;
		if (map->cache_only) {
			map->cache_dirty = true;
			return 0;
		}
	}

	if (regmap_should_log(map))
		dev_info(map->dev, "%x <= %x\n", reg, val);

	trace_regmap_reg_write(map, reg, val);

	return map->reg_write(context, reg, val);
}