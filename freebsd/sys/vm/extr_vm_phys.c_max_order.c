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

/* Variables and functions */
 int PAGE_SHIFT ; 
 scalar_t__ VM_NFREEORDER ; 
 int VM_PAGE_TO_PHYS (int /*<<< orphan*/ ) ; 
 scalar_t__ ffsl (int) ; 
 int min (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
max_order(vm_page_t m)
{

	/*
	 * Unsigned "min" is used here so that "order" is assigned
	 * "VM_NFREEORDER - 1" when "m"'s physical address is zero
	 * or the low-order bits of its physical address are zero
	 * because the size of a physical address exceeds the size of
	 * a long.
	 */
	return (min(ffsl(VM_PAGE_TO_PHYS(m) >> PAGE_SHIFT) - 1,
	    VM_NFREEORDER - 1));
}