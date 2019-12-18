#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_20__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_15__ ;
typedef  struct TYPE_23__   TYPE_14__ ;

/* Type definitions */
typedef  int vm_prot_t ;
typedef  TYPE_2__* vm_page_t ;
typedef  int vm_offset_t ;
struct faultstate {TYPE_9__* first_object; TYPE_15__* entry; TYPE_14__* map; int /*<<< orphan*/  first_pindex; int /*<<< orphan*/ * vp; } ;
typedef  scalar_t__ boolean_t ;
struct TYPE_28__ {int flags; } ;
struct TYPE_27__ {int flags; size_t psind; } ;
struct TYPE_25__ {int /*<<< orphan*/  ru_minflt; } ;
struct TYPE_26__ {TYPE_1__ td_ru; } ;
struct TYPE_24__ {int start; scalar_t__ end; } ;
struct TYPE_23__ {int /*<<< orphan*/  pmap; } ;

/* Variables and functions */
 int KERN_FAILURE ; 
 int KERN_SUCCESS ; 
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 int OBJ_UNMANAGED ; 
 int /*<<< orphan*/  PFBAK ; 
 int /*<<< orphan*/  PFFOR ; 
 int PG_FICTITIOUS ; 
 int PMAP_ENTER_NOSLEEP ; 
 int PMAP_ENTER_WIRED ; 
 int PS_ALL_DIRTY ; 
 int PS_ALL_VALID ; 
 int PS_NONE_BUSY ; 
 int /*<<< orphan*/  VM_OBJECT_RUNLOCK (TYPE_9__*) ; 
 int VM_PAGE_TO_PHYS (TYPE_2__*) ; 
 int VM_PROT_WRITE ; 
 TYPE_20__* curthread ; 
 int* pagesizes ; 
 int pmap_enter (int /*<<< orphan*/ ,int,TYPE_2__*,int,int,int) ; 
 scalar_t__ pmap_ps_enabled (int /*<<< orphan*/ ) ; 
 int rounddown2 (int,int) ; 
 scalar_t__ roundup2 (int,int) ; 
 int /*<<< orphan*/  vm_fault_dirty (TYPE_15__*,TYPE_2__*,int,int,int,int) ; 
 int /*<<< orphan*/  vm_fault_prefault (struct faultstate*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vm_map_lookup_done (TYPE_14__*,TYPE_15__*) ; 
 int /*<<< orphan*/  vm_object_busy (TYPE_9__*) ; 
 int /*<<< orphan*/  vm_object_unbusy (TYPE_9__*) ; 
 int /*<<< orphan*/  vm_page_all_valid (TYPE_2__*) ; 
 scalar_t__ vm_page_busied (TYPE_2__*) ; 
 TYPE_2__* vm_page_lookup (TYPE_9__*,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_page_ps_test (TYPE_2__*,int,TYPE_2__*) ; 
 int /*<<< orphan*/  vm_page_wire (TYPE_2__*) ; 
 TYPE_2__* vm_reserv_to_superpage (TYPE_2__*) ; 

__attribute__((used)) static int
vm_fault_soft_fast(struct faultstate *fs, vm_offset_t vaddr, vm_prot_t prot,
    int fault_type, int fault_flags, boolean_t wired, vm_page_t *m_hold)
{
	vm_page_t m, m_map;
#if (defined(__aarch64__) || defined(__amd64__) || (defined(__arm__) && \
    __ARM_ARCH >= 6) || defined(__i386__) || defined(__riscv)) && \
    VM_NRESERVLEVEL > 0
	vm_page_t m_super;
	int flags;
#endif
	int psind, rv;

	MPASS(fs->vp == NULL);
	vm_object_busy(fs->first_object);
	m = vm_page_lookup(fs->first_object, fs->first_pindex);
	/* A busy page can be mapped for read|execute access. */
	if (m == NULL || ((prot & VM_PROT_WRITE) != 0 &&
	    vm_page_busied(m)) || !vm_page_all_valid(m)) {
		rv = KERN_FAILURE;
		goto out;
	}
	m_map = m;
	psind = 0;
#if (defined(__aarch64__) || defined(__amd64__) || (defined(__arm__) && \
    __ARM_ARCH >= 6) || defined(__i386__) || defined(__riscv)) && \
    VM_NRESERVLEVEL > 0
	if ((m->flags & PG_FICTITIOUS) == 0 &&
	    (m_super = vm_reserv_to_superpage(m)) != NULL &&
	    rounddown2(vaddr, pagesizes[m_super->psind]) >= fs->entry->start &&
	    roundup2(vaddr + 1, pagesizes[m_super->psind]) <= fs->entry->end &&
	    (vaddr & (pagesizes[m_super->psind] - 1)) == (VM_PAGE_TO_PHYS(m) &
	    (pagesizes[m_super->psind] - 1)) && !wired &&
	    pmap_ps_enabled(fs->map->pmap)) {
		flags = PS_ALL_VALID;
		if ((prot & VM_PROT_WRITE) != 0) {
			/*
			 * Create a superpage mapping allowing write access
			 * only if none of the constituent pages are busy and
			 * all of them are already dirty (except possibly for
			 * the page that was faulted on).
			 */
			flags |= PS_NONE_BUSY;
			if ((fs->first_object->flags & OBJ_UNMANAGED) == 0)
				flags |= PS_ALL_DIRTY;
		}
		if (vm_page_ps_test(m_super, flags, m)) {
			m_map = m_super;
			psind = m_super->psind;
			vaddr = rounddown2(vaddr, pagesizes[psind]);
			/* Preset the modified bit for dirty superpages. */
			if ((flags & PS_ALL_DIRTY) != 0)
				fault_type |= VM_PROT_WRITE;
		}
	}
#endif
	rv = pmap_enter(fs->map->pmap, vaddr, m_map, prot, fault_type |
	    PMAP_ENTER_NOSLEEP | (wired ? PMAP_ENTER_WIRED : 0), psind);
	if (rv != KERN_SUCCESS)
		goto out;
	if (m_hold != NULL) {
		*m_hold = m;
		vm_page_wire(m);
	}
	vm_fault_dirty(fs->entry, m, prot, fault_type, fault_flags, false);
	if (psind == 0 && !wired)
		vm_fault_prefault(fs, vaddr, PFBAK, PFFOR, true);
	VM_OBJECT_RUNLOCK(fs->first_object);
	vm_map_lookup_done(fs->map, fs->entry);
	curthread->td_ru.ru_minflt++;

out:
	vm_object_unbusy(fs->first_object);
	return (rv);
}