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
struct dmar_map_entry {int dummy; } ;
struct dmar_domain {int /*<<< orphan*/  rb_root; } ;

/* Variables and functions */
 struct dmar_map_entry* RB_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dmar_map_entry*) ; 
 struct dmar_map_entry* RB_PREV (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dmar_map_entry*) ; 
 int /*<<< orphan*/  dmar_gas_entries_tree ; 
 int /*<<< orphan*/  dmar_gas_fix_free (struct dmar_domain*,struct dmar_map_entry*) ; 

__attribute__((used)) static bool
dmar_gas_rb_insert(struct dmar_domain *domain, struct dmar_map_entry *entry)
{
	struct dmar_map_entry *prev, *found;

	found = RB_INSERT(dmar_gas_entries_tree, &domain->rb_root, entry);
	dmar_gas_fix_free(domain, entry);
	prev = RB_PREV(dmar_gas_entries_tree, &domain->rb_root, entry);
	if (prev != NULL)
		dmar_gas_fix_free(domain, prev);
	return (found == NULL);
}