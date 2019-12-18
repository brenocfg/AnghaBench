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
struct dmar_map_entry {scalar_t__ end; scalar_t__ start; scalar_t__ free_after; } ;
struct dmar_domain {scalar_t__ end; int /*<<< orphan*/  rb_root; } ;

/* Variables and functions */
 struct dmar_map_entry* RB_NEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dmar_map_entry*) ; 
 int /*<<< orphan*/  dmar_gas_augment_entry (struct dmar_map_entry*) ; 
 int /*<<< orphan*/  dmar_gas_entries_tree ; 

__attribute__((used)) static void
dmar_gas_fix_free(struct dmar_domain *domain, struct dmar_map_entry *entry)
{
	struct dmar_map_entry *next;

	next = RB_NEXT(dmar_gas_entries_tree, &domain->rb_root, entry);
	entry->free_after = (next != NULL ? next->start : domain->end) -
	    entry->end;
	dmar_gas_augment_entry(entry);
}