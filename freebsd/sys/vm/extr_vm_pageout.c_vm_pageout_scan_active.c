#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_13__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  TYPE_2__* vm_object_t ;
struct vm_pagequeue {long pq_cnt; int /*<<< orphan*/  pq_pl; } ;
struct vm_domain {int vmd_last_active_scan; TYPE_1__* vmd_clock; struct vm_pagequeue* vmd_pagequeues; TYPE_1__* vmd_markers; } ;
struct scan_state {scalar_t__ scanned; } ;
struct mtx {int dummy; } ;
struct TYPE_21__ {scalar_t__ ref_count; } ;
struct TYPE_20__ {int flags; int aflags; scalar_t__ act_count; scalar_t__ dirty; int /*<<< orphan*/  object; } ;
struct TYPE_19__ {int /*<<< orphan*/  q; } ;

/* Variables and functions */
 scalar_t__ ACT_ADVANCE ; 
 int /*<<< orphan*/  ACT_DECLINE ; 
 scalar_t__ ACT_MAX ; 
 int PGA_REFERENCED ; 
 int PG_MARKER ; 
 size_t PQ_ACTIVE ; 
 int /*<<< orphan*/  PQ_INACTIVE ; 
 int /*<<< orphan*/  PQ_LAUNDRY ; 
 int /*<<< orphan*/  TAILQ_INSERT_AFTER (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ __predict_false (int) ; 
 scalar_t__ act_scan_laundry_weight ; 
 scalar_t__ atomic_load_ptr (int /*<<< orphan*/ *) ; 
 long hz ; 
 scalar_t__ min (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_unlock (struct mtx*) ; 
 TYPE_13__ plinks ; 
 int pmap_ts_referenced (TYPE_1__*) ; 
 int ticks ; 
 int /*<<< orphan*/  vm_page_aflag_clear (TYPE_1__*,int) ; 
 int /*<<< orphan*/  vm_page_change_lock (TYPE_1__*,struct mtx**) ; 
 int /*<<< orphan*/  vm_page_dequeue_deferred (TYPE_1__*) ; 
 size_t vm_page_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_swapqueue (TYPE_1__*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_page_wired (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_pageout_end_scan (struct scan_state*) ; 
 int /*<<< orphan*/  vm_pageout_init_scan (struct scan_state*,struct vm_pagequeue*,TYPE_1__*,TYPE_1__*,int) ; 
 TYPE_1__* vm_pageout_next (struct scan_state*,int) ; 
 long vm_pageout_update_period ; 
 int /*<<< orphan*/  vm_pagequeue_lock (struct vm_pagequeue*) ; 
 int /*<<< orphan*/  vm_pagequeue_unlock (struct vm_pagequeue*) ; 

__attribute__((used)) static void
vm_pageout_scan_active(struct vm_domain *vmd, int page_shortage)
{
	struct scan_state ss;
	struct mtx *mtx;
	vm_object_t object;
	vm_page_t m, marker;
	struct vm_pagequeue *pq;
	long min_scan;
	int act_delta, max_scan, scan_tick;

	marker = &vmd->vmd_markers[PQ_ACTIVE];
	pq = &vmd->vmd_pagequeues[PQ_ACTIVE];
	vm_pagequeue_lock(pq);

	/*
	 * If we're just idle polling attempt to visit every
	 * active page within 'update_period' seconds.
	 */
	scan_tick = ticks;
	if (vm_pageout_update_period != 0) {
		min_scan = pq->pq_cnt;
		min_scan *= scan_tick - vmd->vmd_last_active_scan;
		min_scan /= hz * vm_pageout_update_period;
	} else
		min_scan = 0;
	if (min_scan > 0 || (page_shortage > 0 && pq->pq_cnt > 0))
		vmd->vmd_last_active_scan = scan_tick;

	/*
	 * Scan the active queue for pages that can be deactivated.  Update
	 * the per-page activity counter and use it to identify deactivation
	 * candidates.  Held pages may be deactivated.
	 *
	 * To avoid requeuing each page that remains in the active queue, we
	 * implement the CLOCK algorithm.  To keep the implementation of the
	 * enqueue operation consistent for all page queues, we use two hands,
	 * represented by marker pages. Scans begin at the first hand, which
	 * precedes the second hand in the queue.  When the two hands meet,
	 * they are moved back to the head and tail of the queue, respectively,
	 * and scanning resumes.
	 */
	max_scan = page_shortage > 0 ? pq->pq_cnt : min_scan;
	mtx = NULL;
act_scan:
	vm_pageout_init_scan(&ss, pq, marker, &vmd->vmd_clock[0], max_scan);
	while ((m = vm_pageout_next(&ss, false)) != NULL) {
		if (__predict_false(m == &vmd->vmd_clock[1])) {
			vm_pagequeue_lock(pq);
			TAILQ_REMOVE(&pq->pq_pl, &vmd->vmd_clock[0], plinks.q);
			TAILQ_REMOVE(&pq->pq_pl, &vmd->vmd_clock[1], plinks.q);
			TAILQ_INSERT_HEAD(&pq->pq_pl, &vmd->vmd_clock[0],
			    plinks.q);
			TAILQ_INSERT_TAIL(&pq->pq_pl, &vmd->vmd_clock[1],
			    plinks.q);
			max_scan -= ss.scanned;
			vm_pageout_end_scan(&ss);
			goto act_scan;
		}
		if (__predict_false((m->flags & PG_MARKER) != 0))
			continue;

		vm_page_change_lock(m, &mtx);

		/*
		 * The page may have been disassociated from the queue
		 * or even freed while locks were dropped.  We thus must be
		 * careful whenever modifying page state.  Once the object lock
		 * has been acquired, we have a stable reference to the page.
		 */
		if (vm_page_queue(m) != PQ_ACTIVE)
			continue;

		/*
		 * Wired pages are dequeued lazily.
		 */
		if (vm_page_wired(m)) {
			vm_page_dequeue_deferred(m);
			continue;
		}

		/*
		 * A page's object pointer may be set to NULL before
		 * the object lock is acquired.
		 */
		object = (vm_object_t)atomic_load_ptr(&m->object);
		if (__predict_false(object == NULL))
			/*
			 * The page has been removed from its object.
			 */
			continue;

		/*
		 * Check to see "how much" the page has been used.
		 *
		 * Test PGA_REFERENCED after calling pmap_ts_referenced() so
		 * that a reference from a concurrently destroyed mapping is
		 * observed here and now.
		 *
		 * Perform an unsynchronized object ref count check.  While
		 * the page lock ensures that the page is not reallocated to
		 * another object, in particular, one with unmanaged mappings
		 * that cannot support pmap_ts_referenced(), two races are,
		 * nonetheless, possible:
		 * 1) The count was transitioning to zero, but we saw a non-
		 *    zero value.  pmap_ts_referenced() will return zero
		 *    because the page is not mapped.
		 * 2) The count was transitioning to one, but we saw zero.
		 *    This race delays the detection of a new reference.  At
		 *    worst, we will deactivate and reactivate the page.
		 */
		if (object->ref_count != 0)
			act_delta = pmap_ts_referenced(m);
		else
			act_delta = 0;
		if ((m->aflags & PGA_REFERENCED) != 0) {
			vm_page_aflag_clear(m, PGA_REFERENCED);
			act_delta++;
		}

		/*
		 * Advance or decay the act_count based on recent usage.
		 */
		if (act_delta != 0) {
			m->act_count += ACT_ADVANCE + act_delta;
			if (m->act_count > ACT_MAX)
				m->act_count = ACT_MAX;
		} else
			m->act_count -= min(m->act_count, ACT_DECLINE);

		if (m->act_count == 0) {
			/*
			 * When not short for inactive pages, let dirty pages go
			 * through the inactive queue before moving to the
			 * laundry queues.  This gives them some extra time to
			 * be reactivated, potentially avoiding an expensive
			 * pageout.  However, during a page shortage, the
			 * inactive queue is necessarily small, and so dirty
			 * pages would only spend a trivial amount of time in
			 * the inactive queue.  Therefore, we might as well
			 * place them directly in the laundry queue to reduce
			 * queuing overhead.
			 */
			if (page_shortage <= 0) {
				vm_page_swapqueue(m, PQ_ACTIVE, PQ_INACTIVE);
			} else {
				/*
				 * Calling vm_page_test_dirty() here would
				 * require acquisition of the object's write
				 * lock.  However, during a page shortage,
				 * directing dirty pages into the laundry
				 * queue is only an optimization and not a
				 * requirement.  Therefore, we simply rely on
				 * the opportunistic updates to the page's
				 * dirty field by the pmap.
				 */
				if (m->dirty == 0) {
					vm_page_swapqueue(m, PQ_ACTIVE,
					    PQ_INACTIVE);
					page_shortage -=
					    act_scan_laundry_weight;
				} else {
					vm_page_swapqueue(m, PQ_ACTIVE,
					    PQ_LAUNDRY);
					page_shortage--;
				}
			}
		}
	}
	if (mtx != NULL) {
		mtx_unlock(mtx);
		mtx = NULL;
	}
	vm_pagequeue_lock(pq);
	TAILQ_REMOVE(&pq->pq_pl, &vmd->vmd_clock[0], plinks.q);
	TAILQ_INSERT_AFTER(&pq->pq_pl, marker, &vmd->vmd_clock[0], plinks.q);
	vm_pageout_end_scan(&ss);
	vm_pagequeue_unlock(pq);
}