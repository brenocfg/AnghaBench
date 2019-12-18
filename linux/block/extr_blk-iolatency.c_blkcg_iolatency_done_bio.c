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
typedef  scalar_t__ u64 ;
struct rq_wait {int /*<<< orphan*/  wait; int /*<<< orphan*/  inflight; } ;
struct rq_qos {int dummy; } ;
struct iolatency_grp {scalar_t__ cur_win_nsec; int /*<<< orphan*/  window_start; scalar_t__ min_lat_nsec; struct rq_wait rq_wait; int /*<<< orphan*/  blkiolat; } ;
struct blkcg_gq {struct blkcg_gq* parent; } ;
struct bio {scalar_t__ bi_status; int /*<<< orphan*/  bi_issue; struct blkcg_gq* bi_blkg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_TRACKED ; 
 scalar_t__ BLK_STS_AGAIN ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ atomic64_cmpxchg (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ atomic64_read (int /*<<< orphan*/ *) ; 
 int atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_flagged (struct bio*,int /*<<< orphan*/ ) ; 
 int bio_issue_as_root_blkg (struct bio*) ; 
 int blk_iolatency_enabled (int /*<<< orphan*/ ) ; 
 struct iolatency_grp* blkg_to_lat (struct blkcg_gq*) ; 
 int /*<<< orphan*/  iolatency_check_latencies (struct iolatency_grp*,scalar_t__) ; 
 int /*<<< orphan*/  iolatency_record_time (struct iolatency_grp*,int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  ktime_get () ; 
 scalar_t__ ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void blkcg_iolatency_done_bio(struct rq_qos *rqos, struct bio *bio)
{
	struct blkcg_gq *blkg;
	struct rq_wait *rqw;
	struct iolatency_grp *iolat;
	u64 window_start;
	u64 now = ktime_to_ns(ktime_get());
	bool issue_as_root = bio_issue_as_root_blkg(bio);
	bool enabled = false;
	int inflight = 0;

	blkg = bio->bi_blkg;
	if (!blkg || !bio_flagged(bio, BIO_TRACKED))
		return;

	iolat = blkg_to_lat(bio->bi_blkg);
	if (!iolat)
		return;

	enabled = blk_iolatency_enabled(iolat->blkiolat);
	if (!enabled)
		return;

	while (blkg && blkg->parent) {
		iolat = blkg_to_lat(blkg);
		if (!iolat) {
			blkg = blkg->parent;
			continue;
		}
		rqw = &iolat->rq_wait;

		inflight = atomic_dec_return(&rqw->inflight);
		WARN_ON_ONCE(inflight < 0);
		/*
		 * If bi_status is BLK_STS_AGAIN, the bio wasn't actually
		 * submitted, so do not account for it.
		 */
		if (iolat->min_lat_nsec && bio->bi_status != BLK_STS_AGAIN) {
			iolatency_record_time(iolat, &bio->bi_issue, now,
					      issue_as_root);
			window_start = atomic64_read(&iolat->window_start);
			if (now > window_start &&
			    (now - window_start) >= iolat->cur_win_nsec) {
				if (atomic64_cmpxchg(&iolat->window_start,
					     window_start, now) == window_start)
					iolatency_check_latencies(iolat, now);
			}
		}
		wake_up(&rqw->wait);
		blkg = blkg->parent;
	}
}