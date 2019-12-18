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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct pt_section {struct pt_sec_file_mapping* mapping; } ;
struct pt_sec_file_mapping {long begin; int /*<<< orphan*/ * file; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int fmap_lock (struct pt_sec_file_mapping*) ; 
 int fmap_unlock (struct pt_sec_file_mapping*) ; 
 size_t fread (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int fseek (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 int pte_internal ; 
 int pte_nomap ; 

int pt_sec_file_read(const struct pt_section *section, uint8_t *buffer,
		     uint16_t size, uint64_t offset)
{
	struct pt_sec_file_mapping *mapping;
	FILE *file;
	long begin;
	size_t read;
	int errcode;

	if (!buffer || !section)
		return -pte_internal;

	mapping = section->mapping;
	if (!mapping)
		return -pte_internal;

	file = mapping->file;

	/* We already checked in pt_section_read() that the requested memory
	 * lies within the section's boundaries.
	 *
	 * And we checked that the file covers the entire section in
	 * pt_sec_file_map().  There's no need to check for overflows, again.
	 */
	begin = mapping->begin + (long) offset;

	errcode = fmap_lock(mapping);
	if (errcode < 0)
		return errcode;

	errcode = fseek(file, begin, SEEK_SET);
	if (errcode)
		goto out_unlock;

	read = fread(buffer, 1, size, file);

	errcode = fmap_unlock(mapping);
	if (errcode < 0)
		return errcode;

	return (int) read;

out_unlock:
	(void) fmap_unlock(mapping);
	return -pte_nomap;
}