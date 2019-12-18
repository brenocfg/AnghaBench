#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  TYPE_2__* vm_object_t ;
struct vm_pagequeue {scalar_t__ pq_cnt; } ;
struct vm_domain {scalar_t__ vmd_laundry_request; int vmd_clean_pages_freed; struct vm_pagequeue* vmd_pagequeues; TYPE_1__* vmd_markers; int /*<<< orphan*/  vmd_pageout_deficit; } ;
struct vm_batchqueue {int dummy; } ;
struct scan_state {struct vm_batchqueue bq; } ;
struct mtx {int dummy; } ;
struct TYPE_27__ {scalar_t__ ref_count; int flags; } ;
struct TYPE_26__ {int flags; int aflags; scalar_t__ dirty; int /*<<< orphan*/  queue; int /*<<< orphan*/  act_count; TYPE_2__* object; } ;

/* Variables and functions */
 scalar_t__ ACT_ADVANCE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int OBJ_DEAD ; 
 int PGA_ENQUEUED ; 
 int PGA_QUEUE_STATE_MASK ; 
 int PGA_REFERENCED ; 
 int PGA_REQUEUE ; 
 int PGA_REQUEUE_HEAD ; 
 int PG_MARKER ; 
 size_t PQ_INACTIVE ; 
 size_t PQ_LAUNDRY ; 
 int /*<<< orphan*/  PQ_NONE ; 
 int /*<<< orphan*/  VM_CNT_ADD (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VM_CNT_INC (int /*<<< orphan*/ ) ; 
 scalar_t__ VM_LAUNDRY_BACKGROUND ; 
 scalar_t__ VM_LAUNDRY_IDLE ; 
 scalar_t__ VM_LAUNDRY_SHORTFALL ; 
 int /*<<< orphan*/  VM_OBJECT_TRYWLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (TYPE_2__*) ; 
 scalar_t__ __predict_false (int) ; 
 scalar_t__ atomic_load_acq_int (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_load_ptr (TYPE_2__**) ; 
 int atomic_readandclear_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (struct mtx*) ; 
 int /*<<< orphan*/  mtx_unlock (struct mtx*) ; 
 int /*<<< orphan*/  pmap_page_is_mapped (TYPE_1__*) ; 
 int pmap_ts_referenced (TYPE_1__*) ; 
 int /*<<< orphan*/  swapdev_enabled ; 
 int /*<<< orphan*/  v_dfree ; 
 int /*<<< orphan*/  v_pdshortfalls ; 
 int /*<<< orphan*/  v_reactivated ; 
 int /*<<< orphan*/  vm_batchqueue_init (struct vm_batchqueue*) ; 
 int /*<<< orphan*/  vm_page_activate (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_aflag_clear (TYPE_1__*,int) ; 
 int /*<<< orphan*/  vm_page_aflag_set (TYPE_1__*,int) ; 
 int /*<<< orphan*/  vm_page_change_lock (TYPE_1__*,struct mtx**) ; 
 int /*<<< orphan*/  vm_page_dequeue_deferred (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_free (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_launder (TYPE_1__*) ; 
 scalar_t__ vm_page_none_valid (TYPE_1__*) ; 
 size_t vm_page_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_test_dirty (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_try_remove_all (TYPE_1__*) ; 
 scalar_t__ vm_page_tryxbusy (TYPE_1__*) ; 
 int vm_page_wired (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_xunbusy (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_pageout_end_scan (struct scan_state*) ; 
 int /*<<< orphan*/  vm_pageout_init_scan (struct scan_state*,struct vm_pagequeue*,TYPE_1__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  vm_pageout_mightbe_oom (struct vm_domain*,int,int) ; 
 TYPE_1__* vm_pageout_next (struct scan_state*,int) ; 
 int /*<<< orphan*/  vm_pageout_reinsert_inactive (struct scan_state*,struct vm_batchqueue*,TYPE_1__*) ; 
 int /*<<< orphan*/  vm_pagequeue_lock (struct vm_pagequeue*) ; 
 int /*<<< orphan*/  vm_pagequeue_unlock (struct vm_pagequeue*) ; 
 int /*<<< orphan*/  vm_swapout_run () ; 
 int /*<<< orphan*/  vm_swapout_run_idle () ; 
 int /*<<< orphan*/  wakeup (scalar_t__*) ; 

__attribute__((used)) static int
vm_pageout_scan_inactive(struct vm_domain *vmd, int shortage,
    int *addl_shortage)
{
	struct scan_state ss;
	struct vm_batchqueue rq;
	struct mtx *mtx;
	vm_page_t m, marker;
	struct vm_pagequeue *pq;
	vm_object_t object;
	int act_delta, addl_page_shortage, deficit, page_shortage;
	int starting_page_shortage;

	/*
	 * The addl_page_shortage is an estimate of the number of temporarily
	 * stuck pages in the inactive queue.  In other words, the
	 * number of pages from the inactive count that should be
	 * discounted in setting the target for the active queue scan.
	 */
	addl_page_shortage = 0;

	/*
	 * vmd_pageout_deficit counts the number of pages requested in
	 * allocations that failed because of a free page shortage.  We assume
	 * that the allocations will be reattempted and thus include the deficit
	 * in our scan target.
	 */
	deficit = atomic_readandclear_int(&vmd->vmd_pageout_deficit);
	starting_page_shortage = page_shortage = shortage + deficit;

	mtx = NULL;
	object = NULL;
	vm_batchqueue_init(&rq);

	/*
	 * Start scanning the inactive queue for pages that we can free.  The
	 * scan will stop when we reach the target or we have scanned the
	 * entire queue.  (Note that m->act_count is not used to make
	 * decisions for the inactive queue, only for the active queue.)
	 */
	marker = &vmd->vmd_markers[PQ_INACTIVE];
	pq = &vmd->vmd_pagequeues[PQ_INACTIVE];
	vm_pagequeue_lock(pq);
	vm_pageout_init_scan(&ss, pq, marker, NULL, pq->pq_cnt);
	while (page_shortage > 0 && (m = vm_pageout_next(&ss, true)) != NULL) {
		KASSERT((m->flags & PG_MARKER) == 0,
		    ("marker page %p was dequeued", m));

		vm_page_change_lock(m, &mtx);

recheck:
		/*
		 * The page may have been disassociated from the queue
		 * or even freed while locks were dropped.  We thus must be
		 * careful whenever modifying page state.  Once the object lock
		 * has been acquired, we have a stable reference to the page.
		 */
		if (vm_page_queue(m) != PQ_INACTIVE) {
			addl_page_shortage++;
			continue;
		}

		/*
		 * The page was re-enqueued after the page queue lock was
		 * dropped, or a requeue was requested.  This page gets a second
		 * chance.
		 */
		if ((m->aflags & (PGA_ENQUEUED | PGA_REQUEUE |
		    PGA_REQUEUE_HEAD)) != 0)
			goto reinsert;

		/*
		 * Wired pages may not be freed.  Complete their removal
		 * from the queue now to avoid needless revisits during
		 * future scans.  This check is racy and must be reverified once
		 * we hold the object lock and have verified that the page
		 * is not busy.
		 */
		if (vm_page_wired(m)) {
			vm_page_dequeue_deferred(m);
			continue;
		}

		if (object != m->object) {
			if (object != NULL)
				VM_OBJECT_WUNLOCK(object);

			/*
			 * A page's object pointer may be set to NULL before
			 * the object lock is acquired.
			 */
			object = (vm_object_t)atomic_load_ptr(&m->object);
			if (object != NULL && !VM_OBJECT_TRYWLOCK(object)) {
				mtx_unlock(mtx);
				/* Depends on type-stability. */
				VM_OBJECT_WLOCK(object);
				mtx_lock(mtx);
				goto recheck;
			}
		}
		if (__predict_false(m->object == NULL))
			/*
			 * The page has been removed from its object.
			 */
			continue;
		KASSERT(m->object == object, ("page %p does not belong to %p",
		    m, object));

		if (vm_page_tryxbusy(m) == 0) {
			/*
			 * Don't mess with busy pages.  Leave them at
			 * the front of the queue.  Most likely, they
			 * are being paged out and will leave the
			 * queue shortly after the scan finishes.  So,
			 * they ought to be discounted from the
			 * inactive count.
			 */
			addl_page_shortage++;
			goto reinsert;
		}

		/*
		 * Re-check for wirings now that we hold the object lock and
		 * have verified that the page is unbusied.  If the page is
		 * mapped, it may still be wired by pmap lookups.  The call to
		 * vm_page_try_remove_all() below atomically checks for such
		 * wirings and removes mappings.  If the page is unmapped, the
		 * wire count is guaranteed not to increase.
		 */
		if (__predict_false(vm_page_wired(m))) {
			vm_page_xunbusy(m);
			vm_page_dequeue_deferred(m);
			continue;
		}

		/*
		 * Invalid pages can be easily freed. They cannot be
		 * mapped, vm_page_free() asserts this.
		 */
		if (vm_page_none_valid(m))
			goto free_page;

		/*
		 * If the page has been referenced and the object is not dead,
		 * reactivate or requeue the page depending on whether the
		 * object is mapped.
		 *
		 * Test PGA_REFERENCED after calling pmap_ts_referenced() so
		 * that a reference from a concurrently destroyed mapping is
		 * observed here and now.
		 */
		if (object->ref_count != 0)
			act_delta = pmap_ts_referenced(m);
		else {
			KASSERT(!pmap_page_is_mapped(m),
			    ("page %p is mapped", m));
			act_delta = 0;
		}
		if ((m->aflags & PGA_REFERENCED) != 0) {
			vm_page_aflag_clear(m, PGA_REFERENCED);
			act_delta++;
		}
		if (act_delta != 0) {
			if (object->ref_count != 0) {
				vm_page_xunbusy(m);
				VM_CNT_INC(v_reactivated);
				vm_page_activate(m);

				/*
				 * Increase the activation count if the page
				 * was referenced while in the inactive queue.
				 * This makes it less likely that the page will
				 * be returned prematurely to the inactive
				 * queue.
 				 */
				m->act_count += act_delta + ACT_ADVANCE;
				continue;
			} else if ((object->flags & OBJ_DEAD) == 0) {
				vm_page_xunbusy(m);
				vm_page_aflag_set(m, PGA_REQUEUE);
				goto reinsert;
			}
		}

		/*
		 * If the page appears to be clean at the machine-independent
		 * layer, then remove all of its mappings from the pmap in
		 * anticipation of freeing it.  If, however, any of the page's
		 * mappings allow write access, then the page may still be
		 * modified until the last of those mappings are removed.
		 */
		if (object->ref_count != 0) {
			vm_page_test_dirty(m);
			if (m->dirty == 0 && !vm_page_try_remove_all(m)) {
				vm_page_xunbusy(m);
				vm_page_dequeue_deferred(m);
				continue;
			}
		}

		/*
		 * Clean pages can be freed, but dirty pages must be sent back
		 * to the laundry, unless they belong to a dead object.
		 * Requeueing dirty pages from dead objects is pointless, as
		 * they are being paged out and freed by the thread that
		 * destroyed the object.
		 */
		if (m->dirty == 0) {
free_page:
			/*
			 * Because we dequeued the page and have already
			 * checked for concurrent dequeue and enqueue
			 * requests, we can safely disassociate the page
			 * from the inactive queue.
			 */
			KASSERT((m->aflags & PGA_QUEUE_STATE_MASK) == 0,
			    ("page %p has queue state", m));
			m->queue = PQ_NONE;
			vm_page_free(m);
			page_shortage--;
			continue;
		}
		vm_page_xunbusy(m);
		if ((object->flags & OBJ_DEAD) == 0)
			vm_page_launder(m);
		continue;
reinsert:
		vm_pageout_reinsert_inactive(&ss, &rq, m);
	}
	if (mtx != NULL)
		mtx_unlock(mtx);
	if (object != NULL)
		VM_OBJECT_WUNLOCK(object);
	vm_pageout_reinsert_inactive(&ss, &rq, NULL);
	vm_pageout_reinsert_inactive(&ss, &ss.bq, NULL);
	vm_pagequeue_lock(pq);
	vm_pageout_end_scan(&ss);
	vm_pagequeue_unlock(pq);

	VM_CNT_ADD(v_dfree, starting_page_shortage - page_shortage);

	/*
	 * Wake up the laundry thread so that it can perform any needed
	 * laundering.  If we didn't meet our target, we're in shortfall and
	 * need to launder more aggressively.  If PQ_LAUNDRY is empty and no
	 * swap devices are configured, the laundry thread has no work to do, so
	 * don't bother waking it up.
	 *
	 * The laundry thread uses the number of inactive queue scans elapsed
	 * since the last laundering to determine whether to launder again, so
	 * keep count.
	 */
	if (starting_page_shortage > 0) {
		pq = &vmd->vmd_pagequeues[PQ_LAUNDRY];
		vm_pagequeue_lock(pq);
		if (vmd->vmd_laundry_request == VM_LAUNDRY_IDLE &&
		    (pq->pq_cnt > 0 || atomic_load_acq_int(&swapdev_enabled))) {
			if (page_shortage > 0) {
				vmd->vmd_laundry_request = VM_LAUNDRY_SHORTFALL;
				VM_CNT_INC(v_pdshortfalls);
			} else if (vmd->vmd_laundry_request !=
			    VM_LAUNDRY_SHORTFALL)
				vmd->vmd_laundry_request =
				    VM_LAUNDRY_BACKGROUND;
			wakeup(&vmd->vmd_laundry_request);
		}
		vmd->vmd_clean_pages_freed +=
		    starting_page_shortage - page_shortage;
		vm_pagequeue_unlock(pq);
	}

	/*
	 * Wakeup the swapout daemon if we didn't free the targeted number of
	 * pages.
	 */
	if (page_shortage > 0)
		vm_swapout_run();

	/*
	 * If the inactive queue scan fails repeatedly to meet its
	 * target, kill the largest process.
	 */
	vm_pageout_mightbe_oom(vmd, page_shortage, starting_page_shortage);

	/*
	 * Reclaim pages by swapping out idle processes, if configured to do so.
	 */
	vm_swapout_run_idle();

	/*
	 * See the description of addl_page_shortage above.
	 */
	*addl_shortage = addl_page_shortage + deficit;

	return (page_shortage <= 0);
}