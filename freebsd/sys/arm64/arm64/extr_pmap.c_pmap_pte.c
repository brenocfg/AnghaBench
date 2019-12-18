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
typedef  int pt_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int pd_entry_t ;

/* Variables and functions */
 int ATTR_DESCR_MASK ; 
 int L1_BLOCK ; 
 int L1_TABLE ; 
 int L2_BLOCK ; 
 int L2_TABLE ; 
 int L3_PAGE ; 
 int* pmap_l1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* pmap_l1_to_l2 (int*,int /*<<< orphan*/ ) ; 
 int* pmap_l2_to_l3 (int*,int /*<<< orphan*/ ) ; 
 int pmap_load (int*) ; 

__attribute__((used)) static __inline pt_entry_t *
pmap_pte(pmap_t pmap, vm_offset_t va, int *level)
{
	pd_entry_t *l1, *l2, desc;
	pt_entry_t *l3;

	l1 = pmap_l1(pmap, va);
	if (l1 == NULL) {
		*level = 0;
		return (NULL);
	}
	desc = pmap_load(l1) & ATTR_DESCR_MASK;
	if (desc == L1_BLOCK) {
		*level = 1;
		return (l1);
	}

	if (desc != L1_TABLE) {
		*level = 1;
		return (NULL);
	}

	l2 = pmap_l1_to_l2(l1, va);
	desc = pmap_load(l2) & ATTR_DESCR_MASK;
	if (desc == L2_BLOCK) {
		*level = 2;
		return (l2);
	}

	if (desc != L2_TABLE) {
		*level = 2;
		return (NULL);
	}

	*level = 3;
	l3 = pmap_l2_to_l3(l2, va);
	if ((pmap_load(l3) & ATTR_DESCR_MASK) != L3_PAGE)
		return (NULL);

	return (l3);
}