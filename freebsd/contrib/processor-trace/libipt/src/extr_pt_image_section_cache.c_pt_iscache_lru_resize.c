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
typedef  scalar_t__ uint64_t ;
struct pt_section {int dummy; } ;
struct pt_iscache_lru_entry {scalar_t__ size; struct pt_section* section; } ;
struct pt_image_section_cache {scalar_t__ limit; scalar_t__ used; struct pt_iscache_lru_entry* lru; } ;

/* Variables and functions */
 int pt_iscache_lru_add (struct pt_image_section_cache*,struct pt_section*) ; 
 int pte_internal ; 

__attribute__((used)) static int pt_iscache_lru_resize(struct pt_image_section_cache *iscache,
				 struct pt_section *section, uint64_t memsize)
{
	struct pt_iscache_lru_entry *lru;
	uint64_t oldsize, used;
	int status;

	if (!iscache)
		return -pte_internal;

	status = pt_iscache_lru_add(iscache, section);
	if (status < 0)
		return status;

	lru = iscache->lru;
	if (!lru) {
		if (status)
			return -pte_internal;
		return 0;
	}

	/* If @section is cached, it must be first.
	 *
	 * We may choose not to cache it, though, e.g. if it is too big.
	 */
	if (lru->section != section) {
		if (iscache->limit < memsize)
			return 0;

		return -pte_internal;
	}

	oldsize = lru->size;
	lru->size = memsize;

	/* If we need to prune anyway, we're done. */
	if (status)
		return status;

	used = iscache->used;
	used -= oldsize;
	used += memsize;

	iscache->used = used;

	return (iscache->limit < used) ? 1 : 0;
}