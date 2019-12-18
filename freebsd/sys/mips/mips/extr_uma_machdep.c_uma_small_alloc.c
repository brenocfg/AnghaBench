#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  TYPE_1__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  int /*<<< orphan*/  uma_zone_t ;
typedef  int /*<<< orphan*/  u_int8_t ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPS_KSEG0_LARGEST_PHYS ; 
 scalar_t__ MIPS_PHYS_TO_DIRECT (int /*<<< orphan*/ ) ; 
 int M_NODUMP ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PG_ZERO ; 
 int /*<<< orphan*/  UMA_SLAB_PRIV ; 
 int VM_ALLOC_NOWAIT ; 
 int VM_ALLOC_WAITFAIL ; 
 int VM_ALLOC_WAITOK ; 
 int VM_ALLOC_WIRED ; 
 int /*<<< orphan*/  VM_FREELIST_DIRECT ; 
 int /*<<< orphan*/  VM_PAGE_TO_PHYS (TYPE_1__*) ; 
 int /*<<< orphan*/  bzero (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_add_page (int /*<<< orphan*/ ) ; 
 int malloc2vm_flags (int) ; 
 TYPE_1__* vm_page_alloc_freelist_domain (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ vm_page_reclaim_contig (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_wait (int /*<<< orphan*/ *) ; 

void *
uma_small_alloc(uma_zone_t zone, vm_size_t bytes, int domain, u_int8_t *flags,
    int wait)
{
	vm_paddr_t pa;
	vm_page_t m;
	int pflags;
	void *va;

	*flags = UMA_SLAB_PRIV;
	pflags = malloc2vm_flags(wait) | VM_ALLOC_WIRED;
#ifndef __mips_n64
	pflags &= ~(VM_ALLOC_WAITOK | VM_ALLOC_WAITFAIL);
	pflags |= VM_ALLOC_NOWAIT;
#endif

	for (;;) {
		m = vm_page_alloc_freelist_domain(domain, VM_FREELIST_DIRECT,
		    pflags);
#ifndef __mips_n64
		if (m == NULL && vm_page_reclaim_contig(pflags, 1,
		    0, MIPS_KSEG0_LARGEST_PHYS, PAGE_SIZE, 0))
			continue;
#endif
		if (m != NULL)
			break;
		if ((wait & M_NOWAIT) != 0)
			return (NULL);
		vm_wait(NULL);
	}

	pa = VM_PAGE_TO_PHYS(m);
	if ((wait & M_NODUMP) == 0)
		dump_add_page(pa);
	va = (void *)MIPS_PHYS_TO_DIRECT(pa);
	if ((wait & M_ZERO) && (m->flags & PG_ZERO) == 0)
		bzero(va, PAGE_SIZE);
	return (va);
}