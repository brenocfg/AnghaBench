#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct request_queue {TYPE_1__* elevator; } ;
struct TYPE_4__ {struct bfq_queue** priv; int /*<<< orphan*/  icq; } ;
struct request {TYPE_2__ elv; struct bio* bio; struct request_queue* q; } ;
struct bio {int dummy; } ;
struct bfq_queue {int saved_in_large_burst; struct bfq_queue* bic; int /*<<< orphan*/  ref; int /*<<< orphan*/  allocated; } ;
struct bfq_io_cq {int saved_in_large_burst; struct bfq_io_cq* bic; int /*<<< orphan*/  ref; int /*<<< orphan*/  allocated; } ;
struct bfq_data {scalar_t__ burst_size; struct bfq_queue oom_bfqq; } ;
struct TYPE_3__ {struct bfq_data* elevator_data; } ;

/* Variables and functions */
 scalar_t__ bfq_bfqq_coop (struct bfq_queue*) ; 
 scalar_t__ bfq_bfqq_in_large_burst (struct bfq_queue*) ; 
 scalar_t__ bfq_bfqq_just_created (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_bfqq_resume_state (struct bfq_queue*,struct bfq_data*,struct bfq_queue*,int) ; 
 scalar_t__ bfq_bfqq_split_coop (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_bic_update_cgroup (struct bfq_queue*,struct bio*) ; 
 int /*<<< orphan*/  bfq_check_ioprio_change (struct bfq_queue*,struct bio*) ; 
 struct bfq_queue* bfq_get_bfqq_handle_split (struct bfq_data*,struct bfq_queue*,struct bio*,int,int const,int*) ; 
 int /*<<< orphan*/  bfq_handle_burst (struct bfq_data*,struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_log_bfqq (struct bfq_data*,struct bfq_queue*,char*,...) ; 
 struct bfq_queue* bfq_split_bfqq (struct bfq_queue*,struct bfq_queue*) ; 
 scalar_t__ bfq_tot_busy_queues (struct bfq_data*) ; 
 int bfqq_process_refs (struct bfq_queue*) ; 
 struct bfq_queue* icq_to_bic (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int rq_is_sync (struct request*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct bfq_queue *bfq_init_rq(struct request *rq)
{
	struct request_queue *q = rq->q;
	struct bio *bio = rq->bio;
	struct bfq_data *bfqd = q->elevator->elevator_data;
	struct bfq_io_cq *bic;
	const int is_sync = rq_is_sync(rq);
	struct bfq_queue *bfqq;
	bool new_queue = false;
	bool bfqq_already_existing = false, split = false;

	if (unlikely(!rq->elv.icq))
		return NULL;

	/*
	 * Assuming that elv.priv[1] is set only if everything is set
	 * for this rq. This holds true, because this function is
	 * invoked only for insertion or merging, and, after such
	 * events, a request cannot be manipulated any longer before
	 * being removed from bfq.
	 */
	if (rq->elv.priv[1])
		return rq->elv.priv[1];

	bic = icq_to_bic(rq->elv.icq);

	bfq_check_ioprio_change(bic, bio);

	bfq_bic_update_cgroup(bic, bio);

	bfqq = bfq_get_bfqq_handle_split(bfqd, bic, bio, false, is_sync,
					 &new_queue);

	if (likely(!new_queue)) {
		/* If the queue was seeky for too long, break it apart. */
		if (bfq_bfqq_coop(bfqq) && bfq_bfqq_split_coop(bfqq)) {
			bfq_log_bfqq(bfqd, bfqq, "breaking apart bfqq");

			/* Update bic before losing reference to bfqq */
			if (bfq_bfqq_in_large_burst(bfqq))
				bic->saved_in_large_burst = true;

			bfqq = bfq_split_bfqq(bic, bfqq);
			split = true;

			if (!bfqq)
				bfqq = bfq_get_bfqq_handle_split(bfqd, bic, bio,
								 true, is_sync,
								 NULL);
			else
				bfqq_already_existing = true;
		}
	}

	bfqq->allocated++;
	bfqq->ref++;
	bfq_log_bfqq(bfqd, bfqq, "get_request %p: bfqq %p, %d",
		     rq, bfqq, bfqq->ref);

	rq->elv.priv[0] = bic;
	rq->elv.priv[1] = bfqq;

	/*
	 * If a bfq_queue has only one process reference, it is owned
	 * by only this bic: we can then set bfqq->bic = bic. in
	 * addition, if the queue has also just been split, we have to
	 * resume its state.
	 */
	if (likely(bfqq != &bfqd->oom_bfqq) && bfqq_process_refs(bfqq) == 1) {
		bfqq->bic = bic;
		if (split) {
			/*
			 * The queue has just been split from a shared
			 * queue: restore the idle window and the
			 * possible weight raising period.
			 */
			bfq_bfqq_resume_state(bfqq, bfqd, bic,
					      bfqq_already_existing);
		}
	}

	/*
	 * Consider bfqq as possibly belonging to a burst of newly
	 * created queues only if:
	 * 1) A burst is actually happening (bfqd->burst_size > 0)
	 * or
	 * 2) There is no other active queue. In fact, if, in
	 *    contrast, there are active queues not belonging to the
	 *    possible burst bfqq may belong to, then there is no gain
	 *    in considering bfqq as belonging to a burst, and
	 *    therefore in not weight-raising bfqq. See comments on
	 *    bfq_handle_burst().
	 *
	 * This filtering also helps eliminating false positives,
	 * occurring when bfqq does not belong to an actual large
	 * burst, but some background task (e.g., a service) happens
	 * to trigger the creation of new queues very close to when
	 * bfqq and its possible companion queues are created. See
	 * comments on bfq_handle_burst() for further details also on
	 * this issue.
	 */
	if (unlikely(bfq_bfqq_just_created(bfqq) &&
		     (bfqd->burst_size > 0 ||
		      bfq_tot_busy_queues(bfqd) == 0)))
		bfq_handle_burst(bfqd, bfqq);

	return bfqq;
}