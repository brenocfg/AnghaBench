#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  size_t uint8_t ;
struct vm_pagequeue {int /*<<< orphan*/  pq_pl; } ;
struct TYPE_19__ {struct vm_pagequeue* vmd_pagequeues; } ;
struct TYPE_18__ {size_t queue; int aflags; } ;
struct TYPE_17__ {int /*<<< orphan*/  q; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  PGA_DEQUEUE ; 
 int PGA_ENQUEUED ; 
 int /*<<< orphan*/  PGA_REQUEUE ; 
 size_t PQ_COUNT ; 
 int /*<<< orphan*/  TAILQ_INSERT_BEFORE (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* TAILQ_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ __predict_false (int) ; 
 scalar_t__ __predict_true (int) ; 
 TYPE_10__ plinks ; 
 int /*<<< orphan*/  vm_page_aflag_clear (TYPE_1__*,int) ; 
 int /*<<< orphan*/  vm_page_aflag_set (TYPE_1__*,int) ; 
 int /*<<< orphan*/  vm_page_assert_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_pqbatch_submit (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  vm_page_pqstate_cmpset (TYPE_1__*,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_pagequeue_cnt_dec (struct vm_pagequeue*) ; 
 TYPE_2__* vm_pagequeue_domain (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_pagequeue_lock (struct vm_pagequeue*) ; 
 int /*<<< orphan*/  vm_pagequeue_unlock (struct vm_pagequeue*) ; 

void
vm_page_swapqueue(vm_page_t m, uint8_t oldq, uint8_t newq)
{
	struct vm_pagequeue *pq;
	vm_page_t next;
	bool queued;

	KASSERT(oldq < PQ_COUNT && newq < PQ_COUNT && oldq != newq,
	    ("vm_page_swapqueue: invalid queues (%d, %d)", oldq, newq));
	vm_page_assert_locked(m);

	pq = &vm_pagequeue_domain(m)->vmd_pagequeues[oldq];
	vm_pagequeue_lock(pq);

	/*
	 * The physical queue state might change at any point before the page
	 * queue lock is acquired, so we must verify that we hold the correct
	 * lock before proceeding.
	 */
	if (__predict_false(m->queue != oldq)) {
		vm_pagequeue_unlock(pq);
		return;
	}

	/*
	 * Once the queue index of the page changes, there is nothing
	 * synchronizing with further updates to the physical queue state.
	 * Therefore we must remove the page from the queue now in anticipation
	 * of a successful commit, and be prepared to roll back.
	 */
	if (__predict_true((m->aflags & PGA_ENQUEUED) != 0)) {
		next = TAILQ_NEXT(m, plinks.q);
		TAILQ_REMOVE(&pq->pq_pl, m, plinks.q);
		vm_page_aflag_clear(m, PGA_ENQUEUED);
		queued = true;
	} else {
		queued = false;
	}

	/*
	 * Atomically update the queue field and set PGA_REQUEUE while
	 * ensuring that PGA_DEQUEUE has not been set.
	 */
	if (__predict_false(!vm_page_pqstate_cmpset(m, oldq, newq, PGA_DEQUEUE,
	    PGA_REQUEUE))) {
		if (queued) {
			vm_page_aflag_set(m, PGA_ENQUEUED);
			if (next != NULL)
				TAILQ_INSERT_BEFORE(next, m, plinks.q);
			else
				TAILQ_INSERT_TAIL(&pq->pq_pl, m, plinks.q);
		}
		vm_pagequeue_unlock(pq);
		return;
	}
	vm_pagequeue_cnt_dec(pq);
	vm_pagequeue_unlock(pq);
	vm_page_pqbatch_submit(m, newq);
}