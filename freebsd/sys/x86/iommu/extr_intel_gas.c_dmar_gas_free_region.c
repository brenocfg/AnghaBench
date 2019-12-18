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
struct dmar_domain {int /*<<< orphan*/  last_place; int /*<<< orphan*/  first_place; int /*<<< orphan*/  rb_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAR_DOMAIN_ASSERT_LOCKED (struct dmar_domain*) ; 
 int DMAR_MAP_ENTRY_MAP ; 
 int DMAR_MAP_ENTRY_PLACE ; 
 int DMAR_MAP_ENTRY_RMRR ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 struct dmar_map_entry* RB_NEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dmar_map_entry*) ; 
 struct dmar_map_entry* RB_PREV (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dmar_map_entry*) ; 
 int /*<<< orphan*/  dmar_gas_entries_tree ; 
 int /*<<< orphan*/  dmar_gas_rb_insert (struct dmar_domain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmar_gas_rb_remove (struct dmar_domain*,struct dmar_map_entry*) ; 

void
dmar_gas_free_region(struct dmar_domain *domain, struct dmar_map_entry *entry)
{
	struct dmar_map_entry *next, *prev;

	DMAR_DOMAIN_ASSERT_LOCKED(domain);
	KASSERT((entry->flags & (DMAR_MAP_ENTRY_PLACE | DMAR_MAP_ENTRY_RMRR |
	    DMAR_MAP_ENTRY_MAP)) == DMAR_MAP_ENTRY_RMRR,
	    ("non-RMRR entry %p %p", domain, entry));

	prev = RB_PREV(dmar_gas_entries_tree, &domain->rb_root, entry);
	next = RB_NEXT(dmar_gas_entries_tree, &domain->rb_root, entry);
	dmar_gas_rb_remove(domain, entry);
	entry->flags &= ~DMAR_MAP_ENTRY_RMRR;

	if (prev == NULL)
		dmar_gas_rb_insert(domain, domain->first_place);
	if (next == NULL)
		dmar_gas_rb_insert(domain, domain->last_place);
}