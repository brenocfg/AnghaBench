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
struct regmap {unsigned int reg_stride; } ;

/* Variables and functions */
 unsigned int regcache_get_val (struct regmap*,void*,unsigned int) ; 
 void* regcache_get_val_addr (struct regmap*,void*,unsigned int) ; 
 int /*<<< orphan*/  regcache_reg_needs_sync (struct regmap*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  regcache_reg_present (unsigned long*,unsigned int) ; 
 int regcache_sync_block_raw_flush (struct regmap*,void const**,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  regmap_writeable (struct regmap*,unsigned int) ; 

__attribute__((used)) static int regcache_sync_block_raw(struct regmap *map, void *block,
			    unsigned long *cache_present,
			    unsigned int block_base, unsigned int start,
			    unsigned int end)
{
	unsigned int i, val;
	unsigned int regtmp = 0;
	unsigned int base = 0;
	const void *data = NULL;
	int ret;

	for (i = start; i < end; i++) {
		regtmp = block_base + (i * map->reg_stride);

		if (!regcache_reg_present(cache_present, i) ||
		    !regmap_writeable(map, regtmp)) {
			ret = regcache_sync_block_raw_flush(map, &data,
							    base, regtmp);
			if (ret != 0)
				return ret;
			continue;
		}

		val = regcache_get_val(map, block, i);
		if (!regcache_reg_needs_sync(map, regtmp, val)) {
			ret = regcache_sync_block_raw_flush(map, &data,
							    base, regtmp);
			if (ret != 0)
				return ret;
			continue;
		}

		if (!data) {
			data = regcache_get_val_addr(map, block, i);
			base = regtmp;
		}
	}

	return regcache_sync_block_raw_flush(map, &data, base, regtmp +
			map->reg_stride);
}