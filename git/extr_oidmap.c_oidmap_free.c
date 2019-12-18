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
struct oidmap {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  hashmap_free_ (int /*<<< orphan*/ *,int) ; 

void oidmap_free(struct oidmap *map, int free_entries)
{
	if (!map)
		return;

	/* TODO: make oidmap itself not depend on struct layouts */
	hashmap_free_(&map->map, free_entries ? 0 : -1);
}