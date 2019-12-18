#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  int uint8_t ;
struct vm_pagequeue {int /*<<< orphan*/  pq_pl; } ;
struct vm_domain {int /*<<< orphan*/  vmd_inacthead; } ;
struct TYPE_14__ {int /*<<< orphan*/  q; } ;
struct TYPE_13__ {scalar_t__ queue; int /*<<< orphan*/  aflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRITICAL_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PGA_DEQUEUE ; 
 int PGA_ENQUEUED ; 
 int PGA_QUEUE_STATE_MASK ; 
 int PGA_REQUEUE ; 
 int PGA_REQUEUE_HEAD ; 
 scalar_t__ PQ_INACTIVE ; 
 int /*<<< orphan*/  TAILQ_INSERT_BEFORE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ __predict_true (int) ; 
 int atomic_load_8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  curthread ; 
 TYPE_9__ plinks ; 
 int /*<<< orphan*/  queue_nops ; 
 int /*<<< orphan*/  queue_ops ; 
 int /*<<< orphan*/  vm_page_aflag_clear (TYPE_1__*,int) ; 
 int /*<<< orphan*/  vm_page_aflag_set (TYPE_1__*,int) ; 
 int /*<<< orphan*/  vm_page_dequeue_complete (TYPE_1__*) ; 
 struct vm_pagequeue* vm_page_pagequeue (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_pagequeue_assert_locked (struct vm_pagequeue*) ; 
 int /*<<< orphan*/  vm_pagequeue_cnt_inc (struct vm_pagequeue*) ; 
 struct vm_domain* vm_pagequeue_domain (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_pagequeue_remove (struct vm_pagequeue*,TYPE_1__*) ; 

__attribute__((used)) static inline void
vm_pqbatch_process_page(struct vm_pagequeue *pq, vm_page_t m)
{
	struct vm_domain *vmd;
	uint8_t qflags;

	CRITICAL_ASSERT(curthread);
	vm_pagequeue_assert_locked(pq);

	/*
	 * The page daemon is allowed to set m->queue = PQ_NONE without
	 * the page queue lock held.  In this case it is about to free the page,
	 * which must not have any queue state.
	 */
	qflags = atomic_load_8(&m->aflags);
	KASSERT(pq == vm_page_pagequeue(m) ||
	    (qflags & PGA_QUEUE_STATE_MASK) == 0,
	    ("page %p doesn't belong to queue %p but has aflags %#x",
	    m, pq, qflags));

	if ((qflags & PGA_DEQUEUE) != 0) {
		if (__predict_true((qflags & PGA_ENQUEUED) != 0))
			vm_pagequeue_remove(pq, m);
		vm_page_dequeue_complete(m);
		counter_u64_add(queue_ops, 1);
	} else if ((qflags & (PGA_REQUEUE | PGA_REQUEUE_HEAD)) != 0) {
		if ((qflags & PGA_ENQUEUED) != 0)
			TAILQ_REMOVE(&pq->pq_pl, m, plinks.q);
		else {
			vm_pagequeue_cnt_inc(pq);
			vm_page_aflag_set(m, PGA_ENQUEUED);
		}

		/*
		 * Give PGA_REQUEUE_HEAD precedence over PGA_REQUEUE.
		 * In particular, if both flags are set in close succession,
		 * only PGA_REQUEUE_HEAD will be applied, even if it was set
		 * first.
		 */
		if ((qflags & PGA_REQUEUE_HEAD) != 0) {
			KASSERT(m->queue == PQ_INACTIVE,
			    ("head enqueue not supported for page %p", m));
			vmd = vm_pagequeue_domain(m);
			TAILQ_INSERT_BEFORE(&vmd->vmd_inacthead, m, plinks.q);
		} else
			TAILQ_INSERT_TAIL(&pq->pq_pl, m, plinks.q);

		vm_page_aflag_clear(m, qflags & (PGA_REQUEUE |
		    PGA_REQUEUE_HEAD));
		counter_u64_add(queue_ops, 1);
	} else {
		counter_u64_add(queue_nops, 1);
	}
}