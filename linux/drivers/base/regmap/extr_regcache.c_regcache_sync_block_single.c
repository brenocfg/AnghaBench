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
struct regmap {unsigned int reg_stride; int cache_bypass; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int _regmap_write (struct regmap*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int,int) ; 
 unsigned int regcache_get_val (struct regmap*,void*,unsigned int) ; 
 int /*<<< orphan*/  regcache_reg_needs_sync (struct regmap*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  regcache_reg_present (unsigned long*,unsigned int) ; 
 int /*<<< orphan*/  regmap_writeable (struct regmap*,unsigned int) ; 

__attribute__((used)) static int regcache_sync_block_single(struct regmap *map, void *block,
				      unsigned long *cache_present,
				      unsigned int block_base,
				      unsigned int start, unsigned int end)
{
	unsigned int i, regtmp, val;
	int ret;

	for (i = start; i < end; i++) {
		regtmp = block_base + (i * map->reg_stride);

		if (!regcache_reg_present(cache_present, i) ||
		    !regmap_writeable(map, regtmp))
			continue;

		val = regcache_get_val(map, block, i);
		if (!regcache_reg_needs_sync(map, regtmp, val))
			continue;

		map->cache_bypass = true;

		ret = _regmap_write(map, regtmp, val);

		map->cache_bypass = false;
		if (ret != 0) {
			dev_err(map->dev, "Unable to sync register %#x. %d\n",
				regtmp, ret);
			return ret;
		}
		dev_dbg(map->dev, "Synced register %#x, value %#x\n",
			regtmp, val);
	}

	return 0;
}