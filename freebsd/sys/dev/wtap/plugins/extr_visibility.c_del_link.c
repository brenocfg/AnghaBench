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
typedef  int uint32_t ;
struct visibility_plugin {int /*<<< orphan*/  pl_mtx; struct vis_map* pl_node; } ;
struct vis_map {int* map; } ;
struct link {size_t id1; int id2; } ;

/* Variables and functions */
 int ARRAY_SIZE ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void
del_link(struct visibility_plugin *vis_plugin, struct link *l)
{

	mtx_lock(&vis_plugin->pl_mtx);
	struct vis_map *map = &vis_plugin->pl_node[l->id1];
	int index = l->id2/ARRAY_SIZE;
	int bit = l->id2 % ARRAY_SIZE;
	uint32_t value = 1 << bit;
	map->map[index] = map->map[index] & ~value;
	mtx_unlock(&vis_plugin->pl_mtx);
#if 0
	printf("map->map[index] = %u\n", map->map[index]);
#endif
}