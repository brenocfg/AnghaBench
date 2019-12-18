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
struct pt_image_section_cache {int nsecs; int /*<<< orphan*/ * laddr; struct pt_section** section; } ;

/* Variables and functions */
 int pt_section_get (struct pt_section*) ; 
 int pte_bad_image ; 
 int pte_internal ; 

int pt_iscache_lookup(struct pt_image_section_cache *iscache,
		      struct pt_section **section, uint64_t *laddr, int isid)
{
	if (!iscache || !section || !laddr)
		return -pte_internal;

	if (!isid || iscache->nsecs < isid)
		return -pte_bad_image;

	isid -= 1;

	*section = iscache->section[isid];
	*laddr = iscache->laddr[isid];

	return pt_section_get(*section);
}