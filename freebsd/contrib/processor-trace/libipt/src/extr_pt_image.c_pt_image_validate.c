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
struct pt_section_list {int isid; int /*<<< orphan*/  section; } ;
struct pt_mapped_section {int dummy; } ;
struct pt_image {struct pt_section_list* sections; } ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ *,struct pt_mapped_section const*,int) ; 
 scalar_t__ pt_msec_begin (struct pt_mapped_section const*) ; 
 scalar_t__ pt_msec_end (struct pt_mapped_section const*) ; 
 int pte_internal ; 
 int pte_nomap ; 

int pt_image_validate(const struct pt_image *image,
		      const struct pt_mapped_section *usec, uint64_t vaddr,
		      int isid)
{
	const struct pt_section_list *slist;
	uint64_t begin, end;
	int status;

	if (!image || !usec)
		return -pte_internal;

	/* Check that @vaddr lies within @usec. */
	begin = pt_msec_begin(usec);
	end = pt_msec_end(usec);
	if (vaddr < begin || end <= vaddr)
		return -pte_nomap;

	/* We assume that @usec is a copy of the top of our stack and accept
	 * sporadic validation fails if it isn't, e.g. because it has moved
	 * down.
	 *
	 * A failed validation requires decoders to re-fetch the section so it
	 * only results in a (relatively small) performance loss.
	 */
	slist = image->sections;
	if (!slist)
		return -pte_nomap;

	if (slist->isid != isid)
		return -pte_nomap;

	status = memcmp(&slist->section, usec, sizeof(*usec));
	if (status)
		return -pte_nomap;

	return 0;
}