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
typedef  scalar_t__ vm_paddr_t ;
typedef  scalar_t__ u_long ;
struct vm_phys_seg {scalar_t__ start; int domain; scalar_t__ end; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  VM_DOMAIN (int) ; 
 int powerof2 (scalar_t__) ; 
 scalar_t__ ptoa (scalar_t__) ; 
 int /*<<< orphan*/  vm_domain_free_assert_locked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vm_phys_alloc_seg_contig (struct vm_phys_seg*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int vm_phys_nsegs ; 
 struct vm_phys_seg* vm_phys_segs ; 

vm_page_t
vm_phys_alloc_contig(int domain, u_long npages, vm_paddr_t low, vm_paddr_t high,
    u_long alignment, vm_paddr_t boundary)
{
	vm_paddr_t pa_end, pa_start;
	vm_page_t m_run;
	struct vm_phys_seg *seg;
	int segind;

	KASSERT(npages > 0, ("npages is 0"));
	KASSERT(powerof2(alignment), ("alignment is not a power of 2"));
	KASSERT(powerof2(boundary), ("boundary is not a power of 2"));
	vm_domain_free_assert_locked(VM_DOMAIN(domain));
	if (low >= high)
		return (NULL);
	m_run = NULL;
	for (segind = vm_phys_nsegs - 1; segind >= 0; segind--) {
		seg = &vm_phys_segs[segind];
		if (seg->start >= high || seg->domain != domain)
			continue;
		if (low >= seg->end)
			break;
		if (low <= seg->start)
			pa_start = seg->start;
		else
			pa_start = low;
		if (high < seg->end)
			pa_end = high;
		else
			pa_end = seg->end;
		if (pa_end - pa_start < ptoa(npages))
			continue;
		m_run = vm_phys_alloc_seg_contig(seg, npages, low, high,
		    alignment, boundary);
		if (m_run != NULL)
			break;
	}
	return (m_run);
}