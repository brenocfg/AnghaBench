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
struct regmap {scalar_t__ cache_type; TYPE_1__* cache_ops; int /*<<< orphan*/  dev; int /*<<< orphan*/  reg_defaults_raw; scalar_t__ cache_free; int /*<<< orphan*/  reg_defaults; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* exit ) (struct regmap*) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ REGCACHE_NONE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct regmap*) ; 

void regcache_exit(struct regmap *map)
{
	if (map->cache_type == REGCACHE_NONE)
		return;

	BUG_ON(!map->cache_ops);

	kfree(map->reg_defaults);
	if (map->cache_free)
		kfree(map->reg_defaults_raw);

	if (map->cache_ops->exit) {
		dev_dbg(map->dev, "Destroying %s cache\n",
			map->cache_ops->name);
		map->cache_ops->exit(map);
	}
}