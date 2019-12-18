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
typedef  scalar_t__ uint16_t ;
struct pt_section {scalar_t__ ucount; scalar_t__ acount; struct pt_image_section_cache* iscache; } ;
struct pt_image_section_cache {int dummy; } ;

/* Variables and functions */
 int pt_section_lock_attach (struct pt_section*) ; 
 int pt_section_unlock_attach (struct pt_section*) ; 
 int pte_internal ; 
 int pte_overflow ; 

int pt_section_attach(struct pt_section *section,
		      struct pt_image_section_cache *iscache)
{
	uint16_t acount, ucount;
	int errcode;

	if (!section || !iscache)
		return -pte_internal;

	errcode = pt_section_lock_attach(section);
	if (errcode < 0)
		return errcode;

	ucount = section->ucount;
	acount = section->acount;
	if (!acount) {
		if (section->iscache || !ucount)
			goto out_unlock;

		section->iscache = iscache;
		section->acount = 1;

		return pt_section_unlock_attach(section);
	}

	acount += 1;
	if (!acount) {
		(void) pt_section_unlock_attach(section);
		return -pte_overflow;
	}

	if (ucount < acount)
		goto out_unlock;

	if (section->iscache != iscache)
		goto out_unlock;

	section->acount = acount;

	return pt_section_unlock_attach(section);

 out_unlock:
	(void) pt_section_unlock_attach(section);
	return -pte_internal;
}