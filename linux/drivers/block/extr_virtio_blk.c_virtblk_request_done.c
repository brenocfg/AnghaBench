#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct virtblk_req {int dummy; } ;
struct TYPE_2__ {scalar_t__ bv_offset; int /*<<< orphan*/  bv_page; } ;
struct request {int rq_flags; TYPE_1__ special_vec; } ;

/* Variables and functions */
#define  REQ_OP_SCSI_IN 129 
#define  REQ_OP_SCSI_OUT 128 
 int RQF_SPECIAL_PAYLOAD ; 
 int /*<<< orphan*/  blk_mq_end_request (struct request*,int /*<<< orphan*/ ) ; 
 struct virtblk_req* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 scalar_t__ page_address (int /*<<< orphan*/ ) ; 
 int req_op (struct request*) ; 
 int /*<<< orphan*/  virtblk_result (struct virtblk_req*) ; 
 int /*<<< orphan*/  virtblk_scsi_request_done (struct request*) ; 

__attribute__((used)) static inline void virtblk_request_done(struct request *req)
{
	struct virtblk_req *vbr = blk_mq_rq_to_pdu(req);

	if (req->rq_flags & RQF_SPECIAL_PAYLOAD) {
		kfree(page_address(req->special_vec.bv_page) +
		      req->special_vec.bv_offset);
	}

	switch (req_op(req)) {
	case REQ_OP_SCSI_IN:
	case REQ_OP_SCSI_OUT:
		virtblk_scsi_request_done(req);
		break;
	}

	blk_mq_end_request(req, virtblk_result(vbr));
}