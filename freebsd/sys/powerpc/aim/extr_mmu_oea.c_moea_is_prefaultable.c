#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_offset_t ;
struct TYPE_3__ {int pte_hi; } ;
struct TYPE_4__ {TYPE_1__ pte; } ;
struct pvo_entry {TYPE_2__ pvo_pte; } ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int /*<<< orphan*/  mmu_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int ADDR_POFF ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int PTE_VALID ; 
 struct pvo_entry* moea_pvo_find_va (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

boolean_t
moea_is_prefaultable(mmu_t mmu, pmap_t pmap, vm_offset_t va)
{
	struct pvo_entry *pvo;
	boolean_t rv;

	PMAP_LOCK(pmap);
	pvo = moea_pvo_find_va(pmap, va & ~ADDR_POFF, NULL);
	rv = pvo == NULL || (pvo->pvo_pte.pte.pte_hi & PTE_VALID) == 0;
	PMAP_UNLOCK(pmap);
	return (rv);
}