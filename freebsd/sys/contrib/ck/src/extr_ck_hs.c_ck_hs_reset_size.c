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
struct ck_hs_map {int dummy; } ;
struct ck_hs {int /*<<< orphan*/  m; struct ck_hs_map* map; } ;

/* Variables and functions */
 struct ck_hs_map* ck_hs_map_create (struct ck_hs*,unsigned long) ; 
 int /*<<< orphan*/  ck_hs_map_destroy (int /*<<< orphan*/ ,struct ck_hs_map*,int) ; 
 int /*<<< orphan*/  ck_pr_store_ptr (struct ck_hs_map**,struct ck_hs_map*) ; 

bool
ck_hs_reset_size(struct ck_hs *hs, unsigned long capacity)
{
	struct ck_hs_map *map, *previous;

	previous = hs->map;
	map = ck_hs_map_create(hs, capacity);
	if (map == NULL)
		return false;

	ck_pr_store_ptr(&hs->map, map);
	ck_hs_map_destroy(hs->m, previous, true);
	return true;
}