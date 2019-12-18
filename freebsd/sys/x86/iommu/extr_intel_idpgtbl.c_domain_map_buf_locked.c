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
typedef  size_t vm_pindex_t ;
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int uint64_t ;
struct sf_buf {int dummy; } ;
struct dmar_domain {int pglvl; int /*<<< orphan*/  dmar; } ;
struct TYPE_5__ {int /*<<< orphan*/  pte; } ;
typedef  TYPE_1__ dmar_pte_t ;
typedef  int dmar_gaddr_t ;
struct TYPE_6__ {int ref_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAR_DOMAIN_ASSERT_PGLOCKED (struct dmar_domain*) ; 
 int DMAR_PAGE_SHIFT ; 
 int DMAR_PGF_OBJL ; 
 int DMAR_PGF_WAITOK ; 
 int DMAR_PTE_SP ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  TD_PINNED_ASSERT ; 
 int /*<<< orphan*/  TD_PREP_PINNED_ASSERT ; 
 int VM_PAGE_TO_PHYS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmar_flush_pte_to_ram (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  dmar_pte_store (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dmar_unmap_pgtbl (struct sf_buf*) ; 
 int /*<<< orphan*/  domain_is_sp_lvl (struct dmar_domain*,int) ; 
 int domain_page_size (struct dmar_domain*,int) ; 
 TYPE_1__* domain_pgtbl_map_pte (struct dmar_domain*,int,int,int,size_t*,struct sf_buf**) ; 
 int /*<<< orphan*/  domain_unmap_buf_locked (struct dmar_domain*,int,int,int) ; 
 TYPE_2__* sf_buf_page (struct sf_buf*) ; 

__attribute__((used)) static int
domain_map_buf_locked(struct dmar_domain *domain, dmar_gaddr_t base,
    dmar_gaddr_t size, vm_page_t *ma, uint64_t pflags, int flags)
{
	dmar_pte_t *pte;
	struct sf_buf *sf;
	dmar_gaddr_t pg_sz, base1, size1;
	vm_pindex_t pi, c, idx, run_sz;
	int lvl;
	bool superpage;

	DMAR_DOMAIN_ASSERT_PGLOCKED(domain);

	base1 = base;
	size1 = size;
	flags |= DMAR_PGF_OBJL;
	TD_PREP_PINNED_ASSERT;

	for (sf = NULL, pi = 0; size > 0; base += pg_sz, size -= pg_sz,
	    pi += run_sz) {
		for (lvl = 0, c = 0, superpage = false;; lvl++) {
			pg_sz = domain_page_size(domain, lvl);
			run_sz = pg_sz >> DMAR_PAGE_SHIFT;
			if (lvl == domain->pglvl - 1)
				break;
			/*
			 * Check if the current base suitable for the
			 * superpage mapping.  First, verify the level.
			 */
			if (!domain_is_sp_lvl(domain, lvl))
				continue;
			/*
			 * Next, look at the size of the mapping and
			 * alignment of both guest and host addresses.
			 */
			if (size < pg_sz || (base & (pg_sz - 1)) != 0 ||
			    (VM_PAGE_TO_PHYS(ma[pi]) & (pg_sz - 1)) != 0)
				continue;
			/* All passed, check host pages contiguouty. */
			if (c == 0) {
				for (c = 1; c < run_sz; c++) {
					if (VM_PAGE_TO_PHYS(ma[pi + c]) !=
					    VM_PAGE_TO_PHYS(ma[pi + c - 1]) +
					    PAGE_SIZE)
						break;
				}
			}
			if (c >= run_sz) {
				superpage = true;
				break;
			}
		}
		KASSERT(size >= pg_sz,
		    ("mapping loop overflow %p %jx %jx %jx", domain,
		    (uintmax_t)base, (uintmax_t)size, (uintmax_t)pg_sz));
		KASSERT(pg_sz > 0, ("pg_sz 0 lvl %d", lvl));
		pte = domain_pgtbl_map_pte(domain, base, lvl, flags, &idx, &sf);
		if (pte == NULL) {
			KASSERT((flags & DMAR_PGF_WAITOK) == 0,
			    ("failed waitable pte alloc %p", domain));
			if (sf != NULL)
				dmar_unmap_pgtbl(sf);
			domain_unmap_buf_locked(domain, base1, base - base1,
			    flags);
			TD_PINNED_ASSERT;
			return (ENOMEM);
		}
		dmar_pte_store(&pte->pte, VM_PAGE_TO_PHYS(ma[pi]) | pflags |
		    (superpage ? DMAR_PTE_SP : 0));
		dmar_flush_pte_to_ram(domain->dmar, pte);
		sf_buf_page(sf)->ref_count += 1;
	}
	if (sf != NULL)
		dmar_unmap_pgtbl(sf);
	TD_PINNED_ASSERT;
	return (0);
}