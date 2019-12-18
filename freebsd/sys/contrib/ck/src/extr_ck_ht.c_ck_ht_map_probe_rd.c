#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct ck_ht_map {size_t mask; size_t probe_limit; int mode; int /*<<< orphan*/  deletions; scalar_t__ entries; } ;
struct ck_ht_entry {int /*<<< orphan*/  value; int /*<<< orphan*/  hash; int /*<<< orphan*/  key_length; int /*<<< orphan*/  key; } ;
struct TYPE_9__ {size_t value; } ;
typedef  TYPE_1__ ck_ht_hash_t ;
struct TYPE_10__ {uintptr_t key; uintptr_t value; int hash; void* key_length; } ;
typedef  TYPE_2__ ck_ht_entry_t ;
typedef  scalar_t__ CK_HT_TYPE ;

/* Variables and functions */
 size_t CK_HT_BUCKET_LENGTH ; 
 uintptr_t CK_HT_KEY_EMPTY ; 
 int CK_HT_KEY_MASK ; 
 uintptr_t CK_HT_KEY_TOMBSTONE ; 
 int CK_HT_MODE_BYTESTRING ; 
 void* CK_HT_TYPE_LOAD (int /*<<< orphan*/ *) ; 
 int CK_MD_CACHELINE ; 
 int CK_MD_VMA_BITS ; 
 void* ck_ht_entry_key (TYPE_2__*) ; 
 int /*<<< orphan*/  ck_ht_entry_key_length (TYPE_2__*) ; 
 scalar_t__ ck_ht_map_bound_get (struct ck_ht_map*,TYPE_1__) ; 
 size_t ck_ht_map_probe_next (struct ck_ht_map*,size_t,TYPE_1__,scalar_t__) ; 
 int /*<<< orphan*/  ck_pr_fence_load () ; 
 scalar_t__ ck_pr_load_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (void*,void const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ck_ht_entry *
ck_ht_map_probe_rd(struct ck_ht_map *map,
    ck_ht_hash_t h,
    ck_ht_entry_t *snapshot,
    const void *key,
    uint16_t key_length)
{
	struct ck_ht_entry *bucket, *cursor;
	size_t offset, i, j;
	CK_HT_TYPE probes = 0;
	CK_HT_TYPE probe_maximum;

#ifndef CK_HT_PP
	CK_HT_TYPE d = 0;
	CK_HT_TYPE d_prime = 0;
retry:
#endif

	probe_maximum = ck_ht_map_bound_get(map, h);
	offset = h.value & map->mask;

	for (i = 0; i < map->probe_limit; i++) {
		/*
		 * Probe on a complete cache line first. Scan forward and wrap around to
		 * the beginning of the cache line. Only when the complete cache line has
		 * been scanned do we move on to the next row.
		 */
		bucket = (void *)((uintptr_t)(map->entries + offset) &
			     ~(CK_MD_CACHELINE - 1));

		for (j = 0; j < CK_HT_BUCKET_LENGTH; j++) {
			uint16_t k;

			if (probes++ > probe_maximum)
				return NULL;

			cursor = bucket + ((j + offset) & (CK_HT_BUCKET_LENGTH - 1));

#ifdef CK_HT_PP
			snapshot->key = (uintptr_t)ck_pr_load_ptr(&cursor->key);
			ck_pr_fence_load();
			snapshot->value = (uintptr_t)ck_pr_load_ptr(&cursor->value);
#else
			d = CK_HT_TYPE_LOAD(&map->deletions);
			snapshot->key = (uintptr_t)ck_pr_load_ptr(&cursor->key);
			ck_pr_fence_load();
			snapshot->key_length = CK_HT_TYPE_LOAD(&cursor->key_length);
			snapshot->hash = CK_HT_TYPE_LOAD(&cursor->hash);
			snapshot->value = (uintptr_t)ck_pr_load_ptr(&cursor->value);
#endif

			/*
			 * It is probably worth it to encapsulate probe state
			 * in order to prevent a complete reprobe sequence in
			 * the case of intermittent writers.
			 */
			if (snapshot->key == CK_HT_KEY_TOMBSTONE)
				continue;

			if (snapshot->key == CK_HT_KEY_EMPTY)
				goto leave;

			if (snapshot->key == (uintptr_t)key)
				goto leave;

			if (map->mode & CK_HT_MODE_BYTESTRING) {
				void *pointer;

				/*
				 * Check memoized portion of hash value before
				 * expensive full-length comparison.
				 */
				k = ck_ht_entry_key_length(snapshot);
				if (k != key_length)
					continue;
#ifdef CK_HT_PP
				if ((snapshot->value >> CK_MD_VMA_BITS) != ((h.value >> 32) & CK_HT_KEY_MASK))
					continue;
#else
				if (snapshot->hash != h.value)
					continue;

				d_prime = CK_HT_TYPE_LOAD(&map->deletions);

				/*
				 * It is possible that the slot was
				 * replaced, initiate a re-probe.
				 */
				if (d != d_prime)
					goto retry;
#endif

				pointer = ck_ht_entry_key(snapshot);
				if (memcmp(pointer, key, key_length) == 0)
					goto leave;
			}
		}

		offset = ck_ht_map_probe_next(map, offset, h, probes);
	}

	return NULL;

leave:
	return cursor;
}