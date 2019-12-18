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
struct pt_section {scalar_t__ offset; scalar_t__ size; int /*<<< orphan*/  memsize; int /*<<< orphan*/  read; int /*<<< orphan*/  unmap; struct pt_sec_posix_mapping* mapping; } ;
struct pt_sec_posix_mapping {int /*<<< orphan*/ * end; int /*<<< orphan*/ * begin; scalar_t__ size; int /*<<< orphan*/ * base; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 scalar_t__ INT_MAX ; 
 int /*<<< orphan*/ * MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  PROT_READ ; 
 scalar_t__ SIZE_MAX ; 
 int /*<<< orphan*/  _SC_PAGESIZE ; 
 struct pt_sec_posix_mapping* malloc (int) ; 
 int /*<<< orphan*/ * mmap (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  pt_sec_posix_memsize ; 
 int /*<<< orphan*/  pt_sec_posix_read ; 
 int /*<<< orphan*/  pt_sec_posix_unmap ; 
 int pte_bad_config ; 
 int pte_internal ; 
 int pte_nomem ; 
 long sysconf (int /*<<< orphan*/ ) ; 

int pt_sec_posix_map(struct pt_section *section, int fd)
{
	struct pt_sec_posix_mapping *mapping;
	uint64_t offset, size, adjustment;
	uint8_t *base;
	long page_size;
	int errcode;

	if (!section)
		return -pte_internal;

	offset = section->offset;
	size = section->size;

	page_size = sysconf(_SC_PAGESIZE);
	if (page_size < 0)
		return -pte_bad_config;

	adjustment = offset % (uint64_t) page_size;

	offset -= adjustment;
	size += adjustment;

	/* The section is supposed to fit into the file so we shouldn't
	 * see any overflows, here.
	 */
	if (size < section->size)
		return -pte_internal;

	if (SIZE_MAX < size)
		return -pte_nomem;

	if (INT_MAX < offset)
		return -pte_nomem;

	base = mmap(NULL, (size_t) size, PROT_READ, MAP_SHARED, fd,
		    (off_t) offset);
	if (base == MAP_FAILED)
		return -pte_nomem;

	mapping = malloc(sizeof(*mapping));
	if (!mapping) {
		errcode = -pte_nomem;
		goto out_map;
	}

	mapping->base = base;
	mapping->size = size;
	mapping->begin = base + adjustment;
	mapping->end = base + size;

	section->mapping = mapping;
	section->unmap = pt_sec_posix_unmap;
	section->read = pt_sec_posix_read;
	section->memsize = pt_sec_posix_memsize;

	return 0;

out_map:
	munmap(base, (size_t) size);
	return errcode;
}