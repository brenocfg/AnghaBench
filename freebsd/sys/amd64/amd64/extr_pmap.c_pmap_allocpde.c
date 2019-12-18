#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_pindex_t ;
typedef  TYPE_1__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
struct rwlock {int dummy; } ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int pdp_entry_t ;
struct TYPE_5__ {int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 int NPDPEPGSHIFT ; 
 scalar_t__ NUPDE ; 
 int PG_FRAME ; 
 TYPE_1__* PHYS_TO_VM_PAGE (int) ; 
 TYPE_1__* _pmap_allocpte (int /*<<< orphan*/ ,scalar_t__,struct rwlock**) ; 
 int pmap_pde_pindex (int /*<<< orphan*/ ) ; 
 int* pmap_pdpe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pmap_valid_bit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static vm_page_t
pmap_allocpde(pmap_t pmap, vm_offset_t va, struct rwlock **lockp)
{
	vm_pindex_t pdpindex, ptepindex;
	pdp_entry_t *pdpe, PG_V;
	vm_page_t pdpg;

	PG_V = pmap_valid_bit(pmap);

retry:
	pdpe = pmap_pdpe(pmap, va);
	if (pdpe != NULL && (*pdpe & PG_V) != 0) {
		/* Add a reference to the pd page. */
		pdpg = PHYS_TO_VM_PAGE(*pdpe & PG_FRAME);
		pdpg->ref_count++;
	} else {
		/* Allocate a pd page. */
		ptepindex = pmap_pde_pindex(va);
		pdpindex = ptepindex >> NPDPEPGSHIFT;
		pdpg = _pmap_allocpte(pmap, NUPDE + pdpindex, lockp);
		if (pdpg == NULL && lockp != NULL)
			goto retry;
	}
	return (pdpg);
}