#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct xbb_xen_reqlist {scalar_t__ next_contig_sector; int operation; scalar_t__ nr_segments; } ;
struct TYPE_12__ {scalar_t__ req_cons; TYPE_1__* sring; } ;
struct TYPE_11__ {TYPE_8__ common; int /*<<< orphan*/  x86_64; int /*<<< orphan*/  x86_32; int /*<<< orphan*/  native; } ;
struct xbb_softc {int abi; scalar_t__ no_coalesce_reqs; scalar_t__ max_reqlist_segments; int /*<<< orphan*/  total_dispatch; int /*<<< orphan*/  normal_dispatch; int /*<<< orphan*/  forced_dispatch; int /*<<< orphan*/  reqlist_pending_stailq; int /*<<< orphan*/  reqs_received; TYPE_3__ rings; } ;
struct blkif_x86_64_request {int dummy; } ;
struct blkif_x86_32_request {int dummy; } ;
struct TYPE_10__ {scalar_t__ sector_number; int operation; scalar_t__ nr_segments; } ;
typedef  TYPE_2__ blkif_request_t ;
typedef  TYPE_3__ blkif_back_rings_t ;
struct TYPE_9__ {scalar_t__ req_prod; } ;
typedef  scalar_t__ RING_IDX ;

/* Variables and functions */
#define  BLKIF_PROTOCOL_NATIVE 130 
#define  BLKIF_PROTOCOL_X86_32 129 
#define  BLKIF_PROTOCOL_X86_64 128 
 void* RING_GET_REQUEST (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ RING_REQUEST_CONS_OVERFLOW (TYPE_8__*,scalar_t__) ; 
 struct xbb_xen_reqlist* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct xbb_xen_reqlist*,int /*<<< orphan*/ ) ; 
 struct xbb_xen_reqlist* STAILQ_LAST (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blkif_get_x86_32_req (TYPE_2__*,struct blkif_x86_32_request*) ; 
 int /*<<< orphan*/  blkif_get_x86_64_req (TYPE_2__*,struct blkif_x86_64_request*) ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  rmb () ; 
 int xbb_count_sects (TYPE_2__*) ; 
 int xbb_dispatch_io (struct xbb_softc*,struct xbb_xen_reqlist*) ; 
 int xbb_get_resources (struct xbb_softc*,struct xbb_xen_reqlist**,TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  xbb_xen_reqlist ; 

__attribute__((used)) static void
xbb_run_queue(void *context, int pending)
{
	struct xbb_softc       *xbb;
	blkif_back_rings_t     *rings;
	RING_IDX		rp;
	uint64_t		cur_sector;
	int			cur_operation;
	struct xbb_xen_reqlist *reqlist;


	xbb   = (struct xbb_softc *)context;
	rings = &xbb->rings;

	/*
	 * Work gather and dispatch loop.  Note that we have a bias here
	 * towards gathering I/O sent by blockfront.  We first gather up
	 * everything in the ring, as long as we have resources.  Then we
	 * dispatch one request, and then attempt to gather up any
	 * additional requests that have come in while we were dispatching
	 * the request.
	 *
	 * This allows us to get a clearer picture (via devstat) of how
	 * many requests blockfront is queueing to us at any given time.
	 */
	for (;;) {
		int retval;

		/*
		 * Initialize reqlist to the last element in the pending
		 * queue, if there is one.  This allows us to add more
		 * requests to that request list, if we have room.
		 */
		reqlist = STAILQ_LAST(&xbb->reqlist_pending_stailq,
				      xbb_xen_reqlist, links);
		if (reqlist != NULL) {
			cur_sector = reqlist->next_contig_sector;
			cur_operation = reqlist->operation;
		} else {
			cur_operation = 0;
			cur_sector    = 0;
		}

		/*
		 * Cache req_prod to avoid accessing a cache line shared
		 * with the frontend.
		 */
		rp = rings->common.sring->req_prod;

		/* Ensure we see queued requests up to 'rp'. */
		rmb();

		/**
		 * Run so long as there is work to consume and the generation
		 * of a response will not overflow the ring.
		 *
		 * @note There's a 1 to 1 relationship between requests and
		 *       responses, so an overflow should never occur.  This
		 *       test is to protect our domain from digesting bogus
		 *       data.  Shouldn't we log this?
		 */
		while (rings->common.req_cons != rp
		    && RING_REQUEST_CONS_OVERFLOW(&rings->common,
						  rings->common.req_cons) == 0){
			blkif_request_t	        ring_req_storage;
			blkif_request_t	       *ring_req;
			int			cur_size;

			switch (xbb->abi) {
			case BLKIF_PROTOCOL_NATIVE:
				ring_req = RING_GET_REQUEST(&xbb->rings.native,
				    rings->common.req_cons);
				break;
			case BLKIF_PROTOCOL_X86_32:
			{
				struct blkif_x86_32_request *ring_req32;

				ring_req32 = RING_GET_REQUEST(
				    &xbb->rings.x86_32, rings->common.req_cons);
				blkif_get_x86_32_req(&ring_req_storage,
						     ring_req32);
				ring_req = &ring_req_storage;
				break;
			}
			case BLKIF_PROTOCOL_X86_64:
			{
				struct blkif_x86_64_request *ring_req64;

				ring_req64 =RING_GET_REQUEST(&xbb->rings.x86_64,
				    rings->common.req_cons);
				blkif_get_x86_64_req(&ring_req_storage,
						     ring_req64);
				ring_req = &ring_req_storage;
				break;
			}
			default:
				panic("Unexpected blkif protocol ABI.");
				/* NOTREACHED */
			} 

			/*
			 * Check for situations that would require closing
			 * off this I/O for further coalescing:
			 *  - Coalescing is turned off.
			 *  - Current I/O is out of sequence with the previous
			 *    I/O.
			 *  - Coalesced I/O would be too large.
			 */
			if ((reqlist != NULL)
			 && ((xbb->no_coalesce_reqs != 0)
			  || ((xbb->no_coalesce_reqs == 0)
			   && ((ring_req->sector_number != cur_sector)
			    || (ring_req->operation != cur_operation)
			    || ((ring_req->nr_segments + reqlist->nr_segments) >
			         xbb->max_reqlist_segments))))) {
				reqlist = NULL;
			}

			/*
			 * Grab and check for all resources in one shot.
			 * If we can't get all of the resources we need,
			 * the shortage is noted and the thread will get
			 * woken up when more resources are available.
			 */
			retval = xbb_get_resources(xbb, &reqlist, ring_req,
						   xbb->rings.common.req_cons);

			if (retval != 0) {
				/*
				 * Resource shortage has been recorded.
				 * We'll be scheduled to run once a request
				 * object frees up due to a completion.
				 */
				break;
			}

			/*
			 * Signify that	we can overwrite this request with
			 * a response by incrementing our consumer index.
			 * The response won't be generated until after
			 * we've already consumed all necessary data out
			 * of the version of the request in the ring buffer
			 * (for native mode).  We must update the consumer
			 * index  before issuing back-end I/O so there is
			 * no possibility that it will complete and a
			 * response be generated before we make room in 
			 * the queue for that response.
			 */
			xbb->rings.common.req_cons++;
			xbb->reqs_received++;

			cur_size = xbb_count_sects(ring_req);
			cur_sector = ring_req->sector_number + cur_size;
			reqlist->next_contig_sector = cur_sector;
			cur_operation = ring_req->operation;
		}

		/* Check for I/O to dispatch */
		reqlist = STAILQ_FIRST(&xbb->reqlist_pending_stailq);
		if (reqlist == NULL) {
			/*
			 * We're out of work to do, put the task queue to
			 * sleep.
			 */
			break;
		}

		/*
		 * Grab the first request off the queue and attempt
		 * to dispatch it.
		 */
		STAILQ_REMOVE_HEAD(&xbb->reqlist_pending_stailq, links);

		retval = xbb_dispatch_io(xbb, reqlist);
		if (retval != 0) {
			/*
			 * xbb_dispatch_io() returns non-zero only when
			 * there is a resource shortage.  If that's the
			 * case, re-queue this request on the head of the
			 * queue, and go to sleep until we have more
			 * resources.
			 */
			STAILQ_INSERT_HEAD(&xbb->reqlist_pending_stailq,
					   reqlist, links);
			break;
		} else {
			/*
			 * If we still have anything on the queue after
			 * removing the head entry, that is because we
			 * met one of the criteria to create a new
			 * request list (outlined above), and we'll call
			 * that a forced dispatch for statistical purposes.
			 *
			 * Otherwise, if there is only one element on the
			 * queue, we coalesced everything available on
			 * the ring and we'll call that a normal dispatch.
			 */
			reqlist = STAILQ_FIRST(&xbb->reqlist_pending_stailq);

			if (reqlist != NULL)
				xbb->forced_dispatch++;
			else
				xbb->normal_dispatch++;

			xbb->total_dispatch++;
		}
	}
}