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
typedef  int u_int ;
struct dmar_map_entry {int flags; scalar_t__ start; scalar_t__ end; } ;
struct dmar_domain {int dummy; } ;
typedef  scalar_t__ dmar_gaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMAR_DOMAIN_LOCK (struct dmar_domain*) ; 
 int /*<<< orphan*/  DMAR_DOMAIN_UNLOCK (struct dmar_domain*) ; 
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
 int OFF_TO_IDX (scalar_t__) ; 
 int /*<<< orphan*/  dmar_domain_unload_entry (struct dmar_map_entry*,int) ; 
 int dmar_gas_alloc_region (struct dmar_domain*,struct dmar_map_entry*,int) ; 
 int domain_map_buf (struct dmar_domain*,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int
dmar_gas_map_region(struct dmar_domain *domain, struct dmar_map_entry *entry,
    u_int eflags, u_int flags, vm_page_t *ma)
{
	dmar_gaddr_t start;
	int error;

	KASSERT(entry->flags == 0, ("used RMRR entry %p %p %x", domain,
	    entry, entry->flags));
	KASSERT((flags & ~(DMAR_GM_CANWAIT)) == 0,
	    ("invalid flags 0x%x", flags));

	start = entry->start;
	DMAR_DOMAIN_LOCK(domain);
	error = dmar_gas_alloc_region(domain, entry, flags);
	if (error != 0) {
		DMAR_DOMAIN_UNLOCK(domain);
		return (error);
	}
	entry->flags |= eflags;
	DMAR_DOMAIN_UNLOCK(domain);
	if (entry->end == entry->start)
		return (0);

	error = domain_map_buf(domain, entry->start, entry->end - entry->start,
	    ma + OFF_TO_IDX(start - entry->start),
	    ((eflags & DMAR_MAP_ENTRY_READ) != 0 ? DMAR_PTE_R : 0) |
	    ((eflags & DMAR_MAP_ENTRY_WRITE) != 0 ? DMAR_PTE_W : 0) |
	    ((eflags & DMAR_MAP_ENTRY_SNOOP) != 0 ? DMAR_PTE_SNP : 0) |
	    ((eflags & DMAR_MAP_ENTRY_TM) != 0 ? DMAR_PTE_TM : 0),
	    (flags & DMAR_GM_CANWAIT) != 0 ? DMAR_PGF_WAITOK : 0);
	if (error == ENOMEM) {
		dmar_domain_unload_entry(entry, false);
		return (error);
	}
	KASSERT(error == 0,
	    ("unexpected error %d from domain_map_buf", error));

	return (0);
}