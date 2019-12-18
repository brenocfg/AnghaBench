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
struct pt_section {int ucount; int acount; struct pt_image_section_cache* iscache; } ;
struct pt_image_section_cache {int dummy; } ;

/* Variables and functions */
 int pt_section_lock_attach (struct pt_section*) ; 
 int pt_section_unlock_attach (struct pt_section*) ; 
 int pte_internal ; 
 int pte_overflow ; 

int pt_section_attach(struct pt_section *section,
		      struct pt_image_section_cache *iscache)
{
	int errcode, ucount, acount;

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