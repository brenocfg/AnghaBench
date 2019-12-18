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
struct request {scalar_t__ bio; int /*<<< orphan*/  timeout; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sg_list; } ;
struct bsg_job {int /*<<< orphan*/  result; TYPE_1__ request_payload; int /*<<< orphan*/  kref; struct device* dev; struct request* bidi_rq; TYPE_1__ reply_payload; int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct bsg_job* blk_mq_rq_to_pdu (struct request*) ; 
 int bsg_map_buffer (TYPE_1__*,struct request*) ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool bsg_prepare_job(struct device *dev, struct request *req)
{
	struct bsg_job *job = blk_mq_rq_to_pdu(req);
	int ret;

	job->timeout = req->timeout;

	if (req->bio) {
		ret = bsg_map_buffer(&job->request_payload, req);
		if (ret)
			goto failjob_rls_job;
	}
	if (job->bidi_rq) {
		ret = bsg_map_buffer(&job->reply_payload, job->bidi_rq);
		if (ret)
			goto failjob_rls_rqst_payload;
	}
	job->dev = dev;
	/* take a reference for the request */
	get_device(job->dev);
	kref_init(&job->kref);
	return true;

failjob_rls_rqst_payload:
	kfree(job->request_payload.sg_list);
failjob_rls_job:
	job->result = -ENOMEM;
	return false;
}