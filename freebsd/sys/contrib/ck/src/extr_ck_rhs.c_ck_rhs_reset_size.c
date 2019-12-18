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
struct ck_rhs_map {int dummy; } ;
struct ck_rhs {int /*<<< orphan*/  m; struct ck_rhs_map* map; } ;

/* Variables and functions */
 int /*<<< orphan*/  ck_pr_store_ptr (struct ck_rhs_map**,struct ck_rhs_map*) ; 
 struct ck_rhs_map* ck_rhs_map_create (struct ck_rhs*,unsigned long) ; 
 int /*<<< orphan*/  ck_rhs_map_destroy (int /*<<< orphan*/ ,struct ck_rhs_map*,int) ; 

bool
ck_rhs_reset_size(struct ck_rhs *hs, unsigned long capacity)
{
	struct ck_rhs_map *map, *previous;

	previous = hs->map;
	map = ck_rhs_map_create(hs, capacity);
	if (map == NULL)
		return false;

	ck_pr_store_ptr(&hs->map, map);
	ck_rhs_map_destroy(hs->m, previous, true);
	return true;
}