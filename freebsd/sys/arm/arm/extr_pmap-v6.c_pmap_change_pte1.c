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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  register_t ;
typedef  int /*<<< orphan*/  pt1_entry_t ;
typedef  scalar_t__ pmap_t ;

/* Variables and functions */
 int PSR_F ; 
 int PSR_I ; 
 int /*<<< orphan*/  allpmaps_lock ; 
 int /*<<< orphan*/  disable_interrupts (int) ; 
 scalar_t__ kernel_pmap ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmap_tlb_flush_pte1 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_update_pte1_kernel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte1_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte1_store (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restore_interrupts (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pmap_change_pte1(pmap_t pmap, pt1_entry_t *pte1p, vm_offset_t va,
    pt1_entry_t npte1)
{

	if (pmap == kernel_pmap) {
		mtx_lock_spin(&allpmaps_lock);
		pmap_update_pte1_kernel(va, npte1);
		mtx_unlock_spin(&allpmaps_lock);
	} else {
		register_t cspr;

		/*
		 * Use break-before-make approach for changing userland
		 * mappings. It's absolutely safe in UP case when interrupts
		 * are disabled.
		 */
		cspr = disable_interrupts(PSR_I | PSR_F);
		pte1_clear(pte1p);
		pmap_tlb_flush_pte1(pmap, va, npte1);
		pte1_store(pte1p, npte1);
		restore_interrupts(cspr);
	}
}