#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dmar_unit {int /*<<< orphan*/  tlb_flush_entries; scalar_t__ qi_enabled; } ;
struct dmar_map_entry {scalar_t__ start; scalar_t__ end; TYPE_1__* domain; int /*<<< orphan*/  flags; int /*<<< orphan*/  gseq; } ;
struct TYPE_3__ {struct dmar_unit* dmar; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAR_LOCK (struct dmar_unit*) ; 
 int /*<<< orphan*/  DMAR_MAP_ENTRY_QI_NF ; 
 int /*<<< orphan*/  DMAR_UNLOCK (struct dmar_unit*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct dmar_map_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmamap_link ; 
 int /*<<< orphan*/  dmar_domain_free_entry (struct dmar_map_entry*,int) ; 
 int /*<<< orphan*/  dmar_qi_invalidate_locked (TYPE_1__*,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  domain_flush_iotlb_sync (TYPE_1__*,scalar_t__,scalar_t__) ; 

void
dmar_domain_unload_entry(struct dmar_map_entry *entry, bool free)
{
	struct dmar_unit *unit;

	unit = entry->domain->dmar;
	if (unit->qi_enabled) {
		DMAR_LOCK(unit);
		dmar_qi_invalidate_locked(entry->domain, entry->start,
		    entry->end - entry->start, &entry->gseq, true);
		if (!free)
			entry->flags |= DMAR_MAP_ENTRY_QI_NF;
		TAILQ_INSERT_TAIL(&unit->tlb_flush_entries, entry, dmamap_link);
		DMAR_UNLOCK(unit);
	} else {
		domain_flush_iotlb_sync(entry->domain, entry->start,
		    entry->end - entry->start);
		dmar_domain_free_entry(entry, free);
	}
}