#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
struct md_page {int /*<<< orphan*/  pv_list; } ;
typedef  int /*<<< orphan*/  pmap_t ;
struct TYPE_7__ {int /*<<< orphan*/  pv_list; } ;
struct TYPE_6__ {int flags; TYPE_4__ md; } ;

/* Variables and functions */
 int /*<<< orphan*/  PGA_WRITEABLE ; 
 int PG_FICTITIOUS ; 
 int /*<<< orphan*/  RA_WLOCKED ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VM_PAGE_TO_PHYS (TYPE_1__*) ; 
 struct md_page* pa_to_pvh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_pvh_free (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvh_global_lock ; 
 int /*<<< orphan*/  rw_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_aflag_clear (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pmap_remove_entry(pmap_t pmap, vm_page_t m, vm_offset_t va)
{
	struct md_page *pvh;

	rw_assert(&pvh_global_lock, RA_WLOCKED);
	pmap_pvh_free(&m->md, pmap, va);
	if (TAILQ_EMPTY(&m->md.pv_list) && (m->flags & PG_FICTITIOUS) == 0) {
		pvh = pa_to_pvh(VM_PAGE_TO_PHYS(m));
		if (TAILQ_EMPTY(&pvh->pv_list))
			vm_page_aflag_clear(m, PGA_WRITEABLE);
	}
}