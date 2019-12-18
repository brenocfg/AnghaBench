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
struct vm_domain {scalar_t__ vmd_free_count; scalar_t__ vmd_free_reserved; scalar_t__ vmd_interrupt_free_min; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ MIN_RECLAIM ; 
 int NRUNS ; 
 size_t RUN_INDEX (scalar_t__) ; 
 int VM_ALLOC_CLASS_MASK ; 
 int VM_ALLOC_INTERRUPT ; 
 int VM_ALLOC_SYSTEM ; 
 struct vm_domain* VM_DOMAIN (int) ; 
 scalar_t__ VM_PAGE_TO_PHYS (int /*<<< orphan*/ *) ; 
 int VPSC_ANY ; 
 int VPSC_NORESERV ; 
 int VPSC_NOSUPER ; 
 scalar_t__ curproc ; 
 scalar_t__ pageproc ; 
 int powerof2 (scalar_t__) ; 
 scalar_t__ ptoa (scalar_t__) ; 
 int vm_page_reclaim_run (int,int,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * vm_phys_scan_contig (int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ; 

bool
vm_page_reclaim_contig_domain(int domain, int req, u_long npages,
    vm_paddr_t low, vm_paddr_t high, u_long alignment, vm_paddr_t boundary)
{
	struct vm_domain *vmd;
	vm_paddr_t curr_low;
	vm_page_t m_run, m_runs[NRUNS];
	u_long count, reclaimed;
	int error, i, options, req_class;

	KASSERT(npages > 0, ("npages is 0"));
	KASSERT(powerof2(alignment), ("alignment is not a power of 2"));
	KASSERT(powerof2(boundary), ("boundary is not a power of 2"));
	req_class = req & VM_ALLOC_CLASS_MASK;

	/*
	 * The page daemon is allowed to dig deeper into the free page list.
	 */
	if (curproc == pageproc && req_class != VM_ALLOC_INTERRUPT)
		req_class = VM_ALLOC_SYSTEM;

	/*
	 * Return if the number of free pages cannot satisfy the requested
	 * allocation.
	 */
	vmd = VM_DOMAIN(domain);
	count = vmd->vmd_free_count;
	if (count < npages + vmd->vmd_free_reserved || (count < npages +
	    vmd->vmd_interrupt_free_min && req_class == VM_ALLOC_SYSTEM) ||
	    (count < npages && req_class == VM_ALLOC_INTERRUPT))
		return (false);

	/*
	 * Scan up to three times, relaxing the restrictions ("options") on
	 * the reclamation of reservations and superpages each time.
	 */
	for (options = VPSC_NORESERV;;) {
		/*
		 * Find the highest runs that satisfy the given constraints
		 * and restrictions, and record them in "m_runs".
		 */
		curr_low = low;
		count = 0;
		for (;;) {
			m_run = vm_phys_scan_contig(domain, npages, curr_low,
			    high, alignment, boundary, options);
			if (m_run == NULL)
				break;
			curr_low = VM_PAGE_TO_PHYS(m_run) + ptoa(npages);
			m_runs[RUN_INDEX(count)] = m_run;
			count++;
		}

		/*
		 * Reclaim the highest runs in LIFO (descending) order until
		 * the number of reclaimed pages, "reclaimed", is at least
		 * MIN_RECLAIM.  Reset "reclaimed" each time because each
		 * reclamation is idempotent, and runs will (likely) recur
		 * from one scan to the next as restrictions are relaxed.
		 */
		reclaimed = 0;
		for (i = 0; count > 0 && i < NRUNS; i++) {
			count--;
			m_run = m_runs[RUN_INDEX(count)];
			error = vm_page_reclaim_run(req_class, domain, npages,
			    m_run, high);
			if (error == 0) {
				reclaimed += npages;
				if (reclaimed >= MIN_RECLAIM)
					return (true);
			}
		}

		/*
		 * Either relax the restrictions on the next scan or return if
		 * the last scan had no restrictions.
		 */
		if (options == VPSC_NORESERV)
			options = VPSC_NOSUPER;
		else if (options == VPSC_NOSUPER)
			options = VPSC_ANY;
		else if (options == VPSC_ANY)
			return (reclaimed != 0);
	}
}