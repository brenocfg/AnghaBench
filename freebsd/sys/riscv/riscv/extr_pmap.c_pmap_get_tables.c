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
typedef  int /*<<< orphan*/  pt_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int /*<<< orphan*/  pd_entry_t ;

/* Variables and functions */
 int PTE_RX ; 
 int PTE_V ; 
 int /*<<< orphan*/ * pmap_l1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmap_l1_to_l2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmap_l2_to_l3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pmap_load (int /*<<< orphan*/ *) ; 

bool
pmap_get_tables(pmap_t pmap, vm_offset_t va, pd_entry_t **l1, pd_entry_t **l2,
    pt_entry_t **l3)
{
	pd_entry_t *l1p, *l2p;

	/* Get l1 directory entry. */
	l1p = pmap_l1(pmap, va);
	*l1 = l1p;

	if (l1p == NULL || (pmap_load(l1p) & PTE_V) == 0)
		return (false);

	if ((pmap_load(l1p) & PTE_RX) != 0) {
		*l2 = NULL;
		*l3 = NULL;
		return (true);
	}

	/* Get l2 directory entry. */
	l2p = pmap_l1_to_l2(l1p, va);
	*l2 = l2p;

	if (l2p == NULL || (pmap_load(l2p) & PTE_V) == 0)
		return (false);

	if ((pmap_load(l2p) & PTE_RX) != 0) {
		*l3 = NULL;
		return (true);
	}

	/* Get l3 page table entry. */
	*l3 = pmap_l2_to_l3(l2p, va);

	return (true);
}