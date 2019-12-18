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
typedef  int /*<<< orphan*/  uma_zone_t ;
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  DOMAINSET_FIXED (int) ; 
 int /*<<< orphan*/  UMA_SLAB_KERNEL ; 
 int /*<<< orphan*/  VM_MEMATTR_UNCACHEABLE ; 
 scalar_t__ kmem_alloc_attr_domainset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 

void *
busdma_bufalloc_alloc_uncacheable(uma_zone_t zone, vm_size_t size, int domain,
    uint8_t *pflag, int wait)
{

#ifdef VM_MEMATTR_UNCACHEABLE
	/* Inform UMA that this allocator uses kernel_arena/object. */
	*pflag = UMA_SLAB_KERNEL;

	return ((void *)kmem_alloc_attr_domainset(DOMAINSET_FIXED(domain), size,
	    wait, 0, BUS_SPACE_MAXADDR, VM_MEMATTR_UNCACHEABLE));
#else
	panic("VM_MEMATTR_UNCACHEABLE unavailable");
#endif	/* VM_MEMATTR_UNCACHEABLE */
}