#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  TYPE_1__* pmap_t ;
struct TYPE_4__ {int /*<<< orphan*/  pm_cookie; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASID_TO_OPERAND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COOKIE_TO_ASID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isb () ; 
 int /*<<< orphan*/  ish ; 
 int /*<<< orphan*/  ishst ; 
 TYPE_1__* kernel_pmap ; 

__attribute__((used)) static __inline void
pmap_invalidate_range_nopin(pmap_t pmap, vm_offset_t sva, vm_offset_t eva)
{
	uint64_t end, r, start;

	dsb(ishst);
	if (pmap == kernel_pmap) {
		start = atop(sva);
		end = atop(eva);
		for (r = start; r < end; r++)
			__asm __volatile("tlbi vaae1is, %0" : : "r" (r));
	} else {
		start = end = ASID_TO_OPERAND(COOKIE_TO_ASID(pmap->pm_cookie));
		start |= atop(sva);
		end |= atop(eva);
		for (r = start; r < end; r++)
			__asm __volatile("tlbi vae1is, %0" : : "r" (r));
	}
	dsb(ish);
	isb();
}