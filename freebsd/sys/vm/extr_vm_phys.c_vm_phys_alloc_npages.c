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
 int imin (int,int) ; 
 int /*<<< orphan*/  vm_domain_free_assert_locked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_freelist_rem (struct vm_freelist*,int /*<<< orphan*/ *,int) ; 
 int* vm_freelist_to_flind ; 
 int vm_ndomains ; 
 int /*<<< orphan*/  vm_phys_enq_range (int /*<<< orphan*/ *,int,struct vm_freelist*,int) ; 
 struct vm_freelist**** vm_phys_free_queues ; 
 int /*<<< orphan*/  vm_phys_set_pool (int,int /*<<< orphan*/ *,int) ; 

int
vm_phys_alloc_npages(int domain, int pool, int npages, vm_page_t ma[])
{
	struct vm_freelist *alt, *fl;
	vm_page_t m;
	int avail, end, flind, freelist, i, need, oind, pind;

	KASSERT(domain >= 0 && domain < vm_ndomains,
	    ("vm_phys_alloc_npages: domain %d is out of range", domain));
	KASSERT(pool < VM_NFREEPOOL,
	    ("vm_phys_alloc_npages: pool %d is out of range", pool));
	KASSERT(npages <= 1 << (VM_NFREEORDER - 1),
	    ("vm_phys_alloc_npages: npages %d is out of range", npages));
	vm_domain_free_assert_locked(VM_DOMAIN(domain));
	i = 0;
	for (freelist = 0; freelist < VM_NFREELIST; freelist++) {
		flind = vm_freelist_to_flind[freelist];
		if (flind < 0)
			continue;
		fl = vm_phys_free_queues[domain][flind][pool];
		for (oind = 0; oind < VM_NFREEORDER; oind++) {
			while ((m = TAILQ_FIRST(&fl[oind].pl)) != NULL) {
				vm_freelist_rem(fl, m, oind);
				avail = 1 << oind;
				need = imin(npages - i, avail);
				for (end = i + need; i < end;)
					ma[i++] = m++;
				if (need < avail) {
					/*
					 * Return excess pages to fl.  Its
					 * order [0, oind) queues are empty.
					 */
					vm_phys_enq_range(m, avail - need, fl,
					    1);
					return (npages);
				} else if (i == npages)
					return (npages);
			}
		}
		for (oind = VM_NFREEORDER - 1; oind >= 0; oind--) {
			for (pind = 0; pind < VM_NFREEPOOL; pind++) {
				alt = vm_phys_free_queues[domain][flind][pind];
				while ((m = TAILQ_FIRST(&alt[oind].pl)) !=
				    NULL) {
					vm_freelist_rem(alt, m, oind);
					vm_phys_set_pool(pool, m, oind);
					avail = 1 << oind;
					need = imin(npages - i, avail);
					for (end = i + need; i < end;)
						ma[i++] = m++;
					if (need < avail) {
						/*
						 * Return excess pages to fl.
						 * Its order [0, oind) queues
						 * are empty.
						 */
						vm_phys_enq_range(m, avail -
						    need, fl, 1);
						return (npages);
					} else if (i == npages)
						return (npages);
				}
			}
		}
	}
	return (i);
}