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
typedef  int /*<<< orphan*/  pt1_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 scalar_t__ VM_MAXUSER_ADDRESS ; 
 int /*<<< orphan*/  pmap_pte1 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pmap_unwire_pt2 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,struct spglist*) ; 
 int /*<<< orphan*/  pte1_link_pa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte1_load (int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
pmap_unuse_pt2(pmap_t pmap, vm_offset_t va, struct spglist *free)
{
	pt1_entry_t pte1;
	vm_page_t mpte;

	if (va >= VM_MAXUSER_ADDRESS)
		return (FALSE);
	pte1 = pte1_load(pmap_pte1(pmap, va));
	mpte = PHYS_TO_VM_PAGE(pte1_link_pa(pte1));
	return (pmap_unwire_pt2(pmap, va, mpte, free));
}