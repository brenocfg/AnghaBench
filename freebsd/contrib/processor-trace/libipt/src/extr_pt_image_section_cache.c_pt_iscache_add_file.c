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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct pt_section {int dummy; } ;
struct pt_iscache_entry {struct pt_section* section; int /*<<< orphan*/  laddr; } ;
struct pt_image_section_cache {int size; struct pt_iscache_entry* entries; } ;

/* Variables and functions */
 int isid_from_index (int /*<<< orphan*/ ) ; 
 int pt_iscache_add (struct pt_image_section_cache*,struct pt_section*,int /*<<< orphan*/ ) ; 
 int pt_iscache_find_section_locked (struct pt_image_section_cache*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pt_iscache_lock (struct pt_image_section_cache*) ; 
 int pt_iscache_unlock (struct pt_image_section_cache*) ; 
 int pt_mk_section (struct pt_section**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pt_section_get (struct pt_section*) ; 
 int pt_section_put (struct pt_section*) ; 
 int pte_invalid ; 

int pt_iscache_add_file(struct pt_image_section_cache *iscache,
			const char *filename, uint64_t offset, uint64_t size,
			uint64_t vaddr)
{
	struct pt_section *section;
	int errcode, match, isid;

	if (!iscache || !filename)
		return -pte_invalid;

	errcode = pt_iscache_lock(iscache);
	if (errcode < 0)
		return errcode;

	match = pt_iscache_find_section_locked(iscache, filename, offset,
					       size, vaddr);
	if (match < 0) {
		(void) pt_iscache_unlock(iscache);
		return match;
	}

	/* If we found a perfect match, we will share the existing entry.
	 *
	 * If we found a section, we need to grab a reference before we unlock.
	 *
	 * If we didn't find a matching section, we create a new section, which
	 * implicitly gives us a reference to it.
	 */
	if (match < iscache->size) {
		const struct pt_iscache_entry *entry;

		entry = &iscache->entries[match];
		if (entry->laddr == vaddr) {
			errcode = pt_iscache_unlock(iscache);
			if (errcode < 0)
				return errcode;

			return isid_from_index((uint16_t) match);
		}

		section = entry->section;

		errcode = pt_section_get(section);
		if (errcode < 0) {
			(void) pt_iscache_unlock(iscache);
			return errcode;
		}

		errcode = pt_iscache_unlock(iscache);
		if (errcode < 0) {
			(void) pt_section_put(section);
			return errcode;
		}
	} else {
		errcode = pt_iscache_unlock(iscache);
		if (errcode < 0)
			return errcode;

		section = NULL;
		errcode = pt_mk_section(&section, filename, offset, size);
		if (errcode < 0)
			return errcode;
	}

	/* We unlocked @iscache and hold a reference to @section. */
	isid = pt_iscache_add(iscache, section, vaddr);

	/* We grab a reference when we add the section.  Drop the one we
	 * obtained before.
	 */
	errcode = pt_section_put(section);
	if (errcode < 0)
		return errcode;

	return isid;
}