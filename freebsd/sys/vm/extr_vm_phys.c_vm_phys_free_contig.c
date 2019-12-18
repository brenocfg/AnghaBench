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
typedef  scalar_t__ vm_page_t ;
typedef  scalar_t__ u_long ;

/* Variables and functions */
 int VM_NFREEORDER ; 
 int max_order (scalar_t__) ; 
 int /*<<< orphan*/  vm_domain_free_assert_locked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_pagequeue_domain (scalar_t__) ; 
 int /*<<< orphan*/  vm_phys_enqueue_contig (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vm_phys_free_pages (scalar_t__,int) ; 

void
vm_phys_free_contig(vm_page_t m, u_long npages)
{
	int order_start, order_end;
	vm_page_t m_start, m_end;

	vm_domain_free_assert_locked(vm_pagequeue_domain(m));

	m_start = m;
	order_start = max_order(m_start);
	if (order_start < VM_NFREEORDER - 1)
		m_start += 1 << order_start;
	m_end = m + npages;
	order_end = max_order(m_end);
	if (order_end < VM_NFREEORDER - 1)
		m_end -= 1 << order_end;
	/*
	 * Avoid unnecessary coalescing by freeing the pages at the start and
	 * end of the range last.
	 */
	if (m_start < m_end)
		vm_phys_enqueue_contig(m_start, m_end - m_start);
	if (order_start < VM_NFREEORDER - 1)
		vm_phys_free_pages(m, order_start);
	if (order_end < VM_NFREEORDER - 1)
		vm_phys_free_pages(m_end, order_end);
}