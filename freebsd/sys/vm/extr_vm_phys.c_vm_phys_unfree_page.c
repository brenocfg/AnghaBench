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
typedef  int vm_paddr_t ;
struct vm_phys_seg {int start; TYPE_1__* first_page; struct vm_freelist*** free_queues; int /*<<< orphan*/  domain; } ;
struct vm_freelist {int dummy; } ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_5__ {size_t segind; int order; int phys_addr; size_t pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VM_DOMAIN (int /*<<< orphan*/ ) ; 
 int VM_NFREEORDER ; 
 size_t atop (int) ; 
 int /*<<< orphan*/  vm_domain_free_assert_locked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_freelist_add (struct vm_freelist*,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_freelist_rem (struct vm_freelist*,TYPE_1__*,int) ; 
 struct vm_phys_seg* vm_phys_segs ; 

boolean_t
vm_phys_unfree_page(vm_page_t m)
{
	struct vm_freelist *fl;
	struct vm_phys_seg *seg;
	vm_paddr_t pa, pa_half;
	vm_page_t m_set, m_tmp;
	int order;

	/*
	 * First, find the contiguous, power of two-sized set of free
	 * physical pages containing the given physical page "m" and
	 * assign it to "m_set".
	 */
	seg = &vm_phys_segs[m->segind];
	vm_domain_free_assert_locked(VM_DOMAIN(seg->domain));
	for (m_set = m, order = 0; m_set->order == VM_NFREEORDER &&
	    order < VM_NFREEORDER - 1; ) {
		order++;
		pa = m->phys_addr & (~(vm_paddr_t)0 << (PAGE_SHIFT + order));
		if (pa >= seg->start)
			m_set = &seg->first_page[atop(pa - seg->start)];
		else
			return (FALSE);
	}
	if (m_set->order < order)
		return (FALSE);
	if (m_set->order == VM_NFREEORDER)
		return (FALSE);
	KASSERT(m_set->order < VM_NFREEORDER,
	    ("vm_phys_unfree_page: page %p has unexpected order %d",
	    m_set, m_set->order));

	/*
	 * Next, remove "m_set" from the free lists.  Finally, extract
	 * "m" from "m_set" using an iterative algorithm: While "m_set"
	 * is larger than a page, shrink "m_set" by returning the half
	 * of "m_set" that does not contain "m" to the free lists.
	 */
	fl = (*seg->free_queues)[m_set->pool];
	order = m_set->order;
	vm_freelist_rem(fl, m_set, order);
	while (order > 0) {
		order--;
		pa_half = m_set->phys_addr ^ (1 << (PAGE_SHIFT + order));
		if (m->phys_addr < pa_half)
			m_tmp = &seg->first_page[atop(pa_half - seg->start)];
		else {
			m_tmp = m_set;
			m_set = &seg->first_page[atop(pa_half - seg->start)];
		}
		vm_freelist_add(fl, m_tmp, order, 0);
	}
	KASSERT(m_set == m, ("vm_phys_unfree_page: fatal inconsistency"));
	return (TRUE);
}