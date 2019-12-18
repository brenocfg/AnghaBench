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
struct ck_hs_stat {int /*<<< orphan*/  probe_maximum; int /*<<< orphan*/  tombstones; int /*<<< orphan*/  n_entries; } ;
struct ck_hs_map {int /*<<< orphan*/  probe_maximum; int /*<<< orphan*/  tombstones; int /*<<< orphan*/  n_entries; } ;
struct ck_hs {struct ck_hs_map* map; } ;

/* Variables and functions */

void
ck_hs_stat(struct ck_hs *hs, struct ck_hs_stat *st)
{
	struct ck_hs_map *map = hs->map;

	st->n_entries = map->n_entries;
	st->tombstones = map->tombstones;
	st->probe_maximum = map->probe_maximum;
	return;
}