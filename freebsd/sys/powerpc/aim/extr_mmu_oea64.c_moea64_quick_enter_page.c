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
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  scalar_t__ vm_paddr_t ;
typedef  struct pvo_entry* vm_offset_t ;
typedef  int uint64_t ;
struct TYPE_3__ {int pa; } ;
struct pvo_entry {TYPE_1__ pvo_pte; } ;
typedef  int /*<<< orphan*/  mmu_t ;
struct TYPE_4__ {int /*<<< orphan*/  qmap_lock; int /*<<< orphan*/  qmap_pvo; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int /*<<< orphan*/  MOEA64_PTE_INVALIDATE ; 
 int /*<<< orphan*/  MOEA64_PTE_REPLACE (int /*<<< orphan*/ ,struct pvo_entry*,int /*<<< orphan*/ ) ; 
 struct pvo_entry* PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCPU_PTR (int /*<<< orphan*/ ) ; 
 struct pvo_entry* PHYS_TO_DMAP (scalar_t__) ; 
 scalar_t__ VM_PAGE_TO_PHYS (int /*<<< orphan*/ ) ; 
 TYPE_2__ aim ; 
 scalar_t__ hw_direct_map ; 
 int /*<<< orphan*/  isync () ; 
 int moea64_calc_wimg (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_page_get_memattr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qmap_addr ; 
 int /*<<< orphan*/  sched_pin () ; 

vm_offset_t
moea64_quick_enter_page(mmu_t mmu, vm_page_t m)
{
	struct pvo_entry *pvo;
	vm_paddr_t pa = VM_PAGE_TO_PHYS(m);

	if (hw_direct_map)
		return (PHYS_TO_DMAP(pa));

	/*
 	 * MOEA64_PTE_REPLACE does some locking, so we can't just grab
	 * a critical section and access the PCPU data like on i386.
	 * Instead, pin the thread and grab the PCPU lock to prevent
	 * a preempting thread from using the same PCPU data.
	 */
	sched_pin();

	mtx_assert(PCPU_PTR(aim.qmap_lock), MA_NOTOWNED);
	pvo = PCPU_GET(aim.qmap_pvo);

	mtx_lock(PCPU_PTR(aim.qmap_lock));
	pvo->pvo_pte.pa = moea64_calc_wimg(pa, pmap_page_get_memattr(m)) |
	    (uint64_t)pa;
	MOEA64_PTE_REPLACE(mmu, pvo, MOEA64_PTE_INVALIDATE);
	isync();

	return (PCPU_GET(qmap_addr));
}