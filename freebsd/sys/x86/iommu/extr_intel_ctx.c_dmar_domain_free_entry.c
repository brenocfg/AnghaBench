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
struct dmar_map_entry {int flags; struct dmar_domain* domain; } ;
struct dmar_domain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAR_DOMAIN_LOCK (struct dmar_domain*) ; 
 int /*<<< orphan*/  DMAR_DOMAIN_UNLOCK (struct dmar_domain*) ; 
 int DMAR_MAP_ENTRY_RMRR ; 
 int /*<<< orphan*/  dmar_gas_free_entry (struct dmar_domain*,struct dmar_map_entry*) ; 
 int /*<<< orphan*/  dmar_gas_free_region (struct dmar_domain*,struct dmar_map_entry*) ; 
 int /*<<< orphan*/  dmar_gas_free_space (struct dmar_domain*,struct dmar_map_entry*) ; 

void
dmar_domain_free_entry(struct dmar_map_entry *entry, bool free)
{
	struct dmar_domain *domain;

	domain = entry->domain;
	DMAR_DOMAIN_LOCK(domain);
	if ((entry->flags & DMAR_MAP_ENTRY_RMRR) != 0)
		dmar_gas_free_region(domain, entry);
	else
		dmar_gas_free_space(domain, entry);
	DMAR_DOMAIN_UNLOCK(domain);
	if (free)
		dmar_gas_free_entry(domain, entry);
	else
		entry->flags = 0;
}