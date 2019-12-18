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
 char* pt_section_filename (struct pt_section const*) ; 
 scalar_t__ pt_section_offset (struct pt_section const*) ; 
 scalar_t__ pt_section_size (struct pt_section const*) ; 
 int pte_internal ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static int
pt_iscache_find_section_locked(const struct pt_image_section_cache *iscache,
			       const char *filename, uint64_t offset,
			       uint64_t size, uint64_t laddr)
{
	const struct pt_section *section;
	uint16_t idx, end;
	int match;

	if (!iscache || !filename)
		return -pte_internal;

	section = NULL;
	match = end = iscache->size;
	for (idx = 0; idx < end; ++idx) {
		const struct pt_iscache_entry *entry;
		const struct pt_section *sec;

		entry = &iscache->entries[idx];

		/* We do not zero-initialize the array - a NULL check is
		 * pointless.
		 */
		sec = entry->section;

		/* Avoid redundant match checks. */
		if (sec != section) {
			const char *sec_filename;

			/* We don't have duplicates.  Skip the check. */
			if (section)
				continue;

			if (offset != pt_section_offset(sec))
				continue;

			if (size != pt_section_size(sec))
				continue;

			sec_filename = pt_section_filename(sec);
			if (!sec_filename)
				return -pte_internal;

			if (strcmp(filename, sec_filename) != 0)
				continue;

			/* Use the cached section instead. */
			section = sec;
			match = idx;
		}

		/* If we didn't continue, @section == @sec and we have a match.
		 *
		 * If we also find a matching load address, we're done.
		 */
		if (laddr == entry->laddr)
			return idx;
	}

	return match;
}