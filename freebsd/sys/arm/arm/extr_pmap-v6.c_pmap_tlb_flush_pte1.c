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
typedef  int /*<<< orphan*/  pt1_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTE1_SIZE ; 
 int /*<<< orphan*/  pmap_tlb_flush (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_tlb_flush_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pte1_is_section (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte1_trunc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
pmap_tlb_flush_pte1(pmap_t pmap, vm_offset_t va, pt1_entry_t npte1)
{

	/* Kill all the small mappings or the big one only. */
	if (pte1_is_section(npte1))
		pmap_tlb_flush_range(pmap, pte1_trunc(va), PTE1_SIZE);
	else
		pmap_tlb_flush(pmap, pte1_trunc(va));
}