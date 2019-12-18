#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
struct tte {int tte_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  tte_list; } ;
struct TYPE_6__ {TYPE_1__ md; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR3 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct tte*,int) ; 
 int /*<<< orphan*/  KTR_PMAP ; 
 TYPE_2__* PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_STATS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RA_WLOCKED ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct tte*,int /*<<< orphan*/ ) ; 
 int TD_V ; 
 int /*<<< orphan*/  TTE_GET_PA (struct tte*) ; 
 int /*<<< orphan*/  TTE_ZERO (struct tte*) ; 
 int /*<<< orphan*/  pmap_cache_remove (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_nkremove ; 
 int /*<<< orphan*/  rw_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct tte* tsb_kvtotte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tte_link ; 
 int /*<<< orphan*/  tte_list_global_lock ; 

void
pmap_kremove(vm_offset_t va)
{
	struct tte *tp;
	vm_page_t m;

	rw_assert(&tte_list_global_lock, RA_WLOCKED);
	PMAP_STATS_INC(pmap_nkremove);
	tp = tsb_kvtotte(va);
	CTR3(KTR_PMAP, "pmap_kremove: va=%#lx tp=%p data=%#lx", va, tp,
	    tp->tte_data);
	if ((tp->tte_data & TD_V) == 0)
		return;
	m = PHYS_TO_VM_PAGE(TTE_GET_PA(tp));
	TAILQ_REMOVE(&m->md.tte_list, tp, tte_link);
	pmap_cache_remove(m, va);
	TTE_ZERO(tp);
}