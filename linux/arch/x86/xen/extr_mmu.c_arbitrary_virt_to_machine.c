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
typedef  int /*<<< orphan*/  xmaddr_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  unsigned int phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 unsigned long PAGE_MASK ; 
 unsigned int PAGE_SHIFT ; 
 int /*<<< orphan*/  XMADDR (unsigned int) ; 
 int /*<<< orphan*/ * lookup_address (unsigned long,unsigned int*) ; 
 scalar_t__ pte_mfn (int /*<<< orphan*/ ) ; 
 scalar_t__ virt_addr_valid (void*) ; 
 int /*<<< orphan*/  virt_to_machine (void*) ; 

xmaddr_t arbitrary_virt_to_machine(void *vaddr)
{
	unsigned long address = (unsigned long)vaddr;
	unsigned int level;
	pte_t *pte;
	unsigned offset;

	/*
	 * if the PFN is in the linear mapped vaddr range, we can just use
	 * the (quick) virt_to_machine() p2m lookup
	 */
	if (virt_addr_valid(vaddr))
		return virt_to_machine(vaddr);

	/* otherwise we have to do a (slower) full page-table walk */

	pte = lookup_address(address, &level);
	BUG_ON(pte == NULL);
	offset = address & ~PAGE_MASK;
	return XMADDR(((phys_addr_t)pte_mfn(*pte) << PAGE_SHIFT) + offset);
}