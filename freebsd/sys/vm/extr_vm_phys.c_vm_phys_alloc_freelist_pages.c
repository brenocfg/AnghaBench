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
typedef  int /*<<< orphan*/ * vm_page_t ;
struct vm_freelist {int /*<<< orphan*/  pl; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/ * TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VM_DOMAIN (int) ; 
 int VM_NFREELIST ; 
 int VM_NFREEORDER ; 
 int VM_NFREEPOOL ; 
 int /*<<< orphan*/  vm_domain_free_assert_locked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_freelist_rem (struct vm_freelist*,int /*<<< orphan*/ *,int) ; 
 int* vm_freelist_to_flind ; 
 int vm_ndomains ; 
 struct vm_freelist**** vm_phys_free_queues ; 
 int /*<<< orphan*/  vm_phys_set_pool (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vm_phys_split_pages (int /*<<< orphan*/ *,int,struct vm_freelist*,int,int) ; 

vm_page_t
vm_phys_alloc_freelist_pages(int domain, int freelist, int pool, int order)
{
	struct vm_freelist *alt, *fl;
	vm_page_t m;
	int oind, pind, flind;

	KASSERT(domain >= 0 && domain < vm_ndomains,
	    ("vm_phys_alloc_freelist_pages: domain %d is out of range",
	    domain));
	KASSERT(freelist < VM_NFREELIST,
	    ("vm_phys_alloc_freelist_pages: freelist %d is out of range",
	    freelist));
	KASSERT(pool < VM_NFREEPOOL,
	    ("vm_phys_alloc_freelist_pages: pool %d is out of range", pool));
	KASSERT(order < VM_NFREEORDER,
	    ("vm_phys_alloc_freelist_pages: order %d is out of range", order));

	flind = vm_freelist_to_flind[freelist];
	/* Check if freelist is present */
	if (flind < 0)
		return (NULL);

	vm_domain_free_assert_locked(VM_DOMAIN(domain));
	fl = &vm_phys_free_queues[domain][flind][pool][0];
	for (oind = order; oind < VM_NFREEORDER; oind++) {
		m = TAILQ_FIRST(&fl[oind].pl);
		if (m != NULL) {
			vm_freelist_rem(fl, m, oind);
			/* The order [order, oind) queues are empty. */
			vm_phys_split_pages(m, oind, fl, order, 1);
			return (m);
		}
	}

	/*
	 * The given pool was empty.  Find the largest
	 * contiguous, power-of-two-sized set of pages in any
	 * pool.  Transfer these pages to the given pool, and
	 * use them to satisfy the allocation.
	 */
	for (oind = VM_NFREEORDER - 1; oind >= order; oind--) {
		for (pind = 0; pind < VM_NFREEPOOL; pind++) {
			alt = &vm_phys_free_queues[domain][flind][pind][0];
			m = TAILQ_FIRST(&alt[oind].pl);
			if (m != NULL) {
				vm_freelist_rem(alt, m, oind);
				vm_phys_set_pool(pool, m, oind);
				/* The order [order, oind) queues are empty. */
				vm_phys_split_pages(m, oind, fl, order, 1);
				return (m);
			}
		}
	}
	return (NULL);
}