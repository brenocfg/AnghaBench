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
typedef  size_t uint16_t ;
struct pt_section {int dummy; } ;
struct pt_iscache_entry {scalar_t__ laddr; struct pt_section* section; } ;
struct pt_image_section_cache {size_t size; struct pt_iscache_entry* entries; } ;

/* Variables and functions */
 int isid_from_index (size_t) ; 
 char* pt_section_filename (struct pt_section const*) ; 
 scalar_t__ pt_section_offset (struct pt_section const*) ; 
 scalar_t__ pt_section_size (struct pt_section const*) ; 
 int pte_internal ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static int pt_iscache_find_locked(struct pt_image_section_cache *iscache,
				  const char *filename, uint64_t offset,
				  uint64_t size, uint64_t laddr)
{
	uint16_t idx, end;

	if (!iscache || !filename)
		return -pte_internal;

	end = iscache->size;
	for (idx = 0; idx < end; ++idx) {
		const struct pt_iscache_entry *entry;
		const struct pt_section *section;
		const char *sec_filename;
		uint64_t sec_offset, sec_size;

		entry = &iscache->entries[idx];

		/* We do not zero-initialize the array - a NULL check is
		 * pointless.
		 */
		section = entry->section;
		sec_filename = pt_section_filename(section);
		sec_offset = pt_section_offset(section);
		sec_size = pt_section_size(section);

		if (entry->laddr != laddr)
			continue;

		if (sec_offset != offset)
			continue;

		if (sec_size != size)
			continue;

		/* We should not have a section without a filename. */
		if (!sec_filename)
			return -pte_internal;

		if (strcmp(sec_filename, filename) != 0)
			continue;

		return isid_from_index(idx);
	}

	return 0;
}