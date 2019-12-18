#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
struct TYPE_2__ {scalar_t__ pv_kva; int /*<<< orphan*/  pv_list; } ;
struct vm_page {TYPE_1__ md; } ;
struct pv_entry {scalar_t__ pv_pmap; scalar_t__ pv_va; } ;
typedef  scalar_t__ pmap_t ;

/* Variables and functions */
 int /*<<< orphan*/  RA_WLOCKED ; 
 struct pv_entry* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct pv_entry* TAILQ_NEXT (struct pv_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_nuke_pv (struct vm_page*,scalar_t__,struct pv_entry*) ; 
 int /*<<< orphan*/  pv_list ; 
 int /*<<< orphan*/  pvh_global_lock ; 
 int /*<<< orphan*/  rw_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct pv_entry *
pmap_remove_pv(struct vm_page *pg, pmap_t pm, vm_offset_t va)
{
	struct pv_entry *pve;

	rw_assert(&pvh_global_lock, RA_WLOCKED);
	pve = TAILQ_FIRST(&pg->md.pv_list);

	while (pve) {
		if (pve->pv_pmap == pm && pve->pv_va == va) {	/* match? */
			pmap_nuke_pv(pg, pm, pve);
			break;
		}
		pve = TAILQ_NEXT(pve, pv_list);
	}

	if (pve == NULL && pg->md.pv_kva == va)
		pg->md.pv_kva = 0;

	return(pve);				/* return removed pve */
}