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
struct pt_iscache_lru_entry {struct pt_iscache_lru_entry* next; scalar_t__ size; struct pt_section* section; } ;
struct pt_image_section_cache {scalar_t__ limit; scalar_t__ used; struct pt_iscache_lru_entry* lru; } ;

/* Variables and functions */
 struct pt_iscache_lru_entry* malloc (int) ; 
 int pt_section_map_share (struct pt_section*) ; 
 int pt_section_memsize (struct pt_section*,scalar_t__*) ; 
 int /*<<< orphan*/  pt_section_unmap (struct pt_section*) ; 
 int pte_internal ; 
 int pte_nomem ; 
 int pte_overflow ; 

__attribute__((used)) static int pt_isache_lru_new(struct pt_image_section_cache *iscache,
			     struct pt_section *section)
{
	struct pt_iscache_lru_entry *lru;
	uint64_t memsize, used, total, limit;
	int errcode;

	if (!iscache)
		return -pte_internal;

	errcode = pt_section_memsize(section, &memsize);
	if (errcode < 0)
		return errcode;

	/* Don't try to add the section if it is too big.  We'd prune it again
	 * together with all other sections in our cache.
	 */
	limit = iscache->limit;
	if (limit < memsize)
		return 0;

	errcode = pt_section_map_share(section);
	if (errcode < 0)
		return errcode;

	lru = malloc(sizeof(*lru));
	if (!lru) {
		(void) pt_section_unmap(section);
		return -pte_nomem;
	}

	lru->section = section;
	lru->size = memsize;

	lru->next = iscache->lru;
	iscache->lru = lru;

	used = iscache->used;
	total = used + memsize;
	if (total < used || total < memsize)
		return -pte_overflow;

	iscache->used = total;

	return (limit < total) ? 1 : 0;
}