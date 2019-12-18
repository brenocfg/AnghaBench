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
typedef  int /*<<< orphan*/  uint16_t ;
struct ck_ht_map {int capacity; size_t mask; size_t probe_limit; int /*<<< orphan*/  n_entries; struct ck_ht_entry* entries; } ;
struct ck_ht_hash {size_t value; } ;
struct ck_ht_entry {scalar_t__ key; size_t hash; } ;
struct ck_ht {int mode; int /*<<< orphan*/  m; struct ck_ht_map* map; int /*<<< orphan*/  seed; int /*<<< orphan*/  (* h ) (struct ck_ht_hash*,scalar_t__*,int,int /*<<< orphan*/ ) ;} ;
typedef  int CK_HT_TYPE ;

/* Variables and functions */
 scalar_t__ CK_CC_LIKELY (int) ; 
 size_t CK_HT_BUCKET_LENGTH ; 
 scalar_t__ CK_HT_KEY_EMPTY ; 
 scalar_t__ CK_HT_KEY_TOMBSTONE ; 
 int CK_HT_MODE_BYTESTRING ; 
 int CK_MD_CACHELINE ; 
 void* ck_ht_entry_key (struct ck_ht_entry*) ; 
 int /*<<< orphan*/  ck_ht_entry_key_length (struct ck_ht_entry*) ; 
 int /*<<< orphan*/  ck_ht_map_bound_set (struct ck_ht_map*,struct ck_ht_hash,int) ; 
 struct ck_ht_map* ck_ht_map_create (struct ck_ht*,int) ; 
 int /*<<< orphan*/  ck_ht_map_destroy (int /*<<< orphan*/ ,struct ck_ht_map*,int) ; 
 size_t ck_ht_map_probe_next (struct ck_ht_map*,size_t,struct ck_ht_hash,int) ; 
 int /*<<< orphan*/  ck_pr_fence_store () ; 
 int /*<<< orphan*/  ck_pr_store_ptr_unsafe (struct ck_ht_map**,struct ck_ht_map*) ; 
 int /*<<< orphan*/  stub1 (struct ck_ht_hash*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct ck_ht_hash*,scalar_t__*,int,int /*<<< orphan*/ ) ; 

bool
ck_ht_grow_spmc(struct ck_ht *table, CK_HT_TYPE capacity)
{
	struct ck_ht_map *map, *update;
	struct ck_ht_entry *bucket, *previous;
	struct ck_ht_hash h;
	size_t k, i, j, offset;
	CK_HT_TYPE probes;

restart:
	map = table->map;

	if (map->capacity >= capacity)
		return false;

	update = ck_ht_map_create(table, capacity);
	if (update == NULL)
		return false;

	for (k = 0; k < map->capacity; k++) {
		previous = &map->entries[k];

		if (previous->key == CK_HT_KEY_EMPTY || previous->key == CK_HT_KEY_TOMBSTONE)
			continue;

		if (table->mode & CK_HT_MODE_BYTESTRING) {
#ifdef CK_HT_PP
			void *key;
			uint16_t key_length;

			key = ck_ht_entry_key(previous);
			key_length = ck_ht_entry_key_length(previous);
#endif

#ifndef CK_HT_PP
			h.value = previous->hash;
#else
			table->h(&h, key, key_length, table->seed);
#endif
		} else {
#ifndef CK_HT_PP
			h.value = previous->hash;
#else
			table->h(&h, &previous->key, sizeof(previous->key), table->seed);
#endif
		}

		offset = h.value & update->mask;
		probes = 0;

		for (i = 0; i < update->probe_limit; i++) {
			bucket = (void *)((uintptr_t)(update->entries + offset) & ~(CK_MD_CACHELINE - 1));

			for (j = 0; j < CK_HT_BUCKET_LENGTH; j++) {
				struct ck_ht_entry *cursor = bucket + ((j + offset) & (CK_HT_BUCKET_LENGTH - 1));

				probes++;
				if (CK_CC_LIKELY(cursor->key == CK_HT_KEY_EMPTY)) {
					*cursor = *previous;
					update->n_entries++;
					ck_ht_map_bound_set(update, h, probes);
					break;
				}
			}

			if (j < CK_HT_BUCKET_LENGTH)
				break;

			offset = ck_ht_map_probe_next(update, offset, h, probes);
		}

		if (i == update->probe_limit) {
			/*
			 * We have hit the probe limit, the map needs to be even
			 * larger.
			 */
			ck_ht_map_destroy(table->m, update, false);
			capacity <<= 1;
			goto restart;
		}
	}

	ck_pr_fence_store();
	ck_pr_store_ptr_unsafe(&table->map, update);
	ck_ht_map_destroy(table->m, map, true);
	return true;
}