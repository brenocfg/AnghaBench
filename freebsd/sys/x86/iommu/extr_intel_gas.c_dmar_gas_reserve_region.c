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
struct dmar_map_entry {int /*<<< orphan*/  flags; void* end; void* start; } ;
struct dmar_domain {int dummy; } ;
typedef  void* dmar_gaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMAR_DOMAIN_LOCK (struct dmar_domain*) ; 
 int /*<<< orphan*/  DMAR_DOMAIN_UNLOCK (struct dmar_domain*) ; 
 int /*<<< orphan*/  DMAR_GM_CANWAIT ; 
 int /*<<< orphan*/  DMAR_MAP_ENTRY_UNMAPPED ; 
 int /*<<< orphan*/  DMAR_PGF_WAITOK ; 
 struct dmar_map_entry* dmar_gas_alloc_entry (struct dmar_domain*,int /*<<< orphan*/ ) ; 
 int dmar_gas_alloc_region (struct dmar_domain*,struct dmar_map_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmar_gas_free_entry (struct dmar_domain*,struct dmar_map_entry*) ; 

int
dmar_gas_reserve_region(struct dmar_domain *domain, dmar_gaddr_t start,
    dmar_gaddr_t end)
{
	struct dmar_map_entry *entry;
	int error;

	entry = dmar_gas_alloc_entry(domain, DMAR_PGF_WAITOK);
	entry->start = start;
	entry->end = end;
	DMAR_DOMAIN_LOCK(domain);
	error = dmar_gas_alloc_region(domain, entry, DMAR_GM_CANWAIT);
	if (error == 0)
		entry->flags |= DMAR_MAP_ENTRY_UNMAPPED;
	DMAR_DOMAIN_UNLOCK(domain);
	if (error != 0)
		dmar_gas_free_entry(domain, entry);
	return (error);
}