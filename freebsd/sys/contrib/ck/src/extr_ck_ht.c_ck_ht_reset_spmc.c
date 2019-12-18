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
struct ck_ht_map {int /*<<< orphan*/  capacity; } ;
struct ck_ht {struct ck_ht_map* map; } ;

/* Variables and functions */
 int ck_ht_reset_size_spmc (struct ck_ht*,int /*<<< orphan*/ ) ; 

bool
ck_ht_reset_spmc(struct ck_ht *table)
{
	struct ck_ht_map *map = table->map;

	return ck_ht_reset_size_spmc(table, map->capacity);
}