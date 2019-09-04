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
struct hashmap {unsigned int private_size; scalar_t__ do_count_items; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 

__attribute__((used)) static inline unsigned int hashmap_get_size(struct hashmap *map)
{
	if (map->do_count_items)
		return map->private_size;

	BUG("hashmap_get_size: size not set");
	return 0;
}