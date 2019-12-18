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
typedef  int /*<<< orphan*/  mmu_t ;
struct TYPE_2__ {int /*<<< orphan*/  qmap_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCPU_PTR (int /*<<< orphan*/ ) ; 
 TYPE_1__ aim ; 
 scalar_t__ hw_direct_map ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qmap_addr ; 
 int /*<<< orphan*/  sched_unpin () ; 

void
moea64_quick_remove_page(mmu_t mmu, vm_offset_t addr)
{
	if (hw_direct_map)
		return;

	mtx_assert(PCPU_PTR(aim.qmap_lock), MA_OWNED);
	KASSERT(PCPU_GET(qmap_addr) == addr,
	    ("moea64_quick_remove_page: invalid address"));
	mtx_unlock(PCPU_PTR(aim.qmap_lock));
	sched_unpin();	
}