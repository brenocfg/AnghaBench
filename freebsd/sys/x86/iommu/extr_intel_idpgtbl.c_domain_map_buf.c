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
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int uint64_t ;
struct dmar_unit {int hw_ecap; int hw_cap; } ;
struct dmar_domain {int flags; unsigned long long agaw; struct dmar_unit* dmar; } ;
typedef  unsigned long long dmar_gaddr_t ;

/* Variables and functions */
 int DMAR_CAP_CM ; 
 int DMAR_CAP_RWBF ; 
 int DMAR_DOMAIN_IDMAP ; 
 int /*<<< orphan*/  DMAR_DOMAIN_PGLOCK (struct dmar_domain*) ; 
 int /*<<< orphan*/  DMAR_DOMAIN_PGUNLOCK (struct dmar_domain*) ; 
 int DMAR_ECAP_DI ; 
 int DMAR_ECAP_SC ; 
 int /*<<< orphan*/  DMAR_LOCK (struct dmar_unit*) ; 
 unsigned long long DMAR_PAGE_MASK ; 
 int DMAR_PGF_WAITOK ; 
 int DMAR_PTE_R ; 
 int DMAR_PTE_SNP ; 
 int DMAR_PTE_TM ; 
 int DMAR_PTE_W ; 
 int /*<<< orphan*/  DMAR_UNLOCK (struct dmar_unit*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  dmar_flush_write_bufs (struct dmar_unit*) ; 
 int /*<<< orphan*/  domain_flush_iotlb_sync (struct dmar_domain*,unsigned long long,unsigned long long) ; 
 int domain_map_buf_locked (struct dmar_domain*,unsigned long long,unsigned long long,int /*<<< orphan*/ *,int,int) ; 

int
domain_map_buf(struct dmar_domain *domain, dmar_gaddr_t base, dmar_gaddr_t size,
    vm_page_t *ma, uint64_t pflags, int flags)
{
	struct dmar_unit *unit;
	int error;

	unit = domain->dmar;

	KASSERT((domain->flags & DMAR_DOMAIN_IDMAP) == 0,
	    ("modifying idmap pagetable domain %p", domain));
	KASSERT((base & DMAR_PAGE_MASK) == 0,
	    ("non-aligned base %p %jx %jx", domain, (uintmax_t)base,
	    (uintmax_t)size));
	KASSERT((size & DMAR_PAGE_MASK) == 0,
	    ("non-aligned size %p %jx %jx", domain, (uintmax_t)base,
	    (uintmax_t)size));
	KASSERT(size > 0, ("zero size %p %jx %jx", domain, (uintmax_t)base,
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
	KASSERT((pflags & (DMAR_PTE_R | DMAR_PTE_W)) != 0,
	    ("neither read nor write %jx", (uintmax_t)pflags));
	KASSERT((pflags & ~(DMAR_PTE_R | DMAR_PTE_W | DMAR_PTE_SNP |
	    DMAR_PTE_TM)) == 0,
	    ("invalid pte flags %jx", (uintmax_t)pflags));
	KASSERT((pflags & DMAR_PTE_SNP) == 0 ||
	    (unit->hw_ecap & DMAR_ECAP_SC) != 0,
	    ("PTE_SNP for dmar without snoop control %p %jx",
	    domain, (uintmax_t)pflags));
	KASSERT((pflags & DMAR_PTE_TM) == 0 ||
	    (unit->hw_ecap & DMAR_ECAP_DI) != 0,
	    ("PTE_TM for dmar without DIOTLB %p %jx",
	    domain, (uintmax_t)pflags));
	KASSERT((flags & ~DMAR_PGF_WAITOK) == 0, ("invalid flags %x", flags));

	DMAR_DOMAIN_PGLOCK(domain);
	error = domain_map_buf_locked(domain, base, size, ma, pflags, flags);
	DMAR_DOMAIN_PGUNLOCK(domain);
	if (error != 0)
		return (error);

	if ((unit->hw_cap & DMAR_CAP_CM) != 0)
		domain_flush_iotlb_sync(domain, base, size);
	else if ((unit->hw_cap & DMAR_CAP_RWBF) != 0) {
		/* See 11.1 Write Buffer Flushing. */
		DMAR_LOCK(unit);
		dmar_flush_write_bufs(unit);
		DMAR_UNLOCK(unit);
	}
	return (0);
}