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
struct pt_section {int dummy; } ;
struct pt_mapped_section {int /*<<< orphan*/ * section; } ;
struct pt_msec_cache {int isid; struct pt_mapped_section msec; } ;
struct pt_image {int dummy; } ;
struct pt_asid {int dummy; } ;

/* Variables and functions */
 int pt_image_find (struct pt_image*,struct pt_mapped_section*,struct pt_asid const*,int /*<<< orphan*/ ) ; 
 int pt_msec_cache_invalidate (struct pt_msec_cache*) ; 
 struct pt_section* pt_msec_section (struct pt_mapped_section*) ; 
 int pt_section_map (struct pt_section*) ; 
 int /*<<< orphan*/  pt_section_put (struct pt_section*) ; 
 int pte_internal ; 

int pt_msec_cache_fill(struct pt_msec_cache *cache,
		       const struct pt_mapped_section **pmsec,
		       struct pt_image *image, const struct pt_asid *asid,
		       uint64_t vaddr)
{
	struct pt_mapped_section *msec;
	struct pt_section *section;
	int errcode, isid;

	if (!cache || !pmsec)
		return -pte_internal;

	errcode = pt_msec_cache_invalidate(cache);
	if (errcode < 0)
		return errcode;

	msec = &cache->msec;

	isid = pt_image_find(image, msec, asid, vaddr);
	if (isid < 0)
		return isid;

	section = pt_msec_section(msec);

	errcode = pt_section_map(section);
	if (errcode < 0) {
		(void) pt_section_put(section);
		msec->section = NULL;

		return errcode;
	}

	*pmsec = msec;

	cache->isid = isid;

	return isid;
}