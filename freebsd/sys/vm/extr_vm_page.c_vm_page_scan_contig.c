#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  int vm_paddr_t ;
typedef  TYPE_2__* vm_object_t ;
typedef  int u_long ;
struct mtx {int dummy; } ;
struct TYPE_18__ {scalar_t__ type; scalar_t__ memattr; } ;
struct TYPE_17__ {int flags; int ref_count; int oflags; int order; TYPE_2__* object; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ OBJT_DEFAULT ; 
 scalar_t__ OBJT_SWAP ; 
 scalar_t__ OBJT_VNODE ; 
 int PG_FICTITIOUS ; 
 int PG_MARKER ; 
 scalar_t__ PQ_NONE ; 
 scalar_t__ VM_MEMATTR_DEFAULT ; 
 int VM_NFREEORDER ; 
 int /*<<< orphan*/  VM_OBJECT_RLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  VM_OBJECT_RUNLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  VM_OBJECT_TRYRLOCK (TYPE_2__*) ; 
 int VM_PAGE_TO_PHYS (TYPE_1__*) ; 
 int VPO_SWAPINPROG ; 
 int VPO_SWAPSLEEP ; 
 int VPO_UNMANAGED ; 
 int VPSC_NORESERV ; 
 int VPSC_NOSUPER ; 
 int atop (scalar_t__) ; 
 int /*<<< orphan*/  mtx_lock (struct mtx*) ; 
 int /*<<< orphan*/  mtx_unlock (struct mtx*) ; 
 scalar_t__ pmap_page_get_memattr (TYPE_1__*) ; 
 int powerof2 (int) ; 
 int ptoa (int) ; 
 scalar_t__ rounddown2 (int,int) ; 
 scalar_t__ roundup2 (int,int) ; 
 int /*<<< orphan*/  vm_page_busied (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_change_lock (TYPE_1__*,struct mtx**) ; 
 scalar_t__ vm_page_queue (TYPE_1__*) ; 
 scalar_t__ vm_page_wired (TYPE_1__*) ; 
 int vm_reserv_level (TYPE_1__*) ; 
 int vm_reserv_level_iffullpop (TYPE_1__*) ; 
 int vm_reserv_size (int) ; 

vm_page_t
vm_page_scan_contig(u_long npages, vm_page_t m_start, vm_page_t m_end,
    u_long alignment, vm_paddr_t boundary, int options)
{
	struct mtx *m_mtx;
	vm_object_t object;
	vm_paddr_t pa;
	vm_page_t m, m_run;
#if VM_NRESERVLEVEL > 0
	int level;
#endif
	int m_inc, order, run_ext, run_len;

	KASSERT(npages > 0, ("npages is 0"));
	KASSERT(powerof2(alignment), ("alignment is not a power of 2"));
	KASSERT(powerof2(boundary), ("boundary is not a power of 2"));
	m_run = NULL;
	run_len = 0;
	m_mtx = NULL;
	for (m = m_start; m < m_end && run_len < npages; m += m_inc) {
		KASSERT((m->flags & PG_MARKER) == 0,
		    ("page %p is PG_MARKER", m));
		KASSERT((m->flags & PG_FICTITIOUS) == 0 || m->ref_count >= 1,
		    ("fictitious page %p has invalid ref count", m));

		/*
		 * If the current page would be the start of a run, check its
		 * physical address against the end, alignment, and boundary
		 * conditions.  If it doesn't satisfy these conditions, either
		 * terminate the scan or advance to the next page that
		 * satisfies the failed condition.
		 */
		if (run_len == 0) {
			KASSERT(m_run == NULL, ("m_run != NULL"));
			if (m + npages > m_end)
				break;
			pa = VM_PAGE_TO_PHYS(m);
			if ((pa & (alignment - 1)) != 0) {
				m_inc = atop(roundup2(pa, alignment) - pa);
				continue;
			}
			if (rounddown2(pa ^ (pa + ptoa(npages) - 1),
			    boundary) != 0) {
				m_inc = atop(roundup2(pa, boundary) - pa);
				continue;
			}
		} else
			KASSERT(m_run != NULL, ("m_run == NULL"));

		vm_page_change_lock(m, &m_mtx);
		m_inc = 1;
retry:
		if (vm_page_wired(m))
			run_ext = 0;
#if VM_NRESERVLEVEL > 0
		else if ((level = vm_reserv_level(m)) >= 0 &&
		    (options & VPSC_NORESERV) != 0) {
			run_ext = 0;
			/* Advance to the end of the reservation. */
			pa = VM_PAGE_TO_PHYS(m);
			m_inc = atop(roundup2(pa + 1, vm_reserv_size(level)) -
			    pa);
		}
#endif
		else if ((object = m->object) != NULL) {
			/*
			 * The page is considered eligible for relocation if
			 * and only if it could be laundered or reclaimed by
			 * the page daemon.
			 */
			if (!VM_OBJECT_TRYRLOCK(object)) {
				mtx_unlock(m_mtx);
				VM_OBJECT_RLOCK(object);
				mtx_lock(m_mtx);
				if (m->object != object) {
					/*
					 * The page may have been freed.
					 */
					VM_OBJECT_RUNLOCK(object);
					goto retry;
				}
			}
			/* Don't care: PG_NODUMP, PG_ZERO. */
			if (object->type != OBJT_DEFAULT &&
			    object->type != OBJT_SWAP &&
			    object->type != OBJT_VNODE) {
				run_ext = 0;
#if VM_NRESERVLEVEL > 0
			} else if ((options & VPSC_NOSUPER) != 0 &&
			    (level = vm_reserv_level_iffullpop(m)) >= 0) {
				run_ext = 0;
				/* Advance to the end of the superpage. */
				pa = VM_PAGE_TO_PHYS(m);
				m_inc = atop(roundup2(pa + 1,
				    vm_reserv_size(level)) - pa);
#endif
			} else if (object->memattr == VM_MEMATTR_DEFAULT &&
			    vm_page_queue(m) != PQ_NONE && !vm_page_busied(m) &&
			    !vm_page_wired(m)) {
				/*
				 * The page is allocated but eligible for
				 * relocation.  Extend the current run by one
				 * page.
				 */
				KASSERT(pmap_page_get_memattr(m) ==
				    VM_MEMATTR_DEFAULT,
				    ("page %p has an unexpected memattr", m));
				KASSERT((m->oflags & (VPO_SWAPINPROG |
				    VPO_SWAPSLEEP | VPO_UNMANAGED)) == 0,
				    ("page %p has unexpected oflags", m));
				/* Don't care: PGA_NOSYNC. */
				run_ext = 1;
			} else
				run_ext = 0;
			VM_OBJECT_RUNLOCK(object);
#if VM_NRESERVLEVEL > 0
		} else if (level >= 0) {
			/*
			 * The page is reserved but not yet allocated.  In
			 * other words, it is still free.  Extend the current
			 * run by one page.
			 */
			run_ext = 1;
#endif
		} else if ((order = m->order) < VM_NFREEORDER) {
			/*
			 * The page is enqueued in the physical memory
			 * allocator's free page queues.  Moreover, it is the
			 * first page in a power-of-two-sized run of
			 * contiguous free pages.  Add these pages to the end
			 * of the current run, and jump ahead.
			 */
			run_ext = 1 << order;
			m_inc = 1 << order;
		} else {
			/*
			 * Skip the page for one of the following reasons: (1)
			 * It is enqueued in the physical memory allocator's
			 * free page queues.  However, it is not the first
			 * page in a run of contiguous free pages.  (This case
			 * rarely occurs because the scan is performed in
			 * ascending order.) (2) It is not reserved, and it is
			 * transitioning from free to allocated.  (Conversely,
			 * the transition from allocated to free for managed
			 * pages is blocked by the page lock.) (3) It is
			 * allocated but not contained by an object and not
			 * wired, e.g., allocated by Xen's balloon driver.
			 */
			run_ext = 0;
		}

		/*
		 * Extend or reset the current run of pages.
		 */
		if (run_ext > 0) {
			if (run_len == 0)
				m_run = m;
			run_len += run_ext;
		} else {
			if (run_len > 0) {
				m_run = NULL;
				run_len = 0;
			}
		}
	}
	if (m_mtx != NULL)
		mtx_unlock(m_mtx);
	if (run_len >= npages)
		return (m_run);
	return (NULL);
}