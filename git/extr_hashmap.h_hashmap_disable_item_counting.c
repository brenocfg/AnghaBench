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
struct hashmap {scalar_t__ do_count_items; } ;

/* Variables and functions */

__attribute__((used)) static inline void hashmap_disable_item_counting(struct hashmap *map)
{
	map->do_count_items = 0;
}