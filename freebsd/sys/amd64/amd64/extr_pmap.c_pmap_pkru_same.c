#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
struct TYPE_5__ {scalar_t__ re_end; } ;
struct pmap_pkru_range {scalar_t__ pkru_keyidx; TYPE_1__ pkru_rs_el; } ;
typedef  TYPE_2__* pmap_t ;
struct TYPE_6__ {scalar_t__ pm_type; int /*<<< orphan*/  pm_pkru; } ;

/* Variables and functions */
 int CPUID_STDEXT2_PKU ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MPASS (int) ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ PT_X86 ; 
 scalar_t__ VM_MAXUSER_ADDRESS ; 
 int cpu_stdext_feature2 ; 
 struct pmap_pkru_range* rangeset_lookup (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static bool
pmap_pkru_same(pmap_t pmap, vm_offset_t sva, vm_offset_t eva)
{
	struct pmap_pkru_range *ppr, *prev_ppr;
	vm_offset_t va;

	PMAP_LOCK_ASSERT(pmap, MA_OWNED);
	if (pmap->pm_type != PT_X86 ||
	    (cpu_stdext_feature2 & CPUID_STDEXT2_PKU) == 0 ||
	    sva >= VM_MAXUSER_ADDRESS)
		return (true);
	MPASS(eva <= VM_MAXUSER_ADDRESS);
	for (va = sva, prev_ppr = NULL; va < eva;) {
		ppr = rangeset_lookup(&pmap->pm_pkru, va);
		if ((ppr == NULL) ^ (prev_ppr == NULL))
			return (false);
		if (ppr == NULL) {
			va += PAGE_SIZE;
			continue;
		}
		if (prev_ppr->pkru_keyidx != ppr->pkru_keyidx)
			return (false);
		va = ppr->pkru_rs_el.re_end;
	}
	return (true);
}