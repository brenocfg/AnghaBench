#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_19__ ;

/* Type definitions */
typedef  int vm_prot_t ;
typedef  struct vm_page* vm_page_t ;
typedef  scalar_t__ vm_paddr_t ;
typedef  int vm_offset_t ;
typedef  int uint32_t ;
typedef  int u_int ;
struct TYPE_27__ {int pvh_attrs; scalar_t__ pv_memattr; int pv_kva; int /*<<< orphan*/  pv_list; } ;
struct vm_page {int oflags; TYPE_3__ md; int /*<<< orphan*/  object; } ;
struct pv_entry {int pv_flags; } ;
struct l2_bucket {int* l2b_kva; int l2b_phys; int /*<<< orphan*/  l2b_occupancy; } ;
typedef  int pt_entry_t ;
typedef  TYPE_4__* pmap_t ;
typedef  int pd_entry_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_29__ {scalar_t__ pv_pa; } ;
struct TYPE_25__ {int /*<<< orphan*/  resident_count; } ;
struct TYPE_28__ {int /*<<< orphan*/  pm_domain; TYPE_2__* pm_l1; TYPE_1__ pm_stats; } ;
struct TYPE_26__ {int* l1_kva; } ;
struct TYPE_24__ {int clean_sva; int clean_eva; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int KERN_RESOURCE_SHORTAGE ; 
 int KERN_SUCCESS ; 
 int L1_C_DOM (int /*<<< orphan*/ ) ; 
 int L1_C_PROTO ; 
 size_t L1_IDX (int) ; 
 int L2_S_PROTO ; 
 int L2_S_PROT_U ; 
 int L2_S_PROT_W ; 
 int L2_TYPE_INV ; 
 int L2_TYPE_MASK ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PDEBUG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGA_REFERENCED ; 
 int /*<<< orphan*/  PGA_WRITEABLE ; 
 struct vm_page* PHYS_TO_VM_PAGE (scalar_t__) ; 
 int /*<<< orphan*/  PMAP_ASSERT_LOCKED (TYPE_4__*) ; 
 int PMAP_ENTER_NOSLEEP ; 
 int PMAP_ENTER_QUICK_LOCKED ; 
 int PMAP_ENTER_WIRED ; 
 int /*<<< orphan*/  PMAP_LOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  PTE_SYNC (int*) ; 
 int PVF_EXEC ; 
 int PVF_MOD ; 
 int PVF_NC ; 
 int PVF_REF ; 
 int PVF_UNMAN ; 
 int PVF_WIRED ; 
 int PVF_WRITE ; 
 scalar_t__ PV_BEEN_EXECD (int) ; 
 scalar_t__ PV_BEEN_REFD (int) ; 
 int /*<<< orphan*/  RA_WLOCKED ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ VM_MEMATTR_UNCACHEABLE ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_LOCKED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_PAGE_OBJECT_BUSY_ASSERT (struct vm_page*) ; 
 scalar_t__ VM_PAGE_TO_PHYS (struct vm_page*) ; 
 int VM_PROT_ALL ; 
 int VM_PROT_EXECUTE ; 
 int VM_PROT_WRITE ; 
 int VPO_UNMANAGED ; 
 int /*<<< orphan*/  cpu_dcache_wb_range (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_l2cache_wb_range (int,int /*<<< orphan*/ ) ; 
 TYPE_4__* kernel_pmap ; 
 TYPE_19__ kmi ; 
 size_t l2pte_index (int) ; 
 scalar_t__ l2pte_pa (int) ; 
 scalar_t__ l2pte_valid (int) ; 
 struct l2_bucket* pmap_alloc_l2_bucket (TYPE_4__*,int) ; 
 int /*<<< orphan*/  pmap_dcache_wb_range (TYPE_4__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmap_enter_pv (struct vm_page*,struct pv_entry*,TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  pmap_fix_cache (struct vm_page*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  pmap_free_pv_entry (struct pv_entry*) ; 
 struct l2_bucket* pmap_get_l2_bucket (TYPE_4__*,int) ; 
 struct pv_entry* pmap_get_pv_entry () ; 
 struct l2_bucket* pmap_grow_l2_bucket (TYPE_4__*,int) ; 
 int /*<<< orphan*/  pmap_idcache_wbinv_range (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ pmap_is_current (TYPE_4__*) ; 
 int pmap_modify_pv (struct vm_page*,TYPE_4__*,int,int,int) ; 
 struct pv_entry* pmap_remove_pv (struct vm_page*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  pmap_tlb_flushD_SE (TYPE_4__*,int) ; 
 int /*<<< orphan*/  pmap_tlb_flushID_SE (TYPE_4__*,int) ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int,int) ; 
 int pte_l2_s_cache_mode ; 
 int /*<<< orphan*/  pvh_global_lock ; 
 int /*<<< orphan*/  rw_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 
 TYPE_5__ systempage ; 
 int vector_page ; 
 int /*<<< orphan*/  vm_page_aflag_set (struct vm_page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_dirty (struct vm_page*) ; 
 int /*<<< orphan*/  vm_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pmap_enter_locked(pmap_t pmap, vm_offset_t va, vm_page_t m, vm_prot_t prot,
    u_int flags)
{
	struct l2_bucket *l2b = NULL;
	struct vm_page *opg;
	struct pv_entry *pve = NULL;
	pt_entry_t *ptep, npte, opte;
	u_int nflags;
	u_int oflags;
	vm_paddr_t pa;

	PMAP_ASSERT_LOCKED(pmap);
	rw_assert(&pvh_global_lock, RA_WLOCKED);
	if (va == vector_page) {
		pa = systempage.pv_pa;
		m = NULL;
	} else {
		if ((m->oflags & VPO_UNMANAGED) == 0) {
			if ((flags & PMAP_ENTER_QUICK_LOCKED) == 0)
				VM_PAGE_OBJECT_BUSY_ASSERT(m);
			else
				VM_OBJECT_ASSERT_LOCKED(m->object);
		}
		pa = VM_PAGE_TO_PHYS(m);
	}
	nflags = 0;
	if (prot & VM_PROT_WRITE)
		nflags |= PVF_WRITE;
	if (prot & VM_PROT_EXECUTE)
		nflags |= PVF_EXEC;
	if ((flags & PMAP_ENTER_WIRED) != 0)
		nflags |= PVF_WIRED;
	PDEBUG(1, printf("pmap_enter: pmap = %08x, va = %08x, m = %08x, prot = %x, "
	    "flags = %x\n", (uint32_t) pmap, va, (uint32_t) m, prot, flags));

	if (pmap == kernel_pmap) {
		l2b = pmap_get_l2_bucket(pmap, va);
		if (l2b == NULL)
			l2b = pmap_grow_l2_bucket(pmap, va);
	} else {
do_l2b_alloc:
		l2b = pmap_alloc_l2_bucket(pmap, va);
		if (l2b == NULL) {
			if ((flags & PMAP_ENTER_NOSLEEP) == 0) {
				PMAP_UNLOCK(pmap);
				rw_wunlock(&pvh_global_lock);
				vm_wait(NULL);
				rw_wlock(&pvh_global_lock);
				PMAP_LOCK(pmap);
				goto do_l2b_alloc;
			}
			return (KERN_RESOURCE_SHORTAGE);
		}
	}

	ptep = &l2b->l2b_kva[l2pte_index(va)];

	opte = *ptep;
	npte = pa;
	oflags = 0;
	if (opte) {
		/*
		 * There is already a mapping at this address.
		 * If the physical address is different, lookup the
		 * vm_page.
		 */
		if (l2pte_pa(opte) != pa)
			opg = PHYS_TO_VM_PAGE(l2pte_pa(opte));
		else
			opg = m;
	} else
		opg = NULL;

	if ((prot & (VM_PROT_ALL)) ||
	    (!m || m->md.pvh_attrs & PVF_REF)) {
		/*
		 * - The access type indicates that we don't need
		 *   to do referenced emulation.
		 * OR
		 * - The physical page has already been referenced
		 *   so no need to re-do referenced emulation here.
		 */
		npte |= L2_S_PROTO;

		nflags |= PVF_REF;

		if (m && ((prot & VM_PROT_WRITE) != 0 ||
		    (m->md.pvh_attrs & PVF_MOD))) {
			/*
			 * This is a writable mapping, and the
			 * page's mod state indicates it has
			 * already been modified. Make it
			 * writable from the outset.
			 */
			nflags |= PVF_MOD;
			if (!(m->md.pvh_attrs & PVF_MOD))
				vm_page_dirty(m);
		}
		if (m && opte)
			vm_page_aflag_set(m, PGA_REFERENCED);
	} else {
		/*
		 * Need to do page referenced emulation.
		 */
		npte |= L2_TYPE_INV;
	}

	if (prot & VM_PROT_WRITE) {
		npte |= L2_S_PROT_W;
		if (m != NULL &&
		    (m->oflags & VPO_UNMANAGED) == 0)
			vm_page_aflag_set(m, PGA_WRITEABLE);
	}
	if (m->md.pv_memattr != VM_MEMATTR_UNCACHEABLE)
		npte |= pte_l2_s_cache_mode;
	if (m && m == opg) {
		/*
		 * We're changing the attrs of an existing mapping.
		 */
		oflags = pmap_modify_pv(m, pmap, va,
		    PVF_WRITE | PVF_EXEC | PVF_WIRED |
		    PVF_MOD | PVF_REF, nflags);

		/*
		 * We may need to flush the cache if we're
		 * doing rw-ro...
		 */
		if (pmap_is_current(pmap) &&
		    (oflags & PVF_NC) == 0 &&
		    (opte & L2_S_PROT_W) != 0 &&
		    (prot & VM_PROT_WRITE) == 0 &&
		    (opte & L2_TYPE_MASK) != L2_TYPE_INV) {
			cpu_dcache_wb_range(va, PAGE_SIZE);
			cpu_l2cache_wb_range(va, PAGE_SIZE);
		}
	} else {
		/*
		 * New mapping, or changing the backing page
		 * of an existing mapping.
		 */
		if (opg) {
			/*
			 * Replacing an existing mapping with a new one.
			 * It is part of our managed memory so we
			 * must remove it from the PV list
			 */
			if ((pve = pmap_remove_pv(opg, pmap, va))) {

			/* note for patch: the oflags/invalidation was moved
			 * because PG_FICTITIOUS pages could free the pve
			 */
			    oflags = pve->pv_flags;
			/*
			 * If the old mapping was valid (ref/mod
			 * emulation creates 'invalid' mappings
			 * initially) then make sure to frob
			 * the cache.
			 */
			    if ((oflags & PVF_NC) == 0 && l2pte_valid(opte)) {
				if (PV_BEEN_EXECD(oflags)) {
					pmap_idcache_wbinv_range(pmap, va,
					    PAGE_SIZE);
				} else
					if (PV_BEEN_REFD(oflags)) {
						pmap_dcache_wb_range(pmap, va,
						    PAGE_SIZE, TRUE,
						    (oflags & PVF_WRITE) == 0);
					}
			    }

			/* free/allocate a pv_entry for UNMANAGED pages if
			 * this physical page is not/is already mapped.
			 */

			    if (m && (m->oflags & VPO_UNMANAGED) &&
				  !m->md.pv_kva &&
				 TAILQ_EMPTY(&m->md.pv_list)) {
				pmap_free_pv_entry(pve);
				pve = NULL;
			    }
			} else if (m &&
				 (!(m->oflags & VPO_UNMANAGED) || m->md.pv_kva ||
				  !TAILQ_EMPTY(&m->md.pv_list)))
				pve = pmap_get_pv_entry();
		} else if (m &&
			   (!(m->oflags & VPO_UNMANAGED) || m->md.pv_kva ||
			   !TAILQ_EMPTY(&m->md.pv_list)))
			pve = pmap_get_pv_entry();

		if (m) {
			if ((m->oflags & VPO_UNMANAGED)) {
				if (!TAILQ_EMPTY(&m->md.pv_list) ||
				    m->md.pv_kva) {
					KASSERT(pve != NULL, ("No pv"));
					nflags |= PVF_UNMAN;
					pmap_enter_pv(m, pve, pmap, va, nflags);
				} else
					m->md.pv_kva = va;
			} else {
				KASSERT(va < kmi.clean_sva ||
				    va >= kmi.clean_eva,
		("pmap_enter: managed mapping within the clean submap"));
 				KASSERT(pve != NULL, ("No pv"));
 				pmap_enter_pv(m, pve, pmap, va, nflags);
			}
		}
	}
	/*
	 * Make sure userland mappings get the right permissions
	 */
	if (pmap != kernel_pmap && va != vector_page) {
		npte |= L2_S_PROT_U;
	}

	/*
	 * Keep the stats up to date
	 */
	if (opte == 0) {
		l2b->l2b_occupancy++;
		pmap->pm_stats.resident_count++;
	}

	/*
	 * If this is just a wiring change, the two PTEs will be
	 * identical, so there's no need to update the page table.
	 */
	if (npte != opte) {
		boolean_t is_cached = pmap_is_current(pmap);

		*ptep = npte;
		if (is_cached) {
			/*
			 * We only need to frob the cache/tlb if this pmap
			 * is current
			 */
			PTE_SYNC(ptep);
			if (L1_IDX(va) != L1_IDX(vector_page) &&
			    l2pte_valid(npte)) {
				/*
				 * This mapping is likely to be accessed as
				 * soon as we return to userland. Fix up the
				 * L1 entry to avoid taking another
				 * page/domain fault.
				 */
				pd_entry_t *pl1pd, l1pd;

				pl1pd = &pmap->pm_l1->l1_kva[L1_IDX(va)];
				l1pd = l2b->l2b_phys | L1_C_DOM(pmap->pm_domain) |
				    L1_C_PROTO;
				if (*pl1pd != l1pd) {
					*pl1pd = l1pd;
					PTE_SYNC(pl1pd);
				}
			}
		}

		if (PV_BEEN_EXECD(oflags))
			pmap_tlb_flushID_SE(pmap, va);
		else if (PV_BEEN_REFD(oflags))
			pmap_tlb_flushD_SE(pmap, va);


		if (m)
			pmap_fix_cache(m, pmap, va);
	}
	return (KERN_SUCCESS);
}