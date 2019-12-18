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
struct request {int /*<<< orphan*/  ref; int /*<<< orphan*/  (* end_io ) (struct request*,int /*<<< orphan*/ ) ;} ;
struct blk_mq_hw_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __blk_mq_free_request (struct request*) ; 
 scalar_t__ blk_mq_req_expired (struct request*,unsigned long*) ; 
 int /*<<< orphan*/  blk_mq_rq_timed_out (struct request*,int) ; 
 scalar_t__ is_flush_rq (struct request*,struct blk_mq_hw_ctx*) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool blk_mq_check_expired(struct blk_mq_hw_ctx *hctx,
		struct request *rq, void *priv, bool reserved)
{
	unsigned long *next = priv;

	/*
	 * Just do a quick check if it is expired before locking the request in
	 * so we're not unnecessarilly synchronizing across CPUs.
	 */
	if (!blk_mq_req_expired(rq, next))
		return true;

	/*
	 * We have reason to believe the request may be expired. Take a
	 * reference on the request to lock this request lifetime into its
	 * currently allocated context to prevent it from being reallocated in
	 * the event the completion by-passes this timeout handler.
	 *
	 * If the reference was already released, then the driver beat the
	 * timeout handler to posting a natural completion.
	 */
	if (!refcount_inc_not_zero(&rq->ref))
		return true;

	/*
	 * The request is now locked and cannot be reallocated underneath the
	 * timeout handler's processing. Re-verify this exact request is truly
	 * expired; if it is not expired, then the request was completed and
	 * reallocated as a new request.
	 */
	if (blk_mq_req_expired(rq, next))
		blk_mq_rq_timed_out(rq, reserved);

	if (is_flush_rq(rq, hctx))
		rq->end_io(rq, 0);
	else if (refcount_dec_and_test(&rq->ref))
		__blk_mq_free_request(rq);

	return true;
}