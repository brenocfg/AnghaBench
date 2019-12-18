#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_size_t ;
typedef  int vm_paddr_t ;
typedef  int vm_offset_t ;
struct TYPE_7__ {int pa; } ;
struct pvo_entry {TYPE_3__ pvo_pte; } ;
typedef  int /*<<< orphan*/ * pmap_t ;
typedef  int /*<<< orphan*/  mmu_t ;
struct TYPE_8__ {TYPE_2__* td_proc; } ;
struct TYPE_6__ {TYPE_1__* p_vmspace; } ;
struct TYPE_5__ {int /*<<< orphan*/  vm_pmap; } ;

/* Variables and functions */
 int ADDR_POFF ; 
 int LPTE_I ; 
 int LPTE_RPGN ; 
 scalar_t__ MIN (int,scalar_t__) ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ *) ; 
 scalar_t__ __predict_false (int /*<<< orphan*/ ) ; 
 TYPE_4__* curthread ; 
 struct pvo_entry* moea64_pvo_find_va (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  moea64_syncicache (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,scalar_t__) ; 
 int round_page (int) ; 

void
moea64_sync_icache(mmu_t mmu, pmap_t pm, vm_offset_t va, vm_size_t sz)
{
	struct pvo_entry *pvo;
	vm_offset_t lim;
	vm_paddr_t pa;
	vm_size_t len;

	if (__predict_false(pm == NULL))
		pm = &curthread->td_proc->p_vmspace->vm_pmap;

	PMAP_LOCK(pm);
	while (sz > 0) {
		lim = round_page(va+1);
		len = MIN(lim - va, sz);
		pvo = moea64_pvo_find_va(pm, va & ~ADDR_POFF);
		if (pvo != NULL && !(pvo->pvo_pte.pa & LPTE_I)) {
			pa = (pvo->pvo_pte.pa & LPTE_RPGN) | (va & ADDR_POFF);
			moea64_syncicache(mmu, pm, va, pa, len);
		}
		va += len;
		sz -= len;
	}
	PMAP_UNLOCK(pm);
}