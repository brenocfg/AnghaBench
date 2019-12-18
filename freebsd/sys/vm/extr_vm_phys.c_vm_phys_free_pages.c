#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  int vm_paddr_t ;
struct vm_phys_seg {int start; int end; struct vm_freelist*** free_queues; TYPE_1__* first_page; int /*<<< orphan*/  domain; } ;
struct vm_freelist {int dummy; } ;
struct TYPE_7__ {int order; size_t pool; size_t segind; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  VM_DOMAIN (int /*<<< orphan*/ ) ; 
 int VM_NFREEORDER ; 
 size_t VM_NFREEPOOL ; 
 int VM_PAGE_TO_PHYS (TYPE_1__*) ; 
 size_t atop (int) ; 
 int /*<<< orphan*/  vm_domain_free_assert_locked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_freelist_add (struct vm_freelist*,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  vm_freelist_rem (struct vm_freelist*,TYPE_1__*,int) ; 
 struct vm_phys_seg* vm_phys_segs ; 
 int /*<<< orphan*/  vm_phys_set_pool (size_t,TYPE_1__*,int) ; 

void
vm_phys_free_pages(vm_page_t m, int order)
{
	struct vm_freelist *fl;
	struct vm_phys_seg *seg;
	vm_paddr_t pa;
	vm_page_t m_buddy;

	KASSERT(m->order == VM_NFREEORDER,
	    ("vm_phys_free_pages: page %p has unexpected order %d",
	    m, m->order));
	KASSERT(m->pool < VM_NFREEPOOL,
	    ("vm_phys_free_pages: page %p has unexpected pool %d",
	    m, m->pool));
	KASSERT(order < VM_NFREEORDER,
	    ("vm_phys_free_pages: order %d is out of range", order));
	seg = &vm_phys_segs[m->segind];
	vm_domain_free_assert_locked(VM_DOMAIN(seg->domain));
	if (order < VM_NFREEORDER - 1) {
		pa = VM_PAGE_TO_PHYS(m);
		do {
			pa ^= ((vm_paddr_t)1 << (PAGE_SHIFT + order));
			if (pa < seg->start || pa >= seg->end)
				break;
			m_buddy = &seg->first_page[atop(pa - seg->start)];
			if (m_buddy->order != order)
				break;
			fl = (*seg->free_queues)[m_buddy->pool];
			vm_freelist_rem(fl, m_buddy, order);
			if (m_buddy->pool != m->pool)
				vm_phys_set_pool(m->pool, m_buddy, order);
			order++;
			pa &= ~(((vm_paddr_t)1 << (PAGE_SHIFT + order)) - 1);
			m = &seg->first_page[atop(pa - seg->start)];
		} while (order < VM_NFREEORDER - 1);
	}
	fl = (*seg->free_queues)[m->pool];
	vm_freelist_add(fl, m, order, 1);
}