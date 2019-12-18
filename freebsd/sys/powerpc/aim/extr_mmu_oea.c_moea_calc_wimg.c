#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_paddr_t ;
typedef  int vm_memattr_t ;
typedef  int uint32_t ;
struct TYPE_2__ {scalar_t__ mr_start; scalar_t__ mr_size; } ;

/* Variables and functions */
 int PTE_G ; 
 int PTE_I ; 
 int PTE_M ; 
 int PTE_W ; 
#define  VM_MEMATTR_CACHEABLE 133 
 int VM_MEMATTR_DEFAULT ; 
#define  VM_MEMATTR_PREFETCHABLE 132 
#define  VM_MEMATTR_UNCACHEABLE 131 
#define  VM_MEMATTR_WRITE_BACK 130 
#define  VM_MEMATTR_WRITE_COMBINING 129 
#define  VM_MEMATTR_WRITE_THROUGH 128 
 TYPE_1__* pregions ; 
 int pregions_sz ; 

__attribute__((used)) static __inline uint32_t
moea_calc_wimg(vm_paddr_t pa, vm_memattr_t ma)
{
	uint32_t pte_lo;
	int i;

	if (ma != VM_MEMATTR_DEFAULT) {
		switch (ma) {
		case VM_MEMATTR_UNCACHEABLE:
			return (PTE_I | PTE_G);
		case VM_MEMATTR_CACHEABLE:
			return (PTE_M);
		case VM_MEMATTR_WRITE_COMBINING:
		case VM_MEMATTR_WRITE_BACK:
		case VM_MEMATTR_PREFETCHABLE:
			return (PTE_I);
		case VM_MEMATTR_WRITE_THROUGH:
			return (PTE_W | PTE_M);
		}
	}

	/*
	 * Assume the page is cache inhibited and access is guarded unless
	 * it's in our available memory array.
	 */
	pte_lo = PTE_I | PTE_G;
	for (i = 0; i < pregions_sz; i++) {
		if ((pa >= pregions[i].mr_start) &&
		    (pa < (pregions[i].mr_start + pregions[i].mr_size))) {
			pte_lo = PTE_M;
			break;
		}
	}

	return pte_lo;
}