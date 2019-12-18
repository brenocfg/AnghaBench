#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_page_t ;
typedef  size_t u_int ;
struct TYPE_4__ {scalar_t__* pt2_wirecount; } ;
struct TYPE_5__ {TYPE_1__ md; } ;

/* Variables and functions */
 size_t NPT2_IN_PG ; 

__attribute__((used)) static __inline void
pt2_wirecount_init(vm_page_t m)
{
	u_int i;

	/*
	 * Note: A page m is allocated with VM_ALLOC_WIRED flag and
	 *       m->ref_count should be already set correctly.
	 *       So, there is no need to set it again herein.
	 */
	for (i = 0; i < NPT2_IN_PG; i++)
		m->md.pt2_wirecount[i] = 0;
}