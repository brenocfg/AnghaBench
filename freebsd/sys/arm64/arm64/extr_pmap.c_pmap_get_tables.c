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
typedef  int /*<<< orphan*/  pt_entry_t ;
typedef  TYPE_1__* pmap_t ;
typedef  int /*<<< orphan*/  pd_entry_t ;
struct TYPE_4__ {int /*<<< orphan*/ * pm_l0; } ;

/* Variables and functions */
 int ATTR_DESCR_MASK ; 
 int L0_TABLE ; 
 int L1_BLOCK ; 
 int L1_TABLE ; 
 int L2_BLOCK ; 
 int L2_TABLE ; 
 int /*<<< orphan*/ * pmap_l0 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmap_l0_to_l1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmap_l1_to_l2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmap_l2_to_l3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pmap_load (int /*<<< orphan*/ *) ; 

bool
pmap_get_tables(pmap_t pmap, vm_offset_t va, pd_entry_t **l0, pd_entry_t **l1,
    pd_entry_t **l2, pt_entry_t **l3)
{
	pd_entry_t *l0p, *l1p, *l2p;

	if (pmap->pm_l0 == NULL)
		return (false);

	l0p = pmap_l0(pmap, va);
	*l0 = l0p;

	if ((pmap_load(l0p) & ATTR_DESCR_MASK) != L0_TABLE)
		return (false);

	l1p = pmap_l0_to_l1(l0p, va);
	*l1 = l1p;

	if ((pmap_load(l1p) & ATTR_DESCR_MASK) == L1_BLOCK) {
		*l2 = NULL;
		*l3 = NULL;
		return (true);
	}

	if ((pmap_load(l1p) & ATTR_DESCR_MASK) != L1_TABLE)
		return (false);

	l2p = pmap_l1_to_l2(l1p, va);
	*l2 = l2p;

	if ((pmap_load(l2p) & ATTR_DESCR_MASK) == L2_BLOCK) {
		*l3 = NULL;
		return (true);
	}

	if ((pmap_load(l2p) & ATTR_DESCR_MASK) != L2_TABLE)
		return (false);

	*l3 = pmap_l2_to_l3(l2p, va);

	return (true);
}