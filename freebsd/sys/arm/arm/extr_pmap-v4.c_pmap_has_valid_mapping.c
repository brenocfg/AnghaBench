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
typedef  int /*<<< orphan*/  pd_entry_t ;

/* Variables and functions */
 int L2_TYPE_INV ; 
 int L2_TYPE_MASK ; 
 scalar_t__ pmap_get_pde_pte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int**) ; 

__attribute__((used)) static int
pmap_has_valid_mapping(pmap_t pm, vm_offset_t va)
{
	pd_entry_t *pde;
	pt_entry_t *ptep;

	if (pmap_get_pde_pte(pm, va, &pde, &ptep) &&
	    ptep && ((*ptep & L2_TYPE_MASK) != L2_TYPE_INV))
		return (1);

	return (0);
}