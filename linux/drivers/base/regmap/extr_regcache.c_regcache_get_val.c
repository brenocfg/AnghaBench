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
typedef  unsigned int u8 ;
typedef  unsigned int u64 ;
typedef  unsigned int u32 ;
typedef  unsigned int u16 ;
struct TYPE_2__ {unsigned int (* parse_val ) (int /*<<< orphan*/ ) ;} ;
struct regmap {int cache_word_size; TYPE_1__ format; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 unsigned int EINVAL ; 
 int /*<<< orphan*/  regcache_get_val_addr (struct regmap*,void const*,unsigned int) ; 
 unsigned int stub1 (int /*<<< orphan*/ ) ; 

unsigned int regcache_get_val(struct regmap *map, const void *base,
			      unsigned int idx)
{
	if (!base)
		return -EINVAL;

	/* Use device native format if possible */
	if (map->format.parse_val)
		return map->format.parse_val(regcache_get_val_addr(map, base,
								   idx));

	switch (map->cache_word_size) {
	case 1: {
		const u8 *cache = base;

		return cache[idx];
	}
	case 2: {
		const u16 *cache = base;

		return cache[idx];
	}
	case 4: {
		const u32 *cache = base;

		return cache[idx];
	}
#ifdef CONFIG_64BIT
	case 8: {
		const u64 *cache = base;

		return cache[idx];
	}
#endif
	default:
		BUG();
	}
	/* unreachable */
	return -1;
}