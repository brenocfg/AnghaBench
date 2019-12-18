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
struct throtl_service_queue {struct throtl_service_queue* parent_sq; scalar_t__* nr_queued; } ;
struct throtl_qnode {int dummy; } ;
struct throtl_grp {scalar_t__* last_low_overflow_time; int flags; struct throtl_service_queue service_queue; int /*<<< orphan*/ * io_disp; int /*<<< orphan*/ * bytes_disp; struct throtl_qnode* qnode_on_parent; int /*<<< orphan*/ * has_rules; struct throtl_data* td; } ;
struct throtl_data {int /*<<< orphan*/  track_bio_latency; int /*<<< orphan*/ * nr_queued; } ;
struct request_queue {int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  root_blkg; } ;
struct blkcg_gq {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  value; } ;
struct TYPE_3__ {int /*<<< orphan*/  bi_size; } ;
struct bio {TYPE_2__ bi_issue; TYPE_1__ bi_iter; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ISSUE_THROTL_SKIP_LATENCY ; 
 int /*<<< orphan*/  BIO_THROTTLED ; 
 int READ ; 
 int THROTL_TG_WAS_EMPTY ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 size_t WRITE ; 
 int bio_data_dir (struct bio*) ; 
 scalar_t__ bio_flagged (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_set_flag (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_throtl_update_idletime (struct throtl_grp*) ; 
 struct throtl_grp* blkg_to_tg (int /*<<< orphan*/ ) ; 
 void* jiffies ; 
 int /*<<< orphan*/  rcu_read_lock_held () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct throtl_grp* sq_to_tg (struct throtl_service_queue*) ; 
 int /*<<< orphan*/  tg_bps_limit (struct throtl_grp*,int) ; 
 int /*<<< orphan*/  tg_iops_limit (struct throtl_grp*,int) ; 
 int /*<<< orphan*/  tg_may_dispatch (struct throtl_grp*,struct bio*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tg_update_disptime (struct throtl_grp*) ; 
 int /*<<< orphan*/  throtl_add_bio_tg (struct bio*,struct throtl_qnode*,struct throtl_grp*) ; 
 scalar_t__ throtl_can_upgrade (struct throtl_data*,struct throtl_grp*) ; 
 int /*<<< orphan*/  throtl_charge_bio (struct throtl_grp*,struct bio*) ; 
 int /*<<< orphan*/  throtl_downgrade_check (struct throtl_grp*) ; 
 int /*<<< orphan*/  throtl_log (struct throtl_service_queue*,char*,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  throtl_schedule_next_dispatch (struct throtl_service_queue*,int) ; 
 int /*<<< orphan*/  throtl_trim_slice (struct throtl_grp*,int) ; 
 int /*<<< orphan*/  throtl_update_latency_buckets (struct throtl_data*) ; 
 int /*<<< orphan*/  throtl_upgrade_check (struct throtl_grp*) ; 
 int /*<<< orphan*/  throtl_upgrade_state (struct throtl_data*) ; 

bool blk_throtl_bio(struct request_queue *q, struct blkcg_gq *blkg,
		    struct bio *bio)
{
	struct throtl_qnode *qn = NULL;
	struct throtl_grp *tg = blkg_to_tg(blkg ?: q->root_blkg);
	struct throtl_service_queue *sq;
	bool rw = bio_data_dir(bio);
	bool throttled = false;
	struct throtl_data *td = tg->td;

	WARN_ON_ONCE(!rcu_read_lock_held());

	/* see throtl_charge_bio() */
	if (bio_flagged(bio, BIO_THROTTLED) || !tg->has_rules[rw])
		goto out;

	spin_lock_irq(&q->queue_lock);

	throtl_update_latency_buckets(td);

	blk_throtl_update_idletime(tg);

	sq = &tg->service_queue;

again:
	while (true) {
		if (tg->last_low_overflow_time[rw] == 0)
			tg->last_low_overflow_time[rw] = jiffies;
		throtl_downgrade_check(tg);
		throtl_upgrade_check(tg);
		/* throtl is FIFO - if bios are already queued, should queue */
		if (sq->nr_queued[rw])
			break;

		/* if above limits, break to queue */
		if (!tg_may_dispatch(tg, bio, NULL)) {
			tg->last_low_overflow_time[rw] = jiffies;
			if (throtl_can_upgrade(td, tg)) {
				throtl_upgrade_state(td);
				goto again;
			}
			break;
		}

		/* within limits, let's charge and dispatch directly */
		throtl_charge_bio(tg, bio);

		/*
		 * We need to trim slice even when bios are not being queued
		 * otherwise it might happen that a bio is not queued for
		 * a long time and slice keeps on extending and trim is not
		 * called for a long time. Now if limits are reduced suddenly
		 * we take into account all the IO dispatched so far at new
		 * low rate and * newly queued IO gets a really long dispatch
		 * time.
		 *
		 * So keep on trimming slice even if bio is not queued.
		 */
		throtl_trim_slice(tg, rw);

		/*
		 * @bio passed through this layer without being throttled.
		 * Climb up the ladder.  If we''re already at the top, it
		 * can be executed directly.
		 */
		qn = &tg->qnode_on_parent[rw];
		sq = sq->parent_sq;
		tg = sq_to_tg(sq);
		if (!tg)
			goto out_unlock;
	}

	/* out-of-limit, queue to @tg */
	throtl_log(sq, "[%c] bio. bdisp=%llu sz=%u bps=%llu iodisp=%u iops=%u queued=%d/%d",
		   rw == READ ? 'R' : 'W',
		   tg->bytes_disp[rw], bio->bi_iter.bi_size,
		   tg_bps_limit(tg, rw),
		   tg->io_disp[rw], tg_iops_limit(tg, rw),
		   sq->nr_queued[READ], sq->nr_queued[WRITE]);

	tg->last_low_overflow_time[rw] = jiffies;

	td->nr_queued[rw]++;
	throtl_add_bio_tg(bio, qn, tg);
	throttled = true;

	/*
	 * Update @tg's dispatch time and force schedule dispatch if @tg
	 * was empty before @bio.  The forced scheduling isn't likely to
	 * cause undue delay as @bio is likely to be dispatched directly if
	 * its @tg's disptime is not in the future.
	 */
	if (tg->flags & THROTL_TG_WAS_EMPTY) {
		tg_update_disptime(tg);
		throtl_schedule_next_dispatch(tg->service_queue.parent_sq, true);
	}

out_unlock:
	spin_unlock_irq(&q->queue_lock);
out:
	bio_set_flag(bio, BIO_THROTTLED);

#ifdef CONFIG_BLK_DEV_THROTTLING_LOW
	if (throttled || !td->track_bio_latency)
		bio->bi_issue.value |= BIO_ISSUE_THROTL_SKIP_LATENCY;
#endif
	return throttled;
}