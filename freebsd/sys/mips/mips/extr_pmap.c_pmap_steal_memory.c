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
typedef  scalar_t__ vm_size_t ;
typedef  scalar_t__ vm_paddr_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 scalar_t__ MIPS_DIRECT_MAPPABLE (scalar_t__) ; 
 scalar_t__ MIPS_PHYS_TO_DIRECT (scalar_t__) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__* phys_avail ; 
 scalar_t__ round_page (scalar_t__) ; 

vm_offset_t
pmap_steal_memory(vm_size_t size)
{
	vm_paddr_t bank_size, pa;
	vm_offset_t va;

	size = round_page(size);
	bank_size = phys_avail[1] - phys_avail[0];
	while (size > bank_size) {
		int i;

		for (i = 0; phys_avail[i + 2]; i += 2) {
			phys_avail[i] = phys_avail[i + 2];
			phys_avail[i + 1] = phys_avail[i + 3];
		}
		phys_avail[i] = 0;
		phys_avail[i + 1] = 0;
		if (!phys_avail[0])
			panic("pmap_steal_memory: out of memory");
		bank_size = phys_avail[1] - phys_avail[0];
	}

	pa = phys_avail[0];
	phys_avail[0] += size;
	if (MIPS_DIRECT_MAPPABLE(pa) == 0)
		panic("Out of memory below 512Meg?");
	va = MIPS_PHYS_TO_DIRECT(pa);
	bzero((caddr_t)va, size);
	return (va);
}