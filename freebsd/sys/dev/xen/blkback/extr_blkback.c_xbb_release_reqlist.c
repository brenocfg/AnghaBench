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
struct xbb_xen_reqlist {int /*<<< orphan*/  num_children; int /*<<< orphan*/  contig_req_list; int /*<<< orphan*/  nr_segments; int /*<<< orphan*/ * kva; } ;
struct xbb_softc {int flags; int /*<<< orphan*/  io_task; int /*<<< orphan*/  io_taskqueue; int /*<<< orphan*/  reqlist_free_stailq; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct xbb_xen_reqlist*,int /*<<< orphan*/ ) ; 
 int XBBF_RESOURCE_SHORTAGE ; 
 int XBBF_SHUTDOWN ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xbb_free_kva (struct xbb_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xbb_release_reqs (struct xbb_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xbb_shutdown (struct xbb_softc*) ; 

__attribute__((used)) static inline void
xbb_release_reqlist(struct xbb_softc *xbb, struct xbb_xen_reqlist *reqlist,
		    int wakeup)
{

	mtx_assert(&xbb->lock, MA_OWNED);

	if (wakeup) {
		wakeup = xbb->flags & XBBF_RESOURCE_SHORTAGE;
		xbb->flags &= ~XBBF_RESOURCE_SHORTAGE;
	}

	if (reqlist->kva != NULL)
		xbb_free_kva(xbb, reqlist->kva, reqlist->nr_segments);

	xbb_release_reqs(xbb, &reqlist->contig_req_list, reqlist->num_children);

	STAILQ_INSERT_TAIL(&xbb->reqlist_free_stailq, reqlist, links);

	if ((xbb->flags & XBBF_SHUTDOWN) != 0) {
		/*
		 * Shutdown is in progress.  See if we can
		 * progress further now that one more request
		 * has completed and been returned to the
		 * free pool.
		 */
		xbb_shutdown(xbb);
	}

	if (wakeup != 0)
		taskqueue_enqueue(xbb->io_taskqueue, &xbb->io_task); 
}