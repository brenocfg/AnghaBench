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
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  scalar_t__ vm_offset_t ;
struct spglist {int dummy; } ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  scalar_t__ pd_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTE_TO_PHYS (scalar_t__) ; 
 scalar_t__ VM_MAXUSER_ADDRESS ; 
 int pmap_unwire_ptp (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,struct spglist*) ; 

__attribute__((used)) static int
pmap_unuse_pt(pmap_t pmap, vm_offset_t va, pd_entry_t ptepde,
    struct spglist *free)
{
	vm_page_t mpte;

	if (va >= VM_MAXUSER_ADDRESS)
		return (0);
	KASSERT(ptepde != 0, ("pmap_unuse_pt: ptepde != 0"));
	mpte = PHYS_TO_VM_PAGE(PTE_TO_PHYS(ptepde));
	return (pmap_unwire_ptp(pmap, va, mpte, free));
}