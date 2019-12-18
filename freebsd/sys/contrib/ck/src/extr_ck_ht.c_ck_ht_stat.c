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
struct ck_ht_stat {int /*<<< orphan*/  probe_maximum; int /*<<< orphan*/  n_entries; } ;
struct ck_ht_map {int /*<<< orphan*/  probe_maximum; int /*<<< orphan*/  n_entries; } ;
struct ck_ht {struct ck_ht_map* map; } ;

/* Variables and functions */

void
ck_ht_stat(struct ck_ht *table,
    struct ck_ht_stat *st)
{
	struct ck_ht_map *map = table->map;

	st->n_entries = map->n_entries;
	st->probe_maximum = map->probe_maximum;
	return;
}