#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct sg_io_v4 {scalar_t__ din_xfer_len; int /*<<< orphan*/  din_xferp; scalar_t__ dout_xfer_len; int /*<<< orphan*/  request_len; int /*<<< orphan*/  request; } ;
struct request {int /*<<< orphan*/  q; } ;
struct bsg_job {TYPE_1__* request; TYPE_1__* bidi_rq; int /*<<< orphan*/ * bidi_bio; int /*<<< orphan*/  request_len; } ;
typedef  int /*<<< orphan*/  fmode_t ;
struct TYPE_8__ {int /*<<< orphan*/ * bio; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  REQ_OP_SCSI_IN ; 
 TYPE_1__* blk_get_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bsg_job* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  blk_put_request (TYPE_1__*) ; 
 int blk_rq_map_user (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* memdup_user (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uptr64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bsg_transport_fill_hdr(struct request *rq, struct sg_io_v4 *hdr,
		fmode_t mode)
{
	struct bsg_job *job = blk_mq_rq_to_pdu(rq);
	int ret;

	job->request_len = hdr->request_len;
	job->request = memdup_user(uptr64(hdr->request), hdr->request_len);
	if (IS_ERR(job->request))
		return PTR_ERR(job->request);

	if (hdr->dout_xfer_len && hdr->din_xfer_len) {
		job->bidi_rq = blk_get_request(rq->q, REQ_OP_SCSI_IN, 0);
		if (IS_ERR(job->bidi_rq)) {
			ret = PTR_ERR(job->bidi_rq);
			goto out;
		}

		ret = blk_rq_map_user(rq->q, job->bidi_rq, NULL,
				uptr64(hdr->din_xferp), hdr->din_xfer_len,
				GFP_KERNEL);
		if (ret)
			goto out_free_bidi_rq;

		job->bidi_bio = job->bidi_rq->bio;
	} else {
		job->bidi_rq = NULL;
		job->bidi_bio = NULL;
	}

	return 0;

out_free_bidi_rq:
	if (job->bidi_rq)
		blk_put_request(job->bidi_rq);
out:
	kfree(job->request);
	return ret;
}