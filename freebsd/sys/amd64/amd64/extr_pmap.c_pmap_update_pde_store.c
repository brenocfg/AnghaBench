#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* pmap_t ;
typedef  int /*<<< orphan*/  pd_entry_t ;
struct TYPE_3__ {int pm_type; int /*<<< orphan*/  pm_eptgen; } ;

/* Variables and functions */
#define  PT_EPT 130 
#define  PT_RVI 129 
#define  PT_X86 128 
 int /*<<< orphan*/  atomic_add_acq_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  pde_store (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pmap_update_pde_store(pmap_t pmap, pd_entry_t *pde, pd_entry_t newpde)
{

	switch (pmap->pm_type) {
	case PT_X86:
		break;
	case PT_RVI:
	case PT_EPT:
		/*
		 * XXX
		 * This is a little bogus since the generation number is
		 * supposed to be bumped up when a region of the address
		 * space is invalidated in the page tables.
		 *
		 * In this case the old PDE entry is valid but yet we want
		 * to make sure that any mappings using the old entry are
		 * invalidated in the TLB.
		 *
		 * The reason this works as expected is because we rendezvous
		 * "all" host cpus and force any vcpu context to exit as a
		 * side-effect.
		 */
		atomic_add_acq_long(&pmap->pm_eptgen, 1);
		break;
	default:
		panic("pmap_update_pde_store: bad pm_type %d", pmap->pm_type);
	}
	pde_store(pde, newpde);
}