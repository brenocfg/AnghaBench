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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int GFP_DMA32 ; 
 int GFP_NATIVE_MASK ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  VM_MEMATTR_DEFAULT ; 
 int /*<<< orphan*/  kmem_alloc_contig (size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_malloc (size_t,int) ; 

vm_offset_t
linux_alloc_kmem(gfp_t flags, unsigned int order)
{
	size_t size = ((size_t)PAGE_SIZE) << order;
	vm_offset_t addr;

	if ((flags & GFP_DMA32) == 0) {
		addr = kmem_malloc(size, flags & GFP_NATIVE_MASK);
	} else {
		addr = kmem_alloc_contig(size, flags & GFP_NATIVE_MASK, 0,
		    BUS_SPACE_MAXADDR_32BIT, PAGE_SIZE, 0, VM_MEMATTR_DEFAULT);
	}
	return (addr);
}