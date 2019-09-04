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
struct hashmap_iter {int dummy; } ;
struct hashmap {int do_count_items; unsigned int private_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  hashmap_iter_init (struct hashmap*,struct hashmap_iter*) ; 
 scalar_t__ hashmap_iter_next (struct hashmap_iter*) ; 

__attribute__((used)) static inline void hashmap_enable_item_counting(struct hashmap *map)
{
	unsigned int n = 0;
	struct hashmap_iter iter;

	if (map->do_count_items)
		return;

	hashmap_iter_init(map, &iter);
	while (hashmap_iter_next(&iter))
		n++;

	map->do_count_items = 1;
	map->private_size = n;
}