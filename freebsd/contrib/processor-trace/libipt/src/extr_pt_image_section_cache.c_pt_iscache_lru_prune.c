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
typedef  unsigned long long uint64_t ;
struct pt_iscache_lru_entry {scalar_t__ size; struct pt_iscache_lru_entry* next; } ;
struct pt_image_section_cache {unsigned long long limit; scalar_t__ used; struct pt_iscache_lru_entry* lru; } ;

/* Variables and functions */
 int pte_internal ; 

__attribute__((used)) static int pt_iscache_lru_prune(struct pt_image_section_cache *iscache,
				struct pt_iscache_lru_entry **tail)
{
	struct pt_iscache_lru_entry *lru, **pnext;
	uint64_t limit, used;

	if (!iscache || !tail)
		return -pte_internal;

	limit = iscache->limit;
	used = 0ull;

	pnext = &iscache->lru;
	for (lru = *pnext; lru; pnext = &lru->next, lru = *pnext) {

		used += lru->size;
		if (used <= limit)
			continue;

		/* The cache got too big; prune it starting from @lru. */
		iscache->used = used - lru->size;
		*pnext = NULL;
		*tail = lru;

		return 0;
	}

	/* We shouldn't prune the cache unnecessarily. */
	return -pte_internal;
}