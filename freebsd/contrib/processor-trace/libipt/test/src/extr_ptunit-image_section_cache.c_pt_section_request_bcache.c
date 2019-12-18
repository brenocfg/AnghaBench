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
typedef  int uint64_t ;
struct pt_section {int bcsize; int size; struct pt_image_section_cache* iscache; } ;
struct pt_image_section_cache {int dummy; } ;

/* Variables and functions */
 int pt_iscache_notify_resize (struct pt_image_section_cache*,struct pt_section*,int) ; 
 int pt_section_lock (struct pt_section*) ; 
 int pt_section_lock_attach (struct pt_section*) ; 
 int pt_section_unlock (struct pt_section*) ; 
 int pt_section_unlock_attach (struct pt_section*) ; 
 int pte_internal ; 

int pt_section_request_bcache(struct pt_section *section)
{
	struct pt_image_section_cache *iscache;
	uint64_t memsize;
	int errcode;

	if (!section)
		return -pte_internal;

	errcode = pt_section_lock_attach(section);
	if (errcode < 0)
		return errcode;

	errcode = pt_section_lock(section);
	if (errcode < 0)
		goto out_alock;

	if (section->bcsize)
		goto out_lock;

	section->bcsize = section->size * 3;
	memsize = section->size + section->bcsize;

	errcode = pt_section_unlock(section);
	if (errcode < 0)
		goto out_alock;

	iscache = section->iscache;
	if (iscache) {
		errcode = pt_iscache_notify_resize(iscache, section, memsize);
		if (errcode < 0)
			goto out_alock;
	}

	return pt_section_unlock_attach(section);


out_lock:
	(void) pt_section_unlock(section);

out_alock:
	(void) pt_section_unlock_attach(section);
	return errcode;
}