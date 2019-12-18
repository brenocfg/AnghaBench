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
struct pt_section {int dummy; } ;
struct pt_iscache_lru_entry {struct pt_iscache_lru_entry* next; struct pt_section* section; } ;
struct pt_image_section_cache {struct pt_iscache_lru_entry* lru; } ;

/* Variables and functions */
 int pt_isache_lru_new (struct pt_image_section_cache*,struct pt_section*) ; 
 int pte_internal ; 

__attribute__((used)) static int pt_iscache_lru_add(struct pt_image_section_cache *iscache,
			      struct pt_section *section)
{
	struct pt_iscache_lru_entry *lru, **pnext;

	if (!iscache)
		return -pte_internal;

	pnext = &iscache->lru;
	for (lru = *pnext; lru; pnext = &lru->next, lru = *pnext) {

		if (lru->section != section)
			continue;

		/* We found it in the cache.  Move it to the front. */
		*pnext = lru->next;
		lru->next = iscache->lru;
		iscache->lru = lru;

		return 0;
	}

	/* We didn't find it in the cache.  Add it. */
	return pt_isache_lru_new(iscache, section);
}