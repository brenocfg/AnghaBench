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
struct dmar_map_entry {int flags; } ;
struct dmar_domain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAR_DOMAIN_ASSERT_LOCKED (struct dmar_domain*) ; 
 int DMAR_MAP_ENTRY_MAP ; 
 int DMAR_MAP_ENTRY_PLACE ; 
 int DMAR_MAP_ENTRY_RMRR ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ dmar_check_free ; 
 int /*<<< orphan*/  dmar_gas_check_free (struct dmar_domain*) ; 
 int /*<<< orphan*/  dmar_gas_rb_remove (struct dmar_domain*,struct dmar_map_entry*) ; 

void
dmar_gas_free_space(struct dmar_domain *domain, struct dmar_map_entry *entry)
{

	DMAR_DOMAIN_ASSERT_LOCKED(domain);
	KASSERT((entry->flags & (DMAR_MAP_ENTRY_PLACE | DMAR_MAP_ENTRY_RMRR |
	    DMAR_MAP_ENTRY_MAP)) == DMAR_MAP_ENTRY_MAP,
	    ("permanent entry %p %p", domain, entry));

	dmar_gas_rb_remove(domain, entry);
	entry->flags &= ~DMAR_MAP_ENTRY_MAP;
#ifdef INVARIANTS
	if (dmar_check_free)
		dmar_gas_check_free(domain);
#endif
}