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
struct pt_section {int /*<<< orphan*/ * memsize; int /*<<< orphan*/ * read; int /*<<< orphan*/ * unmap; struct pt_sec_posix_mapping* mapping; } ;
struct pt_sec_posix_mapping {scalar_t__ size; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct pt_sec_posix_mapping*) ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ ,size_t) ; 
 int pte_internal ; 

int pt_sec_posix_unmap(struct pt_section *section)
{
	struct pt_sec_posix_mapping *mapping;

	if (!section)
		return -pte_internal;

	mapping = section->mapping;
	if (!mapping || !section->unmap || !section->read || !section->memsize)
		return -pte_internal;

	section->mapping = NULL;
	section->unmap = NULL;
	section->read = NULL;
	section->memsize = NULL;

	munmap(mapping->base, (size_t) mapping->size);
	free(mapping);

	return 0;
}