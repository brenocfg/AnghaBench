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
struct regmap {int (* reg_read ) (void*,unsigned int,unsigned int*) ;int /*<<< orphan*/  cache_bypass; int /*<<< orphan*/  dev; scalar_t__ cache_only; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 void* _regmap_map_get_context (struct regmap*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int regcache_read (struct regmap*,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  regcache_write (struct regmap*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  regmap_readable (struct regmap*,unsigned int) ; 
 scalar_t__ regmap_should_log (struct regmap*) ; 
 int stub1 (void*,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  trace_regmap_reg_read (struct regmap*,unsigned int,unsigned int) ; 

__attribute__((used)) static int _regmap_read(struct regmap *map, unsigned int reg,
			unsigned int *val)
{
	int ret;
	void *context = _regmap_map_get_context(map);

	if (!map->cache_bypass) {
		ret = regcache_read(map, reg, val);
		if (ret == 0)
			return 0;
	}

	if (map->cache_only)
		return -EBUSY;

	if (!regmap_readable(map, reg))
		return -EIO;

	ret = map->reg_read(context, reg, val);
	if (ret == 0) {
		if (regmap_should_log(map))
			dev_info(map->dev, "%x => %x\n", reg, *val);

		trace_regmap_reg_read(map, reg, *val);

		if (!map->cache_bypass)
			regcache_write(map, reg, *val);
	}

	return ret;
}