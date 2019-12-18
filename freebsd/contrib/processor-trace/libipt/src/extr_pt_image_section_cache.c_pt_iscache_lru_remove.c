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
struct pt_iscache_lru_entry {struct pt_iscache_lru_entry* next; struct pt_section const* section; } ;
struct pt_image_section_cache {struct pt_iscache_lru_entry* lru; } ;

/* Variables and functions */
 int pt_iscache_lru_free (struct pt_iscache_lru_entry*) ; 
 int pte_internal ; 

__attribute__((used)) static int pt_iscache_lru_remove(struct pt_image_section_cache *iscache,
				 const struct pt_section *section)
{
	struct pt_iscache_lru_entry *lru, **pnext;

	if (!iscache)
		return -pte_internal;

	pnext = &iscache->lru;
	for (lru = *pnext; lru; pnext = &lru->next, lru = *pnext) {

		if (lru->section != section)
			continue;

		/* We found it in the cache.  Remove it. */
		*pnext = lru->next;
		lru->next = NULL;
		break;
	}

	return pt_iscache_lru_free(lru);
}