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
typedef  int vm_prot_t ;
typedef  scalar_t__ vm_offset_t ;
struct tte {int dummy; } ;
typedef  TYPE_1__* pmap_t ;
struct TYPE_12__ {int /*<<< orphan*/ * pm_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR4 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  KTR_PMAP ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PMAP_LOCK (TYPE_1__*) ; 
 scalar_t__ PMAP_TSB_THRESH ; 
 int /*<<< orphan*/  PMAP_UNLOCK (TYPE_1__*) ; 
 int VM_PROT_NONE ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 size_t curcpu ; 
 int /*<<< orphan*/  pmap_protect_tte (TYPE_1__*,int /*<<< orphan*/ *,struct tte*,scalar_t__) ; 
 int /*<<< orphan*/  pmap_remove (TYPE_1__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  tlb_context_demap (TYPE_1__*) ; 
 int /*<<< orphan*/  tlb_range_demap (TYPE_1__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  tsb_foreach (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/  (*) (TYPE_1__*,int /*<<< orphan*/ *,struct tte*,scalar_t__)) ; 
 struct tte* tsb_tte_lookup (TYPE_1__*,scalar_t__) ; 

void
pmap_protect(pmap_t pm, vm_offset_t sva, vm_offset_t eva, vm_prot_t prot)
{
	vm_offset_t va;
	struct tte *tp;

	CTR4(KTR_PMAP, "pmap_protect: ctx=%#lx sva=%#lx eva=%#lx prot=%#lx",
	    pm->pm_context[curcpu], sva, eva, prot);

	if ((prot & VM_PROT_READ) == VM_PROT_NONE) {
		pmap_remove(pm, sva, eva);
		return;
	}

	if (prot & VM_PROT_WRITE)
		return;

	PMAP_LOCK(pm);
	if (eva - sva > PMAP_TSB_THRESH) {
		tsb_foreach(pm, NULL, sva, eva, pmap_protect_tte);
		tlb_context_demap(pm);
	} else {
		for (va = sva; va < eva; va += PAGE_SIZE)
			if ((tp = tsb_tte_lookup(pm, va)) != NULL)
				pmap_protect_tte(pm, NULL, tp, va);
		tlb_range_demap(pm, sva, eva - 1);
	}
	PMAP_UNLOCK(pm);
}