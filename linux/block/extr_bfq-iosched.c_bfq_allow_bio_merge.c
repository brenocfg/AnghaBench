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
struct request_queue {TYPE_1__* elevator; } ;
struct request {int dummy; } ;
struct bio {int /*<<< orphan*/  bi_opf; } ;
struct bfq_queue {int dummy; } ;
struct bfq_data {struct bfq_queue* bio_bfqq; int /*<<< orphan*/  bio_bic; } ;
struct TYPE_2__ {struct bfq_data* elevator_data; } ;

/* Variables and functions */
 struct bfq_queue* RQ_BFQQ (struct request*) ; 
 int /*<<< orphan*/  bfq_merge_bfqqs (struct bfq_data*,int /*<<< orphan*/ ,struct bfq_queue*,struct bfq_queue*) ; 
 struct bfq_queue* bfq_setup_cooperator (struct bfq_data*,struct bfq_queue*,struct bio*,int) ; 
 int op_is_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rq_is_sync (struct request*) ; 

__attribute__((used)) static bool bfq_allow_bio_merge(struct request_queue *q, struct request *rq,
				struct bio *bio)
{
	struct bfq_data *bfqd = q->elevator->elevator_data;
	bool is_sync = op_is_sync(bio->bi_opf);
	struct bfq_queue *bfqq = bfqd->bio_bfqq, *new_bfqq;

	/*
	 * Disallow merge of a sync bio into an async request.
	 */
	if (is_sync && !rq_is_sync(rq))
		return false;

	/*
	 * Lookup the bfqq that this bio will be queued with. Allow
	 * merge only if rq is queued there.
	 */
	if (!bfqq)
		return false;

	/*
	 * We take advantage of this function to perform an early merge
	 * of the queues of possible cooperating processes.
	 */
	new_bfqq = bfq_setup_cooperator(bfqd, bfqq, bio, false);
	if (new_bfqq) {
		/*
		 * bic still points to bfqq, then it has not yet been
		 * redirected to some other bfq_queue, and a queue
		 * merge between bfqq and new_bfqq can be safely
		 * fulfilled, i.e., bic can be redirected to new_bfqq
		 * and bfqq can be put.
		 */
		bfq_merge_bfqqs(bfqd, bfqd->bio_bic, bfqq,
				new_bfqq);
		/*
		 * If we get here, bio will be queued into new_queue,
		 * so use new_bfqq to decide whether bio and rq can be
		 * merged.
		 */
		bfqq = new_bfqq;

		/*
		 * Change also bqfd->bio_bfqq, as
		 * bfqd->bio_bic now points to new_bfqq, and
		 * this function may be invoked again (and then may
		 * use again bqfd->bio_bfqq).
		 */
		bfqd->bio_bfqq = bfqq;
	}

	return bfqq == RQ_BFQQ(rq);
}