#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_15__ {int flags; int oflags; int aflags; scalar_t__ queue; scalar_t__ ref_count; scalar_t__ valid; int /*<<< orphan*/ * object; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PAGE_SIZE ; 
 int PGA_EXECUTABLE ; 
 int PGA_WRITEABLE ; 
 int PG_FICTITIOUS ; 
 int PG_PCPU_CACHE ; 
 int PG_ZERO ; 
 scalar_t__ PHYS_TO_DMAP (int /*<<< orphan*/ ) ; 
 scalar_t__ PMAP_HAS_DMAP ; 
 scalar_t__ PQ_NONE ; 
 int /*<<< orphan*/  VM_CNT_INC (int /*<<< orphan*/ ) ; 
 scalar_t__ VM_MEMATTR_DEFAULT ; 
 int /*<<< orphan*/  VM_PAGE_TO_PHYS (TYPE_1__*) ; 
 int VPO_UNMANAGED ; 
 scalar_t__ VPRC_OBJREF ; 
 int /*<<< orphan*/  atomic_thread_fence_acq () ; 
 int /*<<< orphan*/  panic (char*,TYPE_1__*) ; 
 scalar_t__ pmap_page_get_memattr (TYPE_1__*) ; 
 int /*<<< orphan*/  pmap_page_is_mapped (TYPE_1__*) ; 
 int /*<<< orphan*/  pmap_page_set_memattr (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  v_tfree ; 
 int /*<<< orphan*/  vm_page_dequeue_deferred_free (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_object_remove (TYPE_1__*) ; 
 scalar_t__ vm_page_sbusied (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_undirty (TYPE_1__*) ; 
 scalar_t__ vm_page_xbusied (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_xunbusy (TYPE_1__*) ; 
 scalar_t__ vm_reserv_free_page (TYPE_1__*) ; 

bool
vm_page_free_prep(vm_page_t m)
{

	/*
	 * Synchronize with threads that have dropped a reference to this
	 * page.
	 */
	atomic_thread_fence_acq();

#if defined(DIAGNOSTIC) && defined(PHYS_TO_DMAP)
	if (PMAP_HAS_DMAP && (m->flags & PG_ZERO) != 0) {
		uint64_t *p;
		int i;
		p = (uint64_t *)PHYS_TO_DMAP(VM_PAGE_TO_PHYS(m));
		for (i = 0; i < PAGE_SIZE / sizeof(uint64_t); i++, p++)
			KASSERT(*p == 0, ("vm_page_free_prep %p PG_ZERO %d %jx",
			    m, i, (uintmax_t)*p));
	}
#endif
	if ((m->oflags & VPO_UNMANAGED) == 0) {
		KASSERT(!pmap_page_is_mapped(m),
		    ("vm_page_free_prep: freeing mapped page %p", m));
		KASSERT((m->aflags & (PGA_EXECUTABLE | PGA_WRITEABLE)) == 0,
		    ("vm_page_free_prep: mapping flags set in page %p", m));
	} else {
		KASSERT(m->queue == PQ_NONE,
		    ("vm_page_free_prep: unmanaged page %p is queued", m));
	}
	VM_CNT_INC(v_tfree);

	if (vm_page_sbusied(m))
		panic("vm_page_free_prep: freeing shared busy page %p", m);

	if (m->object != NULL) {
		vm_page_object_remove(m);

		/*
		 * The object reference can be released without an atomic
		 * operation.
		 */
		KASSERT((m->flags & PG_FICTITIOUS) != 0 ||
		    m->ref_count == VPRC_OBJREF,
		    ("vm_page_free_prep: page %p has unexpected ref_count %u",
		    m, m->ref_count));
		m->object = NULL;
		m->ref_count -= VPRC_OBJREF;
	}

	if (vm_page_xbusied(m))
		vm_page_xunbusy(m);

	/*
	 * If fictitious remove object association and
	 * return.
	 */
	if ((m->flags & PG_FICTITIOUS) != 0) {
		KASSERT(m->ref_count == 1,
		    ("fictitious page %p is referenced", m));
		KASSERT(m->queue == PQ_NONE,
		    ("fictitious page %p is queued", m));
		return (false);
	}

	/*
	 * Pages need not be dequeued before they are returned to the physical
	 * memory allocator, but they must at least be marked for a deferred
	 * dequeue.
	 */
	if ((m->oflags & VPO_UNMANAGED) == 0)
		vm_page_dequeue_deferred_free(m);

	m->valid = 0;
	vm_page_undirty(m);

	if (m->ref_count != 0)
		panic("vm_page_free_prep: page %p has references", m);

	/*
	 * Restore the default memory attribute to the page.
	 */
	if (pmap_page_get_memattr(m) != VM_MEMATTR_DEFAULT)
		pmap_page_set_memattr(m, VM_MEMATTR_DEFAULT);

#if VM_NRESERVLEVEL > 0
	/*
	 * Determine whether the page belongs to a reservation.  If the page was
	 * allocated from a per-CPU cache, it cannot belong to a reservation, so
	 * as an optimization, we avoid the check in that case.
	 */
	if ((m->flags & PG_PCPU_CACHE) == 0 && vm_reserv_free_page(m))
		return (false);
#endif

	return (true);
}