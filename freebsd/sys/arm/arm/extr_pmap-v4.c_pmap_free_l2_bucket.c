#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_short ;
typedef  scalar_t__ u_int ;
struct l2_dtable {scalar_t__ l2_occupancy; } ;
struct l2_bucket {scalar_t__ l2b_occupancy; size_t l2b_l1idx; int /*<<< orphan*/ * l2b_kva; } ;
typedef  int /*<<< orphan*/  pt_entry_t ;
typedef  TYPE_2__* pmap_t ;
typedef  int pd_entry_t ;
struct TYPE_7__ {struct l2_dtable** pm_l2; int /*<<< orphan*/  pm_domain; TYPE_1__* pm_l1; } ;
struct TYPE_6__ {int* l1_kva; } ;

/* Variables and functions */
 int L1_C_DOM (int /*<<< orphan*/ ) ; 
 int L1_C_DOM_MASK ; 
 int L1_TYPE_C ; 
 int L1_TYPE_MASK ; 
 size_t L2_IDX (size_t) ; 
 int /*<<< orphan*/  PTE_SYNC (int*) ; 
 TYPE_2__* kernel_pmap ; 
 int /*<<< orphan*/  l2table_zone ; 
 int /*<<< orphan*/  pmap_free_l2_ptp (int,...) ; 
 int /*<<< orphan*/  pmap_is_current (TYPE_2__*) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct l2_dtable*) ; 

__attribute__((used)) static void
pmap_free_l2_bucket(pmap_t pm, struct l2_bucket *l2b, u_int count)
{
	struct l2_dtable *l2;
	pd_entry_t *pl1pd, l1pd;
	pt_entry_t *ptep;
	u_short l1idx;


	/*
	 * Update the bucket's reference count according to how many
	 * PTEs the caller has just invalidated.
	 */
	l2b->l2b_occupancy -= count;

	/*
	 * Note:
	 *
	 * Level 2 page tables allocated to the kernel pmap are never freed
	 * as that would require checking all Level 1 page tables and
	 * removing any references to the Level 2 page table. See also the
	 * comment elsewhere about never freeing bootstrap L2 descriptors.
	 *
	 * We make do with just invalidating the mapping in the L2 table.
	 *
	 * This isn't really a big deal in practice and, in fact, leads
	 * to a performance win over time as we don't need to continually
	 * alloc/free.
	 */
	if (l2b->l2b_occupancy > 0 || pm == kernel_pmap)
		return;

	/*
	 * There are no more valid mappings in this level 2 page table.
	 * Go ahead and NULL-out the pointer in the bucket, then
	 * free the page table.
	 */
	l1idx = l2b->l2b_l1idx;
	ptep = l2b->l2b_kva;
	l2b->l2b_kva = NULL;

	pl1pd = &pm->pm_l1->l1_kva[l1idx];

	/*
	 * If the L1 slot matches the pmap's domain
	 * number, then invalidate it.
	 */
	l1pd = *pl1pd & (L1_TYPE_MASK | L1_C_DOM_MASK);
	if (l1pd == (L1_C_DOM(pm->pm_domain) | L1_TYPE_C)) {
		*pl1pd = 0;
		PTE_SYNC(pl1pd);
	}

	/*
	 * Release the L2 descriptor table back to the pool cache.
	 */
#ifndef PMAP_INCLUDE_PTE_SYNC
	pmap_free_l2_ptp(ptep);
#else
	pmap_free_l2_ptp(!pmap_is_current(pm), ptep);
#endif

	/*
	 * Update the reference count in the associated l2_dtable
	 */
	l2 = pm->pm_l2[L2_IDX(l1idx)];
	if (--l2->l2_occupancy > 0)
		return;

	/*
	 * There are no more valid mappings in any of the Level 1
	 * slots managed by this l2_dtable. Go ahead and NULL-out
	 * the pointer in the parent pmap and free the l2_dtable.
	 */
	pm->pm_l2[L2_IDX(l1idx)] = NULL;
	uma_zfree(l2table_zone, l2);
}