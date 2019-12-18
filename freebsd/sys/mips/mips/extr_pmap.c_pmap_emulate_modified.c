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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  pt_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;

/* Variables and functions */
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTE_D ; 
 int /*<<< orphan*/  PTE_MANAGED ; 
 int /*<<< orphan*/  PTE_RO ; 
 int /*<<< orphan*/  PTE_V ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/ * pmap_pte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pte_test (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlb_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
pmap_emulate_modified(pmap_t pmap, vm_offset_t va)
{
	pt_entry_t *pte;

	PMAP_LOCK(pmap);
	pte = pmap_pte(pmap, va);
	if (pte == NULL)
		panic("pmap_emulate_modified: can't find PTE");
#ifdef SMP
	/* It is possible that some other CPU changed m-bit */
	if (!pte_test(pte, PTE_V) || pte_test(pte, PTE_D)) {
		tlb_update(pmap, va, *pte);
		PMAP_UNLOCK(pmap);
		return (0);
	}
#else
	if (!pte_test(pte, PTE_V) || pte_test(pte, PTE_D))
		panic("pmap_emulate_modified: invalid pte");
#endif
	if (pte_test(pte, PTE_RO)) {
		PMAP_UNLOCK(pmap);
		return (1);
	}
	pte_set(pte, PTE_D);
	tlb_update(pmap, va, *pte);
	if (!pte_test(pte, PTE_MANAGED))
		panic("pmap_emulate_modified: unmanaged page");
	PMAP_UNLOCK(pmap);
	return (0);
}