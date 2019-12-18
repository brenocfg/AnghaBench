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
 int MAS2_G ; 
 int MAS2_I ; 
 int MAS2_M ; 
 int MAS2_W ; 
#define  VM_MEMATTR_CACHEABLE 133 
 int VM_MEMATTR_DEFAULT ; 
#define  VM_MEMATTR_PREFETCHABLE 132 
#define  VM_MEMATTR_UNCACHEABLE 131 
#define  VM_MEMATTR_WRITE_BACK 130 
#define  VM_MEMATTR_WRITE_COMBINING 129 
#define  VM_MEMATTR_WRITE_THROUGH 128 
 int _TLB_ENTRY_IO ; 
 int _TLB_ENTRY_MEM ; 
 TYPE_1__* physmem_regions ; 
 int physmem_regions_sz ; 

__attribute__((used)) static __inline uint32_t
tlb_calc_wimg(vm_paddr_t pa, vm_memattr_t ma)
{
	uint32_t attrib;
	int i;

	if (ma != VM_MEMATTR_DEFAULT) {
		switch (ma) {
		case VM_MEMATTR_UNCACHEABLE:
			return (MAS2_I | MAS2_G);
		case VM_MEMATTR_WRITE_COMBINING:
		case VM_MEMATTR_WRITE_BACK:
		case VM_MEMATTR_PREFETCHABLE:
			return (MAS2_I);
		case VM_MEMATTR_WRITE_THROUGH:
			return (MAS2_W | MAS2_M);
		case VM_MEMATTR_CACHEABLE:
			return (MAS2_M);
		}
	}

	/*
	 * Assume the page is cache inhibited and access is guarded unless
	 * it's in our available memory array.
	 */
	attrib = _TLB_ENTRY_IO;
	for (i = 0; i < physmem_regions_sz; i++) {
		if ((pa >= physmem_regions[i].mr_start) &&
		    (pa < (physmem_regions[i].mr_start +
		     physmem_regions[i].mr_size))) {
			attrib = _TLB_ENTRY_MEM;
			break;
		}
	}

	return (attrib);
}