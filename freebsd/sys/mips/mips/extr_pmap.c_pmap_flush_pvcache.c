#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_page_t ;
typedef  TYPE_3__* pv_entry_t ;
struct TYPE_10__ {int /*<<< orphan*/  pv_va; } ;
struct TYPE_8__ {int /*<<< orphan*/  pv_list; } ;
struct TYPE_9__ {TYPE_1__ md; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 TYPE_3__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 TYPE_3__* TAILQ_NEXT (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_dcache_wbinv_range_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pv_list ; 

void
pmap_flush_pvcache(vm_page_t m)
{
	pv_entry_t pv;

	if (m != NULL) {
		for (pv = TAILQ_FIRST(&m->md.pv_list); pv;
		    pv = TAILQ_NEXT(pv, pv_list)) {
			mips_dcache_wbinv_range_index(pv->pv_va, PAGE_SIZE);
		}
	}
}