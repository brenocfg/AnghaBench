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
struct regmap_async {int /*<<< orphan*/  list; struct regmap* map; } ;
struct regmap {int async_ret; int /*<<< orphan*/  async_waitq; int /*<<< orphan*/  async_lock; int /*<<< orphan*/  async_list; int /*<<< orphan*/  async_free; } ;

/* Variables and functions */
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_regmap_async_io_complete (struct regmap*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void regmap_async_complete_cb(struct regmap_async *async, int ret)
{
	struct regmap *map = async->map;
	bool wake;

	trace_regmap_async_io_complete(map);

	spin_lock(&map->async_lock);
	list_move(&async->list, &map->async_free);
	wake = list_empty(&map->async_list);

	if (ret != 0)
		map->async_ret = ret;

	spin_unlock(&map->async_lock);

	if (wake)
		wake_up(&map->async_waitq);
}