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
typedef  int /*<<< orphan*/  vm_paddr_t ;
struct malloc_type {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_MEMATTR_DEFAULT ; 
 scalar_t__ kmem_alloc_contig (unsigned long,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc_type_allocated (struct malloc_type*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_page (unsigned long) ; 

void *
contigmalloc(unsigned long size, struct malloc_type *type, int flags,
    vm_paddr_t low, vm_paddr_t high, unsigned long alignment,
    vm_paddr_t boundary)
{
	void *ret;

	ret = (void *)kmem_alloc_contig(size, flags, low, high, alignment,
	    boundary, VM_MEMATTR_DEFAULT);
	if (ret != NULL)
		malloc_type_allocated(type, round_page(size));
	return (ret);
}