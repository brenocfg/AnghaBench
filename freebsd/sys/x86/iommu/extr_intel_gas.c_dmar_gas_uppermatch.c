#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
struct dmar_map_entry {scalar_t__ start; int /*<<< orphan*/  end; } ;
struct dmar_gas_match_args {TYPE_3__* domain; TYPE_2__* common; TYPE_1__* entry; } ;
struct TYPE_6__ {int /*<<< orphan*/  end; int /*<<< orphan*/  rb_root; } ;
struct TYPE_5__ {scalar_t__ highaddr; int /*<<< orphan*/  alignment; } ;
struct TYPE_4__ {scalar_t__ start; } ;

/* Variables and functions */
 scalar_t__ DMAR_PAGE_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 struct dmar_map_entry* RB_NEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dmar_map_entry*) ; 
 struct dmar_map_entry* RB_NFIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dmar_map_entry*) ; 
 struct dmar_map_entry* RB_PREV (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dmar_map_entry*) ; 
 int /*<<< orphan*/  dmar_gas_entries_tree ; 
 int /*<<< orphan*/  dmar_gas_match_insert (struct dmar_gas_match_args*,struct dmar_map_entry*) ; 
 scalar_t__ dmar_gas_match_one (struct dmar_gas_match_args*,struct dmar_map_entry*,int /*<<< orphan*/ ) ; 
 scalar_t__ roundup2 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dmar_gas_uppermatch(struct dmar_gas_match_args *a)
{
	struct dmar_map_entry *next, *prev, find_entry;

	find_entry.start = a->common->highaddr;
	next = RB_NFIND(dmar_gas_entries_tree, &a->domain->rb_root,
	    &find_entry);
	if (next == NULL)
		return (ENOMEM);
	prev = RB_PREV(dmar_gas_entries_tree, &a->domain->rb_root, next);
	KASSERT(prev != NULL, ("no prev %p %jx", a->domain,
	    (uintmax_t)find_entry.start));
	for (;;) {
		a->entry->start = prev->start + DMAR_PAGE_SIZE;
		if (a->entry->start < a->common->highaddr)
			a->entry->start = a->common->highaddr;
		a->entry->start = roundup2(a->entry->start,
		    a->common->alignment);
		if (dmar_gas_match_one(a, prev, a->domain->end)) {
			dmar_gas_match_insert(a, prev);
			return (0);
		}

		/*
		 * XXXKIB.  This falls back to linear iteration over
		 * the free space in the high region.  But high
		 * regions are almost unused, the code should be
		 * enough to cover the case, although in the
		 * non-optimal way.
		 */
		prev = next;
		next = RB_NEXT(dmar_gas_entries_tree, &a->domain->rb_root,
		    prev);
		KASSERT(next != NULL, ("no next %p %jx", a->domain,
		    (uintmax_t)find_entry.start));
		if (next->end >= a->domain->end)
			return (ENOMEM);
	}
}