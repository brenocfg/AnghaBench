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
struct request {int dummy; } ;
struct bsg_job {int /*<<< orphan*/  request; scalar_t__ bidi_rq; int /*<<< orphan*/  bidi_bio; } ;

/* Variables and functions */
 struct bsg_job* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  blk_put_request (scalar_t__) ; 
 int /*<<< orphan*/  blk_rq_unmap_user (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bsg_transport_free_rq(struct request *rq)
{
	struct bsg_job *job = blk_mq_rq_to_pdu(rq);

	if (job->bidi_rq) {
		blk_rq_unmap_user(job->bidi_bio);
		blk_put_request(job->bidi_rq);
	}

	kfree(job->request);
}