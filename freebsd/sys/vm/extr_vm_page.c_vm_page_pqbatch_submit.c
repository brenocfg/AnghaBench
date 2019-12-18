#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  size_t uint8_t ;
struct vm_pagequeue {int dummy; } ;
struct vm_batchqueue {int dummy; } ;
struct TYPE_10__ {struct vm_pagequeue* vmd_pagequeues; } ;
struct TYPE_9__ {int oflags; size_t queue; int aflags; int /*<<< orphan*/ * object; } ;

/* Variables and functions */
 struct vm_batchqueue* DPCPU_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PGA_ENQUEUED ; 
 size_t PQ_COUNT ; 
 size_t PQ_NONE ; 
 int VPO_UNMANAGED ; 
 scalar_t__ __predict_true (int) ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 scalar_t__ mtx_owned (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** pqbatch ; 
 scalar_t__ vm_batchqueue_insert (struct vm_batchqueue*,TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_lockptr (TYPE_1__*) ; 
 TYPE_4__* vm_pagequeue_domain (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_pagequeue_lock (struct vm_pagequeue*) ; 
 int /*<<< orphan*/  vm_pagequeue_unlock (struct vm_pagequeue*) ; 
 int vm_phys_domain (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_pqbatch_process (struct vm_pagequeue*,struct vm_batchqueue*,size_t) ; 
 int /*<<< orphan*/  vm_pqbatch_process_page (struct vm_pagequeue*,TYPE_1__*) ; 

void
vm_page_pqbatch_submit(vm_page_t m, uint8_t queue)
{
	struct vm_batchqueue *bq;
	struct vm_pagequeue *pq;
	int domain;

	KASSERT((m->oflags & VPO_UNMANAGED) == 0,
	    ("page %p is unmanaged", m));
	KASSERT(mtx_owned(vm_page_lockptr(m)) || m->object == NULL,
	    ("missing synchronization for page %p", m));
	KASSERT(queue < PQ_COUNT, ("invalid queue %d", queue));

	domain = vm_phys_domain(m);
	pq = &vm_pagequeue_domain(m)->vmd_pagequeues[queue];

	critical_enter();
	bq = DPCPU_PTR(pqbatch[domain][queue]);
	if (vm_batchqueue_insert(bq, m)) {
		critical_exit();
		return;
	}
	critical_exit();
	vm_pagequeue_lock(pq);
	critical_enter();
	bq = DPCPU_PTR(pqbatch[domain][queue]);
	vm_pqbatch_process(pq, bq, queue);

	/*
	 * The page may have been logically dequeued before we acquired the
	 * page queue lock.  In this case, since we either hold the page lock
	 * or the page is being freed, a different thread cannot be concurrently
	 * enqueuing the page.
	 */
	if (__predict_true(m->queue == queue))
		vm_pqbatch_process_page(pq, m);
	else {
		KASSERT(m->queue == PQ_NONE,
		    ("invalid queue transition for page %p", m));
		KASSERT((m->aflags & PGA_ENQUEUED) == 0,
		    ("page %p is enqueued with invalid queue index", m));
	}
	vm_pagequeue_unlock(pq);
	critical_exit();
}