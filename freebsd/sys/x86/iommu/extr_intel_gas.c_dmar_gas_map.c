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
typedef  int u_int ;
struct dmar_map_entry {scalar_t__ end; int flags; scalar_t__ start; } ;
struct dmar_domain {scalar_t__ end; } ;
struct bus_dma_tag_common {int dummy; } ;
typedef  int /*<<< orphan*/  dmar_gaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMAR_DOMAIN_LOCK (struct dmar_domain*) ; 
 int /*<<< orphan*/  DMAR_DOMAIN_UNLOCK (struct dmar_domain*) ; 
 int DMAR_GM_CANSPLIT ; 
 int DMAR_GM_CANWAIT ; 
 int DMAR_MAP_ENTRY_READ ; 
 int DMAR_MAP_ENTRY_SNOOP ; 
 int DMAR_MAP_ENTRY_TM ; 
 int DMAR_MAP_ENTRY_WRITE ; 
 int /*<<< orphan*/  DMAR_PGF_WAITOK ; 
 int DMAR_PTE_R ; 
 int DMAR_PTE_SNP ; 
 int DMAR_PTE_TM ; 
 int DMAR_PTE_W ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ dmar_check_free ; 
 int /*<<< orphan*/  dmar_domain_unload_entry (struct dmar_map_entry*,int) ; 
 struct dmar_map_entry* dmar_gas_alloc_entry (struct dmar_domain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmar_gas_check_free (struct dmar_domain*) ; 
 int dmar_gas_find_space (struct dmar_domain*,struct bus_dma_tag_common const*,int /*<<< orphan*/ ,int,int,struct dmar_map_entry*) ; 
 int /*<<< orphan*/  dmar_gas_free_entry (struct dmar_domain*,struct dmar_map_entry*) ; 
 int domain_map_buf (struct dmar_domain*,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int
dmar_gas_map(struct dmar_domain *domain,
    const struct bus_dma_tag_common *common, dmar_gaddr_t size, int offset,
    u_int eflags, u_int flags, vm_page_t *ma, struct dmar_map_entry **res)
{
	struct dmar_map_entry *entry;
	int error;

	KASSERT((flags & ~(DMAR_GM_CANWAIT | DMAR_GM_CANSPLIT)) == 0,
	    ("invalid flags 0x%x", flags));

	entry = dmar_gas_alloc_entry(domain, (flags & DMAR_GM_CANWAIT) != 0 ?
	    DMAR_PGF_WAITOK : 0);
	if (entry == NULL)
		return (ENOMEM);
	DMAR_DOMAIN_LOCK(domain);
	error = dmar_gas_find_space(domain, common, size, offset, flags,
	    entry);
	if (error == ENOMEM) {
		DMAR_DOMAIN_UNLOCK(domain);
		dmar_gas_free_entry(domain, entry);
		return (error);
	}
#ifdef INVARIANTS
	if (dmar_check_free)
		dmar_gas_check_free(domain);
#endif
	KASSERT(error == 0,
	    ("unexpected error %d from dmar_gas_find_entry", error));
	KASSERT(entry->end < domain->end, ("allocated GPA %jx, max GPA %jx",
	    (uintmax_t)entry->end, (uintmax_t)domain->end));
	entry->flags |= eflags;
	DMAR_DOMAIN_UNLOCK(domain);

	error = domain_map_buf(domain, entry->start, entry->end - entry->start,
	    ma,
	    ((eflags & DMAR_MAP_ENTRY_READ) != 0 ? DMAR_PTE_R : 0) |
	    ((eflags & DMAR_MAP_ENTRY_WRITE) != 0 ? DMAR_PTE_W : 0) |
	    ((eflags & DMAR_MAP_ENTRY_SNOOP) != 0 ? DMAR_PTE_SNP : 0) |
	    ((eflags & DMAR_MAP_ENTRY_TM) != 0 ? DMAR_PTE_TM : 0),
	    (flags & DMAR_GM_CANWAIT) != 0 ? DMAR_PGF_WAITOK : 0);
	if (error == ENOMEM) {
		dmar_domain_unload_entry(entry, true);
		return (error);
	}
	KASSERT(error == 0,
	    ("unexpected error %d from domain_map_buf", error));

	*res = entry;
	return (0);
}