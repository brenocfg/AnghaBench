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
struct ck_ht_map {int /*<<< orphan*/  deletions; } ;
struct ck_ht_entry {scalar_t__ key; } ;
struct ck_ht {int mode; int /*<<< orphan*/  map; } ;
typedef  int /*<<< orphan*/  ck_ht_hash_t ;
typedef  struct ck_ht_entry ck_ht_entry_t ;
typedef  scalar_t__ CK_HT_TYPE ;

/* Variables and functions */
 scalar_t__ CK_HT_KEY_EMPTY ; 
 int CK_HT_MODE_BYTESTRING ; 
 scalar_t__ CK_HT_TYPE_LOAD (int /*<<< orphan*/ *) ; 
 void* ck_ht_entry_key (struct ck_ht_entry*) ; 
 int ck_ht_entry_key_length (struct ck_ht_entry*) ; 
 struct ck_ht_entry* ck_ht_map_probe_rd (struct ck_ht_map*,int /*<<< orphan*/ ,struct ck_ht_entry*,void*,int) ; 
 struct ck_ht_map* ck_pr_load_ptr (int /*<<< orphan*/ *) ; 

bool
ck_ht_get_spmc(struct ck_ht *table,
    ck_ht_hash_t h,
    ck_ht_entry_t *entry)
{
	struct ck_ht_entry *candidate, snapshot;
	struct ck_ht_map *map;
	CK_HT_TYPE d, d_prime;

restart:
	map = ck_pr_load_ptr(&table->map);

	/*
	 * Platforms that cannot read key and key_length atomically must reprobe
	 * on the scan of any single entry.
	 */
	d = CK_HT_TYPE_LOAD(&map->deletions);

	if (table->mode & CK_HT_MODE_BYTESTRING) {
		candidate = ck_ht_map_probe_rd(map, h, &snapshot,
		    ck_ht_entry_key(entry), ck_ht_entry_key_length(entry));
	} else {
		candidate = ck_ht_map_probe_rd(map, h, &snapshot,
		    (void *)entry->key, sizeof(entry->key));
	}

	d_prime = CK_HT_TYPE_LOAD(&map->deletions);
	if (d != d_prime) {
		/*
		 * It is possible we have read (K, V'). Only valid states are
		 * (K, V), (K', V') and (T, V). Restart load operation in face
		 * of concurrent deletions or replacements.
		 */
		goto restart;
	}

	if (candidate == NULL || snapshot.key == CK_HT_KEY_EMPTY)
		return false;

	*entry = snapshot;
	return true;
}