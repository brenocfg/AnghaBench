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
struct vm_pagequeue {int /*<<< orphan*/  pq_cnt; } ;
struct vm_domain {struct vm_pagequeue* vmd_pagequeues; TYPE_1__* vmd_markers; } ;
struct scan_state {int scanned; } ;
struct mtx {int dummy; } ;
struct TYPE_27__ {scalar_t__ ref_count; int flags; scalar_t__ type; } ;
struct TYPE_26__ {int flags; int aflags; scalar_t__ dirty; int /*<<< orphan*/  act_count; TYPE_2__* object; } ;

/* Variables and functions */
 scalar_t__ ACT_ADVANCE ; 
 int EDEADLK ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ OBJT_DEFAULT ; 
 scalar_t__ OBJT_SWAP ; 
 int OBJ_DEAD ; 
 int PGA_REFERENCED ; 
 int PGA_REQUEUE ; 
 int PG_MARKER ; 
 int PQ_LAUNDRY ; 
 int PQ_UNSWAPPABLE ; 
 int /*<<< orphan*/  VM_CNT_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_TRYWLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (TYPE_2__*) ; 
 scalar_t__ __predict_false (int) ; 
 scalar_t__ atomic_load_acq_int (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_load_ptr (TYPE_2__**) ; 
 scalar_t__ disable_swap_pageouts ; 
 int /*<<< orphan*/  mtx_lock (struct mtx*) ; 
 int /*<<< orphan*/  mtx_unlock (struct mtx*) ; 
 int /*<<< orphan*/  pageout_lock_miss ; 
 int /*<<< orphan*/  pmap_page_is_mapped (TYPE_1__*) ; 
 int pmap_ts_referenced (TYPE_1__*) ; 
 int /*<<< orphan*/  speedup_syncer () ; 
 int /*<<< orphan*/  swapdev_enabled ; 
 int /*<<< orphan*/  v_dfree ; 
 int /*<<< orphan*/  v_reactivated ; 
 int /*<<< orphan*/  vm_page_activate (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_aflag_clear (TYPE_1__*,int) ; 
 int /*<<< orphan*/  vm_page_change_lock (TYPE_1__*,struct mtx**) ; 
 int /*<<< orphan*/  vm_page_dequeue_deferred (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_free (TYPE_1__*) ; 
 scalar_t__ vm_page_none_valid (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_pqbatch_submit (TYPE_1__*,int) ; 
 int vm_page_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_requeue (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_test_dirty (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_try_remove_all (TYPE_1__*) ; 
 scalar_t__ vm_page_tryxbusy (TYPE_1__*) ; 
 int vm_page_wired (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_xunbusy (TYPE_1__*) ; 
 int vm_pageout_clean (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  vm_pageout_end_scan (struct scan_state*) ; 
 int /*<<< orphan*/  vm_pageout_init_scan (struct scan_state*,struct vm_pagequeue*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* vm_pageout_next (struct scan_state*,int) ; 
 int /*<<< orphan*/  vm_pagequeue_lock (struct vm_pagequeue*) ; 
 int /*<<< orphan*/  vm_pagequeue_unlock (struct vm_pagequeue*) ; 

__attribute__((used)) static int
vm_pageout_launder(struct vm_domain *vmd, int launder, bool in_shortfall)
{
	struct scan_state ss;
	struct vm_pagequeue *pq;
	struct mtx *mtx;
	vm_object_t object;
	vm_page_t m, marker;
	int act_delta, error, numpagedout, queue, starting_target;
	int vnodes_skipped;
	bool pageout_ok;

	mtx = NULL;
	object = NULL;
	starting_target = launder;
	vnodes_skipped = 0;

	/*
	 * Scan the laundry queues for pages eligible to be laundered.  We stop
	 * once the target number of dirty pages have been laundered, or once
	 * we've reached the end of the queue.  A single iteration of this loop
	 * may cause more than one page to be laundered because of clustering.
	 *
	 * As an optimization, we avoid laundering from PQ_UNSWAPPABLE when no
	 * swap devices are configured.
	 */
	if (atomic_load_acq_int(&swapdev_enabled))
		queue = PQ_UNSWAPPABLE;
	else
		queue = PQ_LAUNDRY;

scan:
	marker = &vmd->vmd_markers[queue];
	pq = &vmd->vmd_pagequeues[queue];
	vm_pagequeue_lock(pq);
	vm_pageout_init_scan(&ss, pq, marker, NULL, pq->pq_cnt);
	while (launder > 0 && (m = vm_pageout_next(&ss, false)) != NULL) {
		if (__predict_false((m->flags & PG_MARKER) != 0))
			continue;

		vm_page_change_lock(m, &mtx);

recheck:
		/*
		 * The page may have been disassociated from the queue
		 * or even freed while locks were dropped.  We thus must be
		 * careful whenever modifying page state.  Once the object lock
		 * has been acquired, we have a stable reference to the page.
		 */
		if (vm_page_queue(m) != queue)
			continue;

		/*
		 * A requeue was requested, so this page gets a second
		 * chance.
		 */
		if ((m->aflags & PGA_REQUEUE) != 0) {
			vm_page_pqbatch_submit(m, queue);
			continue;
		}

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

		if (vm_page_tryxbusy(m) == 0)
			continue;

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
		 * Invalid pages can be easily freed.  They cannot be
		 * mapped; vm_page_free() asserts this.
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
				 * was referenced while in the laundry queue.
				 * This makes it less likely that the page will
				 * be returned prematurely to the inactive
				 * queue.
 				 */
				m->act_count += act_delta + ACT_ADVANCE;

				/*
				 * If this was a background laundering, count
				 * activated pages towards our target.  The
				 * purpose of background laundering is to ensure
				 * that pages are eventually cycled through the
				 * laundry queue, and an activation is a valid
				 * way out.
				 */
				if (!in_shortfall)
					launder--;
				continue;
			} else if ((object->flags & OBJ_DEAD) == 0) {
				vm_page_xunbusy(m);
				vm_page_requeue(m);
				continue;
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
		 * Clean pages are freed, and dirty pages are paged out unless
		 * they belong to a dead object.  Requeueing dirty pages from
		 * dead objects is pointless, as they are being paged out and
		 * freed by the thread that destroyed the object.
		 */
		if (m->dirty == 0) {
free_page:
			vm_page_free(m);
			VM_CNT_INC(v_dfree);
		} else if ((object->flags & OBJ_DEAD) == 0) {
			if (object->type != OBJT_SWAP &&
			    object->type != OBJT_DEFAULT)
				pageout_ok = true;
			else if (disable_swap_pageouts)
				pageout_ok = false;
			else
				pageout_ok = true;
			if (!pageout_ok) {
				vm_page_xunbusy(m);
				vm_page_requeue(m);
				continue;
			}

			/*
			 * Form a cluster with adjacent, dirty pages from the
			 * same object, and page out that entire cluster.
			 *
			 * The adjacent, dirty pages must also be in the
			 * laundry.  However, their mappings are not checked
			 * for new references.  Consequently, a recently
			 * referenced page may be paged out.  However, that
			 * page will not be prematurely reclaimed.  After page
			 * out, the page will be placed in the inactive queue,
			 * where any new references will be detected and the
			 * page reactivated.
			 */
			error = vm_pageout_clean(m, &numpagedout);
			if (error == 0) {
				launder -= numpagedout;
				ss.scanned += numpagedout;
			} else if (error == EDEADLK) {
				pageout_lock_miss++;
				vnodes_skipped++;
			}
			mtx = NULL;
			object = NULL;
		} else
			vm_page_xunbusy(m);
	}
	if (mtx != NULL) {
		mtx_unlock(mtx);
		mtx = NULL;
	}
	if (object != NULL) {
		VM_OBJECT_WUNLOCK(object);
		object = NULL;
	}
	vm_pagequeue_lock(pq);
	vm_pageout_end_scan(&ss);
	vm_pagequeue_unlock(pq);

	if (launder > 0 && queue == PQ_UNSWAPPABLE) {
		queue = PQ_LAUNDRY;
		goto scan;
	}

	/*
	 * Wakeup the sync daemon if we skipped a vnode in a writeable object
	 * and we didn't launder enough pages.
	 */
	if (vnodes_skipped > 0 && launder > 0)
		(void)speedup_syncer();

	return (starting_target - launder);
}