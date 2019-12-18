#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_size_t ;
typedef  scalar_t__ vm_pindex_t ;
typedef  TYPE_2__* vm_page_t ;
typedef  int vm_paddr_t ;
typedef  int vm_offset_t ;
typedef  TYPE_3__* vm_object_t ;
typedef  int pt_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int pd_entry_t ;
struct TYPE_15__ {scalar_t__ type; } ;
struct TYPE_13__ {int pat_mode; } ;
struct TYPE_14__ {scalar_t__ valid; scalar_t__ ref_count; TYPE_1__ md; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int NBPDR ; 
 scalar_t__ OBJT_DEVICE ; 
 scalar_t__ OBJT_SG ; 
 int PAGE_SIZE ; 
 int PG_PS ; 
 int PG_U ; 
 scalar_t__ PHYS_TO_DMAP (int) ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 TYPE_2__* TAILQ_NEXT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (TYPE_3__*) ; 
 scalar_t__ VM_PAGE_BITS_ALL ; 
 int VM_PAGE_TO_PHYS (TYPE_2__*) ; 
 int /*<<< orphan*/  atomic_add_long (int /*<<< orphan*/ *,int) ; 
 scalar_t__ atop (int) ; 
 int /*<<< orphan*/  listq ; 
 int /*<<< orphan*/  pde_store (int*,int) ; 
 int pmap_accessed_bit (int /*<<< orphan*/ ) ; 
 TYPE_2__* pmap_allocpde (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int pmap_cache_bits (int /*<<< orphan*/ ,int,int) ; 
 int pmap_modified_bit (int /*<<< orphan*/ ) ; 
 size_t pmap_pde_index (int) ; 
 int /*<<< orphan*/  pmap_pde_mappings ; 
 int /*<<< orphan*/  pmap_ps_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_resident_count_inc (int /*<<< orphan*/ ,int) ; 
 int pmap_rw_bit (int /*<<< orphan*/ ) ; 
 int pmap_valid_bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_populate (TYPE_3__*,scalar_t__,scalar_t__) ; 
 TYPE_2__* vm_page_lookup (TYPE_3__*,scalar_t__) ; 

void
pmap_object_init_pt(pmap_t pmap, vm_offset_t addr, vm_object_t object,
    vm_pindex_t pindex, vm_size_t size)
{
	pd_entry_t *pde;
	pt_entry_t PG_A, PG_M, PG_RW, PG_V;
	vm_paddr_t pa, ptepa;
	vm_page_t p, pdpg;
	int pat_mode;

	PG_A = pmap_accessed_bit(pmap);
	PG_M = pmap_modified_bit(pmap);
	PG_V = pmap_valid_bit(pmap);
	PG_RW = pmap_rw_bit(pmap);

	VM_OBJECT_ASSERT_WLOCKED(object);
	KASSERT(object->type == OBJT_DEVICE || object->type == OBJT_SG,
	    ("pmap_object_init_pt: non-device object"));
	if ((addr & (NBPDR - 1)) == 0 && (size & (NBPDR - 1)) == 0) {
		if (!pmap_ps_enabled(pmap))
			return;
		if (!vm_object_populate(object, pindex, pindex + atop(size)))
			return;
		p = vm_page_lookup(object, pindex);
		KASSERT(p->valid == VM_PAGE_BITS_ALL,
		    ("pmap_object_init_pt: invalid page %p", p));
		pat_mode = p->md.pat_mode;

		/*
		 * Abort the mapping if the first page is not physically
		 * aligned to a 2MB page boundary.
		 */
		ptepa = VM_PAGE_TO_PHYS(p);
		if (ptepa & (NBPDR - 1))
			return;

		/*
		 * Skip the first page.  Abort the mapping if the rest of
		 * the pages are not physically contiguous or have differing
		 * memory attributes.
		 */
		p = TAILQ_NEXT(p, listq);
		for (pa = ptepa + PAGE_SIZE; pa < ptepa + size;
		    pa += PAGE_SIZE) {
			KASSERT(p->valid == VM_PAGE_BITS_ALL,
			    ("pmap_object_init_pt: invalid page %p", p));
			if (pa != VM_PAGE_TO_PHYS(p) ||
			    pat_mode != p->md.pat_mode)
				return;
			p = TAILQ_NEXT(p, listq);
		}

		/*
		 * Map using 2MB pages.  Since "ptepa" is 2M aligned and
		 * "size" is a multiple of 2M, adding the PAT setting to "pa"
		 * will not affect the termination of this loop.
		 */ 
		PMAP_LOCK(pmap);
		for (pa = ptepa | pmap_cache_bits(pmap, pat_mode, 1);
		    pa < ptepa + size; pa += NBPDR) {
			pdpg = pmap_allocpde(pmap, addr, NULL);
			if (pdpg == NULL) {
				/*
				 * The creation of mappings below is only an
				 * optimization.  If a page directory page
				 * cannot be allocated without blocking,
				 * continue on to the next mapping rather than
				 * blocking.
				 */
				addr += NBPDR;
				continue;
			}
			pde = (pd_entry_t *)PHYS_TO_DMAP(VM_PAGE_TO_PHYS(pdpg));
			pde = &pde[pmap_pde_index(addr)];
			if ((*pde & PG_V) == 0) {
				pde_store(pde, pa | PG_PS | PG_M | PG_A |
				    PG_U | PG_RW | PG_V);
				pmap_resident_count_inc(pmap, NBPDR / PAGE_SIZE);
				atomic_add_long(&pmap_pde_mappings, 1);
			} else {
				/* Continue on if the PDE is already valid. */
				pdpg->ref_count--;
				KASSERT(pdpg->ref_count > 0,
				    ("pmap_object_init_pt: missing reference "
				    "to page directory page, va: 0x%lx", addr));
			}
			addr += NBPDR;
		}
		PMAP_UNLOCK(pmap);
	}
}