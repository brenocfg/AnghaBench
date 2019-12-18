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
struct ck_rhs_map {unsigned long max_entries; unsigned long capacity; unsigned long n_entries; } ;
struct ck_rhs {unsigned int load_factor; struct ck_rhs_map* map; } ;

/* Variables and functions */
 int ck_rhs_grow (struct ck_rhs*,int) ; 

bool
ck_rhs_set_load_factor(struct ck_rhs *hs, unsigned int load_factor)
{
	struct ck_rhs_map *map = hs->map;

	if (load_factor == 0 || load_factor > 100)
		return false;

	hs->load_factor = load_factor;
	map->max_entries = (map->capacity * (unsigned long)hs->load_factor) / 100;
	while (map->n_entries > map->max_entries) {
		if (ck_rhs_grow(hs, map->capacity << 1) == false)
			return false;
		map = hs->map;
	}
	return true;
}