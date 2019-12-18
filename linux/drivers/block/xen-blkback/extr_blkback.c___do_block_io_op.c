#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ req_cons; scalar_t__ rsp_prod_pvt; TYPE_1__* sring; } ;
union blkif_back_rings {TYPE_4__ common; int /*<<< orphan*/  x86_64; int /*<<< orphan*/  x86_32; int /*<<< orphan*/  native; } ;
struct xen_blkif_ring {TYPE_3__* blkif; int /*<<< orphan*/  st_oo_req; union blkif_back_rings blk_rings; } ;
struct pending_req {int dummy; } ;
struct blkif_request {int operation; } ;
typedef  int /*<<< orphan*/  req ;
struct TYPE_7__ {int /*<<< orphan*/  pdevice; } ;
struct TYPE_8__ {int blk_protocol; TYPE_2__ vbd; } ;
struct TYPE_6__ {scalar_t__ req_prod; } ;
typedef  scalar_t__ RING_IDX ;

/* Variables and functions */
#define  BLKIF_OP_DISCARD 136 
#define  BLKIF_OP_FLUSH_DISKCACHE 135 
#define  BLKIF_OP_INDIRECT 134 
#define  BLKIF_OP_READ 133 
#define  BLKIF_OP_WRITE 132 
#define  BLKIF_OP_WRITE_BARRIER 131 
#define  BLKIF_PROTOCOL_NATIVE 130 
#define  BLKIF_PROTOCOL_X86_32 129 
#define  BLKIF_PROTOCOL_X86_64 128 
 int /*<<< orphan*/  BUG () ; 
 int EACCES ; 
 int /*<<< orphan*/  RING_GET_REQUEST (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ RING_REQUEST_CONS_OVERFLOW (TYPE_4__*,scalar_t__) ; 
 scalar_t__ RING_REQUEST_PROD_OVERFLOW (TYPE_4__*,scalar_t__) ; 
 struct pending_req* alloc_req (struct xen_blkif_ring*) ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  blkif_get_x86_32_req (struct blkif_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blkif_get_x86_64_req (struct blkif_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  dispatch_discard_io (struct xen_blkif_ring*,struct blkif_request*) ; 
 int /*<<< orphan*/  dispatch_other_io (struct xen_blkif_ring*,struct blkif_request*,struct pending_req*) ; 
 int /*<<< orphan*/  dispatch_rw_block_io (struct xen_blkif_ring*,struct blkif_request*,struct pending_req*) ; 
 int /*<<< orphan*/  free_req (struct xen_blkif_ring*,struct pending_req*) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  memcpy (struct blkif_request*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_warn (char*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmb () ; 

__attribute__((used)) static int
__do_block_io_op(struct xen_blkif_ring *ring)
{
	union blkif_back_rings *blk_rings = &ring->blk_rings;
	struct blkif_request req;
	struct pending_req *pending_req;
	RING_IDX rc, rp;
	int more_to_do = 0;

	rc = blk_rings->common.req_cons;
	rp = blk_rings->common.sring->req_prod;
	rmb(); /* Ensure we see queued requests up to 'rp'. */

	if (RING_REQUEST_PROD_OVERFLOW(&blk_rings->common, rp)) {
		rc = blk_rings->common.rsp_prod_pvt;
		pr_warn("Frontend provided bogus ring requests (%d - %d = %d). Halting ring processing on dev=%04x\n",
			rp, rc, rp - rc, ring->blkif->vbd.pdevice);
		return -EACCES;
	}
	while (rc != rp) {

		if (RING_REQUEST_CONS_OVERFLOW(&blk_rings->common, rc))
			break;

		if (kthread_should_stop()) {
			more_to_do = 1;
			break;
		}

		pending_req = alloc_req(ring);
		if (NULL == pending_req) {
			ring->st_oo_req++;
			more_to_do = 1;
			break;
		}

		switch (ring->blkif->blk_protocol) {
		case BLKIF_PROTOCOL_NATIVE:
			memcpy(&req, RING_GET_REQUEST(&blk_rings->native, rc), sizeof(req));
			break;
		case BLKIF_PROTOCOL_X86_32:
			blkif_get_x86_32_req(&req, RING_GET_REQUEST(&blk_rings->x86_32, rc));
			break;
		case BLKIF_PROTOCOL_X86_64:
			blkif_get_x86_64_req(&req, RING_GET_REQUEST(&blk_rings->x86_64, rc));
			break;
		default:
			BUG();
		}
		blk_rings->common.req_cons = ++rc; /* before make_response() */

		/* Apply all sanity checks to /private copy/ of request. */
		barrier();

		switch (req.operation) {
		case BLKIF_OP_READ:
		case BLKIF_OP_WRITE:
		case BLKIF_OP_WRITE_BARRIER:
		case BLKIF_OP_FLUSH_DISKCACHE:
		case BLKIF_OP_INDIRECT:
			if (dispatch_rw_block_io(ring, &req, pending_req))
				goto done;
			break;
		case BLKIF_OP_DISCARD:
			free_req(ring, pending_req);
			if (dispatch_discard_io(ring, &req))
				goto done;
			break;
		default:
			if (dispatch_other_io(ring, &req, pending_req))
				goto done;
			break;
		}

		/* Yield point for this unbounded loop. */
		cond_resched();
	}
done:
	return more_to_do;
}