#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct ck_ht_map {size_t mask; size_t probe_limit; int mode; scalar_t__ entries; } ;
struct ck_ht_entry {uintptr_t key; int value; int hash; } ;
struct TYPE_5__ {size_t value; } ;
typedef  TYPE_1__ ck_ht_hash_t ;
typedef  struct ck_ht_entry ck_ht_entry_t ;
typedef  scalar_t__ CK_HT_TYPE ;

/* Variables and functions */
 size_t CK_HT_BUCKET_LENGTH ; 
 uintptr_t CK_HT_KEY_EMPTY ; 
 int CK_HT_KEY_MASK ; 
 uintptr_t CK_HT_KEY_TOMBSTONE ; 
 int CK_HT_MODE_BYTESTRING ; 
 scalar_t__ CK_HT_TYPE_MAX ; 
 int CK_MD_CACHELINE ; 
 int CK_MD_VMA_BITS ; 
 void* ck_ht_entry_key (struct ck_ht_entry*) ; 
 int /*<<< orphan*/  ck_ht_entry_key_length (struct ck_ht_entry*) ; 
 scalar_t__ ck_ht_map_bound_get (struct ck_ht_map*,TYPE_1__) ; 
 size_t ck_ht_map_probe_next (struct ck_ht_map*,size_t,TYPE_1__,scalar_t__) ; 
 scalar_t__ memcmp (void*,void const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ck_ht_entry *
ck_ht_map_probe_wr(struct ck_ht_map *map,
    ck_ht_hash_t h,
    ck_ht_entry_t *snapshot,
    ck_ht_entry_t **available,
    const void *key,
    uint16_t key_length,
    CK_HT_TYPE *probe_limit,
    CK_HT_TYPE *probe_wr)
{
	struct ck_ht_entry *bucket, *cursor;
	struct ck_ht_entry *first = NULL;
	size_t offset, i, j;
	CK_HT_TYPE probes = 0;
	CK_HT_TYPE limit;

	if (probe_limit == NULL) {
		limit = ck_ht_map_bound_get(map, h);
	} else {
		limit = CK_HT_TYPE_MAX;
	}

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

			if (probes++ > limit)
				break;

			cursor = bucket + ((j + offset) & (CK_HT_BUCKET_LENGTH - 1));

			/*
			 * It is probably worth it to encapsulate probe state
			 * in order to prevent a complete reprobe sequence in
			 * the case of intermittent writers.
			 */
			if (cursor->key == CK_HT_KEY_TOMBSTONE) {
				if (first == NULL) {
					first = cursor;
					*probe_wr = probes;
				}

				continue;
			}

			if (cursor->key == CK_HT_KEY_EMPTY)
				goto leave;

			if (cursor->key == (uintptr_t)key)
				goto leave;

			if (map->mode & CK_HT_MODE_BYTESTRING) {
				void *pointer;

				/*
				 * Check memoized portion of hash value before
				 * expensive full-length comparison.
				 */
				k = ck_ht_entry_key_length(cursor);
				if (k != key_length)
					continue;

#ifdef CK_HT_PP
				if ((cursor->value >> CK_MD_VMA_BITS) != ((h.value >> 32) & CK_HT_KEY_MASK))
					continue;
#else
				if (cursor->hash != h.value)
					continue;
#endif

				pointer = ck_ht_entry_key(cursor);
				if (memcmp(pointer, key, key_length) == 0)
					goto leave;
			}
		}

		offset = ck_ht_map_probe_next(map, offset, h, probes);
	}

	cursor = NULL;

leave:
	if (probe_limit != NULL) {
		*probe_limit = probes;
	} else if (first == NULL) {
		*probe_wr = probes;
	}

	*available = first;

	if (cursor != NULL) {
		*snapshot = *cursor;
	}

	return cursor;
}