#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct xbb_xen_req {int /*<<< orphan*/  operation; int /*<<< orphan*/  id; } ;
struct TYPE_6__ {int /*<<< orphan*/  rsp_prod_pvt; } ;
struct TYPE_9__ {int /*<<< orphan*/  rsp_prod_pvt; } ;
struct TYPE_7__ {TYPE_1__ common; TYPE_5__ x86_64; TYPE_5__ x86_32; TYPE_5__ native; } ;
struct xbb_softc {int abi; int /*<<< orphan*/  reqs_queued_for_completion; TYPE_2__ rings; int /*<<< orphan*/  reqs_completed_with_error; int /*<<< orphan*/  lock; } ;
struct TYPE_8__ {int status; int /*<<< orphan*/  operation; int /*<<< orphan*/  id; } ;
typedef  TYPE_3__ blkif_response_t ;

/* Variables and functions */
#define  BLKIF_PROTOCOL_NATIVE 130 
#define  BLKIF_PROTOCOL_X86_32 129 
#define  BLKIF_PROTOCOL_X86_64 128 
 int BLKIF_RSP_OKAY ; 
 int /*<<< orphan*/  MA_OWNED ; 
 TYPE_3__* RING_GET_RESPONSE (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void
xbb_queue_response(struct xbb_softc *xbb, struct xbb_xen_req *req, int status)
{
	blkif_response_t *resp;

	/*
	 * The mutex is required here, and should be held across this call
	 * until after the subsequent call to xbb_push_responses().  This
	 * is to guarantee that another context won't queue responses and
	 * push them while we're active.
	 *
	 * That could lead to the other end being notified of responses
	 * before the resources have been freed on this end.  The other end
	 * would then be able to queue additional I/O, and we may run out
 	 * of resources because we haven't freed them all yet.
	 */
	mtx_assert(&xbb->lock, MA_OWNED);

	/*
	 * Place on the response ring for the relevant domain.
	 * For now, only the spacing between entries is different
	 * in the different ABIs, not the response entry layout.
	 */
	switch (xbb->abi) {
	case BLKIF_PROTOCOL_NATIVE:
		resp = RING_GET_RESPONSE(&xbb->rings.native,
					 xbb->rings.native.rsp_prod_pvt);
		break;
	case BLKIF_PROTOCOL_X86_32:
		resp = (blkif_response_t *)
		    RING_GET_RESPONSE(&xbb->rings.x86_32,
				      xbb->rings.x86_32.rsp_prod_pvt);
		break;
	case BLKIF_PROTOCOL_X86_64:
		resp = (blkif_response_t *)
		    RING_GET_RESPONSE(&xbb->rings.x86_64,
				      xbb->rings.x86_64.rsp_prod_pvt);
		break;
	default:
		panic("Unexpected blkif protocol ABI.");
	}

	resp->id        = req->id;
	resp->operation = req->operation;
	resp->status    = status;

	if (status != BLKIF_RSP_OKAY)
		xbb->reqs_completed_with_error++;

	xbb->rings.common.rsp_prod_pvt++;

	xbb->reqs_queued_for_completion++;

}