#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ nr_segments; int /*<<< orphan*/  operation; int /*<<< orphan*/  id; int /*<<< orphan*/  sector_number; } ;
struct xbb_xen_reqlist {int /*<<< orphan*/  nr_segments; int /*<<< orphan*/  num_children; int /*<<< orphan*/  contig_req_list; int /*<<< orphan*/  ds_t0; TYPE_1__* ring_req; TYPE_1__ ring_req_storage; int /*<<< orphan*/  operation; int /*<<< orphan*/  id; int /*<<< orphan*/  req_ring_idx; struct xbb_xen_reqlist* reqlist; int /*<<< orphan*/  starting_sector_number; } ;
struct xbb_xen_req {int /*<<< orphan*/  nr_segments; int /*<<< orphan*/  num_children; int /*<<< orphan*/  contig_req_list; int /*<<< orphan*/  ds_t0; TYPE_1__* ring_req; TYPE_1__ ring_req_storage; int /*<<< orphan*/  operation; int /*<<< orphan*/  id; int /*<<< orphan*/  req_ring_idx; struct xbb_xen_req* reqlist; int /*<<< orphan*/  starting_sector_number; } ;
struct xbb_softc {int flags; scalar_t__ abi; int /*<<< orphan*/  lock; int /*<<< orphan*/  request_shortages; int /*<<< orphan*/  xbb_stats_in; int /*<<< orphan*/  reqlist_pending_stailq; } ;
typedef  TYPE_1__ blkif_request_t ;
typedef  int /*<<< orphan*/  RING_IDX ;

/* Variables and functions */
 scalar_t__ BLKIF_PROTOCOL_NATIVE ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct xbb_xen_reqlist*,int /*<<< orphan*/ ) ; 
 int XBBF_RESOURCE_SHORTAGE ; 
 int XBBF_SHUTDOWN ; 
 int /*<<< orphan*/  bcopy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  binuptime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devstat_start_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 struct xbb_xen_reqlist* xbb_get_req (struct xbb_softc*) ; 
 struct xbb_xen_reqlist* xbb_get_reqlist (struct xbb_softc*) ; 
 int /*<<< orphan*/  xbb_release_req (struct xbb_softc*,struct xbb_xen_reqlist*) ; 
 int /*<<< orphan*/  xbb_release_reqlist (struct xbb_softc*,struct xbb_xen_reqlist*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xbb_get_resources(struct xbb_softc *xbb, struct xbb_xen_reqlist **reqlist,
		  blkif_request_t *ring_req, RING_IDX ring_idx)
{
	struct xbb_xen_reqlist *nreqlist;
	struct xbb_xen_req     *nreq;

	nreqlist = NULL;
	nreq     = NULL;

	mtx_lock(&xbb->lock);

	/*
	 * We don't allow new resources to be allocated if we're in the
	 * process of shutting down.
	 */
	if ((xbb->flags & XBBF_SHUTDOWN) != 0) {
		mtx_unlock(&xbb->lock);
		return (1);
	}

	/*
	 * Allocate a reqlist if the caller doesn't have one already.
	 */
	if (*reqlist == NULL) {
		nreqlist = xbb_get_reqlist(xbb);
		if (nreqlist == NULL)
			goto bailout_error;
	}

	/* We always allocate a request. */
	nreq = xbb_get_req(xbb);
	if (nreq == NULL)
		goto bailout_error;

	mtx_unlock(&xbb->lock);

	if (*reqlist == NULL) {
		*reqlist = nreqlist;
		nreqlist->operation = ring_req->operation;
		nreqlist->starting_sector_number = ring_req->sector_number;
		STAILQ_INSERT_TAIL(&xbb->reqlist_pending_stailq, nreqlist,
				   links);
	}

	nreq->reqlist = *reqlist;
	nreq->req_ring_idx = ring_idx;
	nreq->id = ring_req->id;
	nreq->operation = ring_req->operation;

	if (xbb->abi != BLKIF_PROTOCOL_NATIVE) {
		bcopy(ring_req, &nreq->ring_req_storage, sizeof(*ring_req));
		nreq->ring_req = &nreq->ring_req_storage;
	} else {
		nreq->ring_req = ring_req;
	}

	binuptime(&nreq->ds_t0);
	devstat_start_transaction(xbb->xbb_stats_in, &nreq->ds_t0);
	STAILQ_INSERT_TAIL(&(*reqlist)->contig_req_list, nreq, links);
	(*reqlist)->num_children++;
	(*reqlist)->nr_segments += ring_req->nr_segments;

	return (0);

bailout_error:

	/*
	 * We're out of resources, so set the shortage flag.  The next time
	 * a request is released, we'll try waking up the work thread to
	 * see if we can allocate more resources.
	 */
	xbb->flags |= XBBF_RESOURCE_SHORTAGE;
	xbb->request_shortages++;

	if (nreq != NULL)
		xbb_release_req(xbb, nreq);

	if (nreqlist != NULL)
		xbb_release_reqlist(xbb, nreqlist, /*wakeup*/ 0);

	mtx_unlock(&xbb->lock);

	return (1);
}