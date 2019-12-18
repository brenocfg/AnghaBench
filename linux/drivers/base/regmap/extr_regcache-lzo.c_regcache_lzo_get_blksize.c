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
struct regmap {int /*<<< orphan*/  cache_size_raw; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_lzo_block_count (struct regmap*) ; 

__attribute__((used)) static inline int regcache_lzo_get_blksize(struct regmap *map)
{
	return DIV_ROUND_UP(map->cache_size_raw,
			    regcache_lzo_block_count(map));
}