#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  int u_int ;
struct vm_freelist {int dummy; } ;
struct TYPE_5__ {int order; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PAGE_SIZE ; 
 int VM_NFREEORDER ; 
 int VM_PAGE_TO_PHYS (TYPE_1__*) ; 
 int ffs (int) ; 
 int fls (int) ; 
 int /*<<< orphan*/  vm_freelist_add (struct vm_freelist*,TYPE_1__*,int,int) ; 

__attribute__((used)) static void
vm_phys_enq_range(vm_page_t m, u_int npages, struct vm_freelist *fl, int tail)
{
	u_int n;
	int order;

	KASSERT(npages > 0, ("vm_phys_enq_range: npages is 0"));
	KASSERT(((VM_PAGE_TO_PHYS(m) + npages * PAGE_SIZE) &
	    ((PAGE_SIZE << (fls(npages) - 1)) - 1)) == 0,
	    ("vm_phys_enq_range: page %p and npages %u are misaligned",
	    m, npages));
	do {
		KASSERT(m->order == VM_NFREEORDER,
		    ("vm_phys_enq_range: page %p has unexpected order %d",
		    m, m->order));
		order = ffs(npages) - 1;
		KASSERT(order < VM_NFREEORDER,
		    ("vm_phys_enq_range: order %d is out of range", order));
		vm_freelist_add(fl, m, order, tail);
		n = 1 << order;
		m += n;
		npages -= n;
	} while (npages > 0);
}