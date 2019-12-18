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
struct TYPE_2__ {int /*<<< orphan*/  (* format_val ) (void*,unsigned int,int /*<<< orphan*/ ) ;} ;
struct regmap {unsigned int cache_word_size; TYPE_1__ format; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 unsigned int regcache_get_val (struct regmap*,void*,unsigned int) ; 
 int /*<<< orphan*/  stub1 (void*,unsigned int,int /*<<< orphan*/ ) ; 

bool regcache_set_val(struct regmap *map, void *base, unsigned int idx,
		      unsigned int val)
{
	if (regcache_get_val(map, base, idx) == val)
		return true;

	/* Use device native format if possible */
	if (map->format.format_val) {
		map->format.format_val(base + (map->cache_word_size * idx),
				       val, 0);
		return false;
	}

	switch (map->cache_word_size) {
	case 1: {
		u8 *cache = base;

		cache[idx] = val;
		break;
	}
	case 2: {
		u16 *cache = base;

		cache[idx] = val;
		break;
	}
	case 4: {
		u32 *cache = base;

		cache[idx] = val;
		break;
	}
#ifdef CONFIG_64BIT
	case 8: {
		u64 *cache = base;

		cache[idx] = val;
		break;
	}
#endif
	default:
		BUG();
	}
	return false;
}