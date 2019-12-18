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
struct ck_ht_map {int /*<<< orphan*/  n_entries; } ;
struct ck_ht {int /*<<< orphan*/  map; } ;
typedef  int /*<<< orphan*/  CK_HT_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  CK_HT_TYPE_LOAD (int /*<<< orphan*/ *) ; 
 struct ck_ht_map* ck_pr_load_ptr (int /*<<< orphan*/ *) ; 

CK_HT_TYPE
ck_ht_count(struct ck_ht *table)
{
	struct ck_ht_map *map = ck_pr_load_ptr(&table->map);

	return CK_HT_TYPE_LOAD(&map->n_entries);
}