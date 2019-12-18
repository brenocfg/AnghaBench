#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t val_bytes; int /*<<< orphan*/  (* format_val ) (void*,unsigned int,int /*<<< orphan*/ ) ;} ;
struct regmap {scalar_t__ cache_type; size_t max_raw_read; int /*<<< orphan*/  lock_arg; int /*<<< orphan*/  (* unlock ) (int /*<<< orphan*/ ) ;TYPE_2__ format; scalar_t__ use_single_read; TYPE_1__* bus; scalar_t__ cache_bypass; int /*<<< orphan*/  (* lock ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  reg_stride; } ;
struct TYPE_3__ {int /*<<< orphan*/  read; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  IS_ALIGNED (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ REGCACHE_NONE ; 
 int _regmap_raw_read (struct regmap*,unsigned int,void*,size_t) ; 
 int _regmap_read (struct regmap*,scalar_t__,unsigned int*) ; 
 scalar_t__ regmap_get_offset (struct regmap*,int) ; 
 scalar_t__ regmap_volatile_range (struct regmap*,unsigned int,size_t) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (void*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 

int regmap_raw_read(struct regmap *map, unsigned int reg, void *val,
		    size_t val_len)
{
	size_t val_bytes = map->format.val_bytes;
	size_t val_count = val_len / val_bytes;
	unsigned int v;
	int ret, i;

	if (!map->bus)
		return -EINVAL;
	if (val_len % map->format.val_bytes)
		return -EINVAL;
	if (!IS_ALIGNED(reg, map->reg_stride))
		return -EINVAL;
	if (val_count == 0)
		return -EINVAL;

	map->lock(map->lock_arg);

	if (regmap_volatile_range(map, reg, val_count) || map->cache_bypass ||
	    map->cache_type == REGCACHE_NONE) {
		size_t chunk_count, chunk_bytes;
		size_t chunk_regs = val_count;

		if (!map->bus->read) {
			ret = -ENOTSUPP;
			goto out;
		}

		if (map->use_single_read)
			chunk_regs = 1;
		else if (map->max_raw_read && val_len > map->max_raw_read)
			chunk_regs = map->max_raw_read / val_bytes;

		chunk_count = val_count / chunk_regs;
		chunk_bytes = chunk_regs * val_bytes;

		/* Read bytes that fit into whole chunks */
		for (i = 0; i < chunk_count; i++) {
			ret = _regmap_raw_read(map, reg, val, chunk_bytes);
			if (ret != 0)
				goto out;

			reg += regmap_get_offset(map, chunk_regs);
			val += chunk_bytes;
			val_len -= chunk_bytes;
		}

		/* Read remaining bytes */
		if (val_len) {
			ret = _regmap_raw_read(map, reg, val, val_len);
			if (ret != 0)
				goto out;
		}
	} else {
		/* Otherwise go word by word for the cache; should be low
		 * cost as we expect to hit the cache.
		 */
		for (i = 0; i < val_count; i++) {
			ret = _regmap_read(map, reg + regmap_get_offset(map, i),
					   &v);
			if (ret != 0)
				goto out;

			map->format.format_val(val + (i * val_bytes), v, 0);
		}
	}

 out:
	map->unlock(map->lock_arg);

	return ret;
}