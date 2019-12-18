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
struct ck_ht_map {int dummy; } ;
struct ck_ht {int /*<<< orphan*/  m; struct ck_ht_map* map; } ;
typedef  int /*<<< orphan*/  CK_HT_TYPE ;

/* Variables and functions */
 struct ck_ht_map* ck_ht_map_create (struct ck_ht*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ck_ht_map_destroy (int /*<<< orphan*/ ,struct ck_ht_map*,int) ; 
 int /*<<< orphan*/  ck_pr_store_ptr_unsafe (struct ck_ht_map**,struct ck_ht_map*) ; 

bool
ck_ht_reset_size_spmc(struct ck_ht *table, CK_HT_TYPE size)
{
	struct ck_ht_map *map, *update;

	map = table->map;
	update = ck_ht_map_create(table, size);
	if (update == NULL)
		return false;

	ck_pr_store_ptr_unsafe(&table->map, update);
	ck_ht_map_destroy(table->m, map, true);
	return true;
}