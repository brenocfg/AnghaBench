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
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  int /*<<< orphan*/  uma_zone_t ;
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  DOMAINSET_FIXED (int) ; 
 int /*<<< orphan*/  UMA_SLAB_KERNEL ; 
 int /*<<< orphan*/  VM_MEMATTR_DEFAULT ; 
 scalar_t__ kmem_alloc_contig_domainset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
mbuf_jumbo_alloc(uma_zone_t zone, vm_size_t bytes, int domain, uint8_t *flags,
    int wait)
{

	/* Inform UMA that this allocator uses kernel_map/object. */
	*flags = UMA_SLAB_KERNEL;
	return ((void *)kmem_alloc_contig_domainset(DOMAINSET_FIXED(domain),
	    bytes, wait, (vm_paddr_t)0, ~(vm_paddr_t)0, 1, 0,
	    VM_MEMATTR_DEFAULT));
}