#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
struct tte {int dummy; } ;
typedef  TYPE_1__* pmap_t ;
struct TYPE_12__ {int /*<<< orphan*/ * pm_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR3 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  KTR_PMAP ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PMAP_LOCK (TYPE_1__*) ; 
 scalar_t__ PMAP_REMOVE_DONE (TYPE_1__*) ; 
 scalar_t__ PMAP_TSB_THRESH ; 
 int /*<<< orphan*/  PMAP_UNLOCK (TYPE_1__*) ; 
 size_t curcpu ; 
 int /*<<< orphan*/  pmap_remove_tte (TYPE_1__*,int /*<<< orphan*/ *,struct tte*,scalar_t__) ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tlb_context_demap (TYPE_1__*) ; 
 int /*<<< orphan*/  tlb_range_demap (TYPE_1__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  tsb_foreach (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/  (*) (TYPE_1__*,int /*<<< orphan*/ *,struct tte*,scalar_t__)) ; 
 struct tte* tsb_tte_lookup (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  tte_list_global_lock ; 

void
pmap_remove(pmap_t pm, vm_offset_t start, vm_offset_t end)
{
	struct tte *tp;
	vm_offset_t va;

	CTR3(KTR_PMAP, "pmap_remove: ctx=%#lx start=%#lx end=%#lx",
	    pm->pm_context[curcpu], start, end);
	if (PMAP_REMOVE_DONE(pm))
		return;
	rw_wlock(&tte_list_global_lock);
	PMAP_LOCK(pm);
	if (end - start > PMAP_TSB_THRESH) {
		tsb_foreach(pm, NULL, start, end, pmap_remove_tte);
		tlb_context_demap(pm);
	} else {
		for (va = start; va < end; va += PAGE_SIZE)
			if ((tp = tsb_tte_lookup(pm, va)) != NULL &&
			    !pmap_remove_tte(pm, NULL, tp, va))
				break;
		tlb_range_demap(pm, start, end - 1);
	}
	PMAP_UNLOCK(pm);
	rw_wunlock(&tte_list_global_lock);
}