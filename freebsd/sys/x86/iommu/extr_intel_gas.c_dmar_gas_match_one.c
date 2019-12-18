#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dmar_map_entry {scalar_t__ end; scalar_t__ free_after; } ;
struct dmar_gas_match_args {scalar_t__ size; scalar_t__ offset; int gas_flags; TYPE_2__* entry; TYPE_1__* common; } ;
typedef  scalar_t__ dmar_gaddr_t ;
struct TYPE_4__ {scalar_t__ start; } ;
struct TYPE_3__ {scalar_t__ boundary; int /*<<< orphan*/  alignment; } ;

/* Variables and functions */
 int DMAR_GM_CANSPLIT ; 
 scalar_t__ DMAR_PAGE_SIZE ; 
 scalar_t__ dmar_test_boundary (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ rounddown2 (scalar_t__,scalar_t__) ; 
 scalar_t__ roundup2 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
dmar_gas_match_one(struct dmar_gas_match_args *a, struct dmar_map_entry *prev,
    dmar_gaddr_t end)
{
	dmar_gaddr_t bs, start;

	if (a->entry->start + a->size > end)
		return (false);

	/* DMAR_PAGE_SIZE to create gap after new entry. */
	if (a->entry->start < prev->end + DMAR_PAGE_SIZE ||
	    a->entry->start + a->size + a->offset + DMAR_PAGE_SIZE >
	    prev->end + prev->free_after)
		return (false);

	/* No boundary crossing. */
	if (dmar_test_boundary(a->entry->start + a->offset, a->size,
	    a->common->boundary))
		return (true);

	/*
	 * The start + offset to start + offset + size region crosses
	 * the boundary.  Check if there is enough space after the
	 * next boundary after the prev->end.
	 */
	bs = rounddown2(a->entry->start + a->offset + a->common->boundary,
	    a->common->boundary);
	start = roundup2(bs, a->common->alignment);
	/* DMAR_PAGE_SIZE to create gap after new entry. */
	if (start + a->offset + a->size + DMAR_PAGE_SIZE <=
	    prev->end + prev->free_after &&
	    start + a->offset + a->size <= end &&
	    dmar_test_boundary(start + a->offset, a->size,
	    a->common->boundary)) {
		a->entry->start = start;
		return (true);
	}

	/*
	 * Not enough space to align at the requested boundary, or
	 * boundary is smaller than the size, but allowed to split.
	 * We already checked that start + size does not overlap end.
	 *
	 * XXXKIB. It is possible that bs is exactly at the start of
	 * the next entry, then we do not have gap.  Ignore for now.
	 */
	if ((a->gas_flags & DMAR_GM_CANSPLIT) != 0) {
		a->size = bs - a->entry->start;
		return (true);
	}

	return (false);
}