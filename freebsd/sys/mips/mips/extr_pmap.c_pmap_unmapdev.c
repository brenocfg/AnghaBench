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
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  int vm_offset_t ;

/* Variables and functions */
 int MIPS_KSEG1_END ; 
 int MIPS_KSEG1_START ; 
 int PAGE_MASK ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  kva_free (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roundup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int trunc_page (int) ; 

void
pmap_unmapdev(vm_offset_t va, vm_size_t size)
{
#ifndef __mips_n64
	vm_offset_t base, offset;

	/* If the address is within KSEG1 then there is nothing to do */
	if (va >= MIPS_KSEG1_START && va <= MIPS_KSEG1_END)
		return;

	base = trunc_page(va);
	offset = va & PAGE_MASK;
	size = roundup(size + offset, PAGE_SIZE);
	kva_free(base, size);
#endif
}