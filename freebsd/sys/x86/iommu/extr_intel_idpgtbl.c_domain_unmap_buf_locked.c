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
typedef  int /*<<< orphan*/  vm_pindex_t ;
typedef  int /*<<< orphan*/  uintmax_t ;
struct sf_buf {int dummy; } ;
struct dmar_domain {int flags; unsigned long long agaw; int pglvl; } ;
struct TYPE_4__ {int pte; } ;
typedef  TYPE_1__ dmar_pte_t ;
typedef  unsigned long long dmar_gaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMAR_DOMAIN_ASSERT_PGLOCKED (struct dmar_domain*) ; 
 int DMAR_DOMAIN_IDMAP ; 
 unsigned long long DMAR_PAGE_MASK ; 
 int DMAR_PGF_OBJL ; 
 int DMAR_PGF_WAITOK ; 
 int DMAR_PTE_SP ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  TD_PINNED_ASSERT ; 
 int /*<<< orphan*/  TD_PREP_PINNED_ASSERT ; 
 int /*<<< orphan*/  dmar_unmap_pgtbl (struct sf_buf*) ; 
 int /*<<< orphan*/  domain_is_sp_lvl (struct dmar_domain*,int) ; 
 unsigned long long domain_page_size (struct dmar_domain*,int) ; 
 TYPE_1__* domain_pgtbl_map_pte (struct dmar_domain*,unsigned long long,int,int,int /*<<< orphan*/ *,struct sf_buf**) ; 
 int /*<<< orphan*/  domain_unmap_clear_pte (struct dmar_domain*,unsigned long long,int,int,TYPE_1__*,struct sf_buf**,int) ; 

__attribute__((used)) static int
domain_unmap_buf_locked(struct dmar_domain *domain, dmar_gaddr_t base,
    dmar_gaddr_t size, int flags)
{
	dmar_pte_t *pte;
	struct sf_buf *sf;
	vm_pindex_t idx;
	dmar_gaddr_t pg_sz;
	int lvl;

	DMAR_DOMAIN_ASSERT_PGLOCKED(domain);
	if (size == 0)
		return (0);

	KASSERT((domain->flags & DMAR_DOMAIN_IDMAP) == 0,
	    ("modifying idmap pagetable domain %p", domain));
	KASSERT((base & DMAR_PAGE_MASK) == 0,
	    ("non-aligned base %p %jx %jx", domain, (uintmax_t)base,
	    (uintmax_t)size));
	KASSERT((size & DMAR_PAGE_MASK) == 0,
	    ("non-aligned size %p %jx %jx", domain, (uintmax_t)base,
	    (uintmax_t)size));
	KASSERT(base < (1ULL << domain->agaw),
	    ("base too high %p %jx %jx agaw %d", domain, (uintmax_t)base,
	    (uintmax_t)size, domain->agaw));
	KASSERT(base + size < (1ULL << domain->agaw),
	    ("end too high %p %jx %jx agaw %d", domain, (uintmax_t)base,
	    (uintmax_t)size, domain->agaw));
	KASSERT(base + size > base,
	    ("size overflow %p %jx %jx", domain, (uintmax_t)base,
	    (uintmax_t)size));
	KASSERT((flags & ~DMAR_PGF_WAITOK) == 0, ("invalid flags %x", flags));

	pg_sz = 0; /* silence gcc */
	flags |= DMAR_PGF_OBJL;
	TD_PREP_PINNED_ASSERT;

	for (sf = NULL; size > 0; base += pg_sz, size -= pg_sz) {
		for (lvl = 0; lvl < domain->pglvl; lvl++) {
			if (lvl != domain->pglvl - 1 &&
			    !domain_is_sp_lvl(domain, lvl))
				continue;
			pg_sz = domain_page_size(domain, lvl);
			if (pg_sz > size)
				continue;
			pte = domain_pgtbl_map_pte(domain, base, lvl, flags,
			    &idx, &sf);
			KASSERT(pte != NULL,
			    ("sleeping or page missed %p %jx %d 0x%x",
			    domain, (uintmax_t)base, lvl, flags));
			if ((pte->pte & DMAR_PTE_SP) != 0 ||
			    lvl == domain->pglvl - 1) {
				domain_unmap_clear_pte(domain, base, lvl,
				    flags, pte, &sf, false);
				break;
			}
		}
		KASSERT(size >= pg_sz,
		    ("unmapping loop overflow %p %jx %jx %jx", domain,
		    (uintmax_t)base, (uintmax_t)size, (uintmax_t)pg_sz));
	}
	if (sf != NULL)
		dmar_unmap_pgtbl(sf);
	/*
	 * See 11.1 Write Buffer Flushing for an explanation why RWBF
	 * can be ignored there.
	 */

	TD_PINNED_ASSERT;
	return (0);
}