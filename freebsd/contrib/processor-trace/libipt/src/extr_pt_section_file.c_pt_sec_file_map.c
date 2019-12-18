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
struct pt_section {scalar_t__ offset; scalar_t__ size; int /*<<< orphan*/  memsize; int /*<<< orphan*/  read; int /*<<< orphan*/  unmap; struct pt_sec_file_mapping* mapping; } ;
struct pt_sec_file_mapping {long begin; long end; int /*<<< orphan*/ * file; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 int fmap_init (struct pt_sec_file_mapping*) ; 
 int /*<<< orphan*/  free (struct pt_sec_file_mapping*) ; 
 int fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long ftell (int /*<<< orphan*/ *) ; 
 struct pt_sec_file_mapping* malloc (int) ; 
 int /*<<< orphan*/  pt_sec_file_memsize ; 
 int /*<<< orphan*/  pt_sec_file_read ; 
 int /*<<< orphan*/  pt_sec_file_unmap ; 
 int pte_bad_image ; 
 int pte_internal ; 
 int pte_nomem ; 

int pt_sec_file_map(struct pt_section *section, FILE *file)
{
	struct pt_sec_file_mapping *mapping;
	uint64_t offset, size;
	long begin, end, fsize;
	int errcode;

	if (!section)
		return -pte_internal;

	mapping = section->mapping;
	if (mapping)
		return -pte_internal;

	offset = section->offset;
	size = section->size;

	begin = (long) offset;
	end = begin + (long) size;

	/* Check for overflows. */
	if ((uint64_t) begin != offset)
		return -pte_bad_image;

	if ((uint64_t) end != (offset + size))
		return -pte_bad_image;

	if (end < begin)
		return -pte_bad_image;

	/* Validate that the section lies within the file. */
	errcode = fseek(file, 0, SEEK_END);
	if (errcode)
		return -pte_bad_image;

	fsize = ftell(file);
	if (fsize < 0)
		return -pte_bad_image;

	if (fsize < end)
		return -pte_bad_image;

	mapping = malloc(sizeof(*mapping));
	if (!mapping)
		return -pte_nomem;

	errcode = fmap_init(mapping);
	if (errcode < 0)
		goto out_mem;

	mapping->file = file;
	mapping->begin = begin;
	mapping->end = end;

	section->mapping = mapping;
	section->unmap = pt_sec_file_unmap;
	section->read = pt_sec_file_read;
	section->memsize = pt_sec_file_memsize;

	return 0;

out_mem:
	free(mapping);
	return errcode;
}