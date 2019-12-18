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
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  pt1_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTE1_LINK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kern_pte1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_pt2pa (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_preboot_pt2pg_setup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte1_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte1_store (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pmap_preboot_pt2_setup(vm_offset_t va)
{
	pt1_entry_t *pte1p;
	vm_paddr_t pt2pg_pa, pt2_pa;

	/* Setup PT2's page. */
	pt2pg_pa = pmap_preboot_pt2pg_setup(va);
	pt2_pa = page_pt2pa(pt2pg_pa, pte1_index(va));

	/* Insert PT2 to PT1. */
	pte1p = kern_pte1(va);
	pte1_store(pte1p, PTE1_LINK(pt2_pa));
}