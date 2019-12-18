#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
struct pmap_pkru_range {int /*<<< orphan*/  pkru_keyidx; } ;
typedef  int /*<<< orphan*/  pt_entry_t ;
typedef  TYPE_1__* pmap_t ;
struct TYPE_4__ {scalar_t__ pm_type; int /*<<< orphan*/  pm_pkru; } ;

/* Variables and functions */
 int CPUID_STDEXT2_PKU ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ PT_X86 ; 
 scalar_t__ VM_MAXUSER_ADDRESS ; 
 int /*<<< orphan*/  X86_PG_PKU (int /*<<< orphan*/ ) ; 
 int cpu_stdext_feature2 ; 
 struct pmap_pkru_range* rangeset_lookup (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static pt_entry_t
pmap_pkru_get(pmap_t pmap, vm_offset_t va)
{
	struct pmap_pkru_range *ppr;

	PMAP_LOCK_ASSERT(pmap, MA_OWNED);
	if (pmap->pm_type != PT_X86 ||
	    (cpu_stdext_feature2 & CPUID_STDEXT2_PKU) == 0 ||
	    va >= VM_MAXUSER_ADDRESS)
		return (0);
	ppr = rangeset_lookup(&pmap->pm_pkru, va);
	if (ppr != NULL)
		return (X86_PG_PKU(ppr->pkru_keyidx));
	return (0);
}