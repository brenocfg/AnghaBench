#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_prot_t ;
typedef  TYPE_3__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int uint64_t ;
typedef  int u_int ;
struct pvo_head {int dummy; } ;
struct TYPE_12__ {int prot; int pa; } ;
struct pvo_entry {scalar_t__ pvo_pmap; TYPE_2__ pvo_pte; int /*<<< orphan*/  pvo_vaddr; } ;
typedef  scalar_t__ pmap_t ;
typedef  int /*<<< orphan*/  mmu_t ;
typedef  int /*<<< orphan*/  int8_t ;
struct TYPE_11__ {struct pvo_head mdpg_pvoh; } ;
struct TYPE_13__ {int oflags; int aflags; TYPE_1__ md; int /*<<< orphan*/  object; } ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int KERN_RESOURCE_SHORTAGE ; 
 int KERN_SUCCESS ; 
 int LPTE_G ; 
 int LPTE_I ; 
 int LPTE_NOEXEC ; 
 int /*<<< orphan*/  MOEA64_PTE_INSERT (int /*<<< orphan*/ ,struct pvo_entry*) ; 
 scalar_t__ MOEA64_PTE_SYNCH (int /*<<< orphan*/ ,struct pvo_entry*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PGA_EXECUTABLE ; 
 int PGA_WRITEABLE ; 
 int PMAP_ENTER_QUICK_LOCKED ; 
 int PMAP_ENTER_WIRED ; 
 int /*<<< orphan*/  PMAP_LOCK (scalar_t__) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (scalar_t__) ; 
 int /*<<< orphan*/  PVO_MANAGED ; 
 int /*<<< orphan*/  PVO_WIRED ; 
 int /*<<< orphan*/  PV_PAGE_LOCK (TYPE_3__*) ; 
 int /*<<< orphan*/  PV_PAGE_UNLOCK (TYPE_3__*) ; 
 int /*<<< orphan*/  STAT_MOEA64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_LOCKED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_PAGE_OBJECT_BUSY_ASSERT (TYPE_3__*) ; 
 int VM_PAGE_TO_PHYS (TYPE_3__*) ; 
 int VM_PROT_WRITE ; 
 int VPO_UNMANAGED ; 
 struct pvo_entry* alloc_pvo_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_pvo_entry (struct pvo_entry*) ; 
 int /*<<< orphan*/  init_pvo_entry (struct pvo_entry*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ kernel_pmap ; 
 int moea64_calc_wimg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  moea64_initialized ; 
 int /*<<< orphan*/  moea64_pte_overflow ; 
 int moea64_pvo_enter (int /*<<< orphan*/ ,struct pvo_entry*,struct pvo_head*,struct pvo_entry**) ; 
 int /*<<< orphan*/  moea64_pvo_remove_from_page (int /*<<< orphan*/ ,struct pvo_entry*) ; 
 int /*<<< orphan*/  moea64_pvo_remove_from_pmap (int /*<<< orphan*/ ,struct pvo_entry*) ; 
 int /*<<< orphan*/  moea64_syncicache (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ pmap_bootstrapped ; 
 int /*<<< orphan*/  pmap_page_get_memattr (TYPE_3__*) ; 
 int /*<<< orphan*/  vm_page_aflag_set (TYPE_3__*,int) ; 

int
moea64_enter(mmu_t mmu, pmap_t pmap, vm_offset_t va, vm_page_t m, 
    vm_prot_t prot, u_int flags, int8_t psind)
{
	struct		pvo_entry *pvo, *oldpvo;
	struct		pvo_head *pvo_head;
	uint64_t	pte_lo;
	int		error;

	if ((m->oflags & VPO_UNMANAGED) == 0) {
		if ((flags & PMAP_ENTER_QUICK_LOCKED) == 0)
			VM_PAGE_OBJECT_BUSY_ASSERT(m);
		else
			VM_OBJECT_ASSERT_LOCKED(m->object);
	}

	pvo = alloc_pvo_entry(0);
	if (pvo == NULL)
		return (KERN_RESOURCE_SHORTAGE);
	pvo->pvo_pmap = NULL; /* to be filled in later */
	pvo->pvo_pte.prot = prot;

	pte_lo = moea64_calc_wimg(VM_PAGE_TO_PHYS(m), pmap_page_get_memattr(m));
	pvo->pvo_pte.pa = VM_PAGE_TO_PHYS(m) | pte_lo;

	if ((flags & PMAP_ENTER_WIRED) != 0)
		pvo->pvo_vaddr |= PVO_WIRED;

	if ((m->oflags & VPO_UNMANAGED) != 0 || !moea64_initialized) {
		pvo_head = NULL;
	} else {
		pvo_head = &m->md.mdpg_pvoh;
		pvo->pvo_vaddr |= PVO_MANAGED;
	}

	PV_PAGE_LOCK(m);
	PMAP_LOCK(pmap);
	if (pvo->pvo_pmap == NULL)
		init_pvo_entry(pvo, pmap, va);
	if (prot & VM_PROT_WRITE)
		if (pmap_bootstrapped &&
		    (m->oflags & VPO_UNMANAGED) == 0)
			vm_page_aflag_set(m, PGA_WRITEABLE);

	error = moea64_pvo_enter(mmu, pvo, pvo_head, &oldpvo);
	if (error == EEXIST) {
		if (oldpvo->pvo_vaddr == pvo->pvo_vaddr &&
		    oldpvo->pvo_pte.pa == pvo->pvo_pte.pa &&
		    oldpvo->pvo_pte.prot == prot) {
			/* Identical mapping already exists */
			error = 0;

			/* If not in page table, reinsert it */
			if (MOEA64_PTE_SYNCH(mmu, oldpvo) < 0) {
				STAT_MOEA64(moea64_pte_overflow--);
				MOEA64_PTE_INSERT(mmu, oldpvo);
			}

			/* Then just clean up and go home */
			PV_PAGE_UNLOCK(m);
			PMAP_UNLOCK(pmap);
			free_pvo_entry(pvo);
			goto out;
		} else {
			/* Otherwise, need to kill it first */
			KASSERT(oldpvo->pvo_pmap == pmap, ("pmap of old "
			    "mapping does not match new mapping"));
			moea64_pvo_remove_from_pmap(mmu, oldpvo);
			moea64_pvo_enter(mmu, pvo, pvo_head, NULL);
		}
	}
	PMAP_UNLOCK(pmap);
	PV_PAGE_UNLOCK(m);

	/* Free any dead pages */
	if (error == EEXIST) {
		moea64_pvo_remove_from_page(mmu, oldpvo);
		free_pvo_entry(oldpvo);
	}

out:
	/*
	 * Flush the page from the instruction cache if this page is
	 * mapped executable and cacheable.
	 */
	if (pmap != kernel_pmap && !(m->aflags & PGA_EXECUTABLE) &&
	    (pte_lo & (LPTE_I | LPTE_G | LPTE_NOEXEC)) == 0) {
		vm_page_aflag_set(m, PGA_EXECUTABLE);
		moea64_syncicache(mmu, pmap, va, VM_PAGE_TO_PHYS(m), PAGE_SIZE);
	}
	return (KERN_SUCCESS);
}